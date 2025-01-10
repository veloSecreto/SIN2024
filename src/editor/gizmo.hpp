#pragma once
#include "im3d/im3d.h"
#include "../api/opengl/gl_renderer.h"
#include "../input/input.h"
#include "../physics/transform.hpp"
#include "../game/_camera.h"
#include "../backend/backend.h"

namespace Gizmo {

    inline GLuint g_Im3dVertexArray;
    inline GLuint g_Im3dVertexBuffer;

    inline Im3d::Mat4 g_transform = (1.0f);

    inline bool _inUse = false;

    inline void cleanUp() {

        Im3d::GetContext();
    }


    inline bool hasHover() {
        return (Im3d::GetHotId() != 0);
    }

    inline bool inUse() {
        return _inUse;
    }

    inline Im3d::Mat4& getTransform() {
        return g_transform;
    }

    inline Im3d::Mat4 GlmMat4ToIm3dMat4(const glm::mat4& glmMatrix) {
        Im3d::Mat4 matrix;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                matrix[i * 4 + j] = glmMatrix[i][j];
            }
        }
        return matrix;
    }

    inline void init() {
        glGenBuffers(1, &g_Im3dVertexBuffer);
        glGenVertexArrays(1, &g_Im3dVertexArray);
        glBindVertexArray(g_Im3dVertexArray);
        glBindBuffer(GL_ARRAY_BUFFER, g_Im3dVertexBuffer);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Im3d::VertexData), (GLvoid*)offsetof(Im3d::VertexData, m_positionSize));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Im3d::VertexData), (GLvoid*)offsetof(Im3d::VertexData, m_color));
        glBindVertexArray(0);
    }

#define if_likely(e)   if(!!(e))
    constexpr float Pi = 3.14159265359f;
    constexpr float TwoPi = 2.0f * Pi;
    constexpr float HalfPi = 0.5f * Pi;

    inline Im3d::Vec3 ToEulerXYZ(const Im3d::Mat3& _m) {
        // http://www.staff.city.ac.uk/~sbbh653/publications/euler.pdf
        Im3d::Vec3 ret;
        if_likely(fabs(_m(2, 0)) < 1.0f) {
            ret.y = -asinf(_m(2, 0));
            float c = 1.0f / cosf(ret.y);
            ret.x = atan2f(_m(2, 1) * c, _m(2, 2) * c);
            ret.z = atan2f(_m(1, 0) * c, _m(0, 0) * c);
        }
        else {
            ret.z = 0.0f;
            if (!(_m(2, 0) > -1.0f)) {
                ret.x = ret.z + atan2f(_m(0, 1), _m(0, 2));
                ret.y = HalfPi;
            }
            else {
                ret.x = -ret.z + atan2f(-_m(0, 1), -_m(0, 2));
                ret.y = -HalfPi;
            }
        }
        return ret;
    }

    inline void update(Transform& transform) {

        Im3d::Context& ctx = Im3d::GetContext();
        ctx.m_gizmoHeightPixels = 50;
        ctx.m_gizmoSizePixels = 6;

        if (Input::keyPressed(SIN_KEY_NUMPAD_1)) {
            Im3d::GetContext().m_gizmoMode = Im3d::GizmoMode::GizmoMode_Translation;
        }
        if (Input::keyPressed(SIN_KEY_NUMPAD_2)) {
            Im3d::GetContext().m_gizmoMode = Im3d::GizmoMode::GizmoMode_Rotation;
        }
        if (Input::keyPressed(SIN_KEY_NUMPAD_3)) {
            Im3d::GetContext().m_gizmoMode = Im3d::GizmoMode::GizmoMode_Scale;
        }

        Im3d::AppData& ad = Im3d::GetAppData();

        ad.m_deltaTime = Clock::dt;
        ad.m_viewportSize = Im3d::Vec2((float)Backend::getWinWidth(), (float)Backend::getWinHeight());
        ad.m_viewOrigin = { Camera::m_position.x, Camera::m_position.y, Camera::m_position.z };
        ad.m_viewDirection = { Camera::_forward.x, Camera::_forward.y, Camera::_forward.z };
        ad.m_worldUp = Im3d::Vec3(0.0f, 1.0f, 0.0f);
        ad.m_projOrtho = false;
        ad.m_projScaleY = tanf(1.0f * 0.5f) * 2.0f; // controls how gizmos are scaled in world space to maintain a constant screen height or vertical fov for a perspective projection

        // World space cursor ray from mouse position
        auto& mousePos = Input::getMousePos();
        Im3d::Vec2 cursorPos = { mousePos.x, mousePos.y };
        glm::vec3 mouseRay = Input::getMouseRay();
        cursorPos.x = (cursorPos.x / ad.m_viewportSize.x) * 2.0f - 1.0f;
        cursorPos.y = (cursorPos.y / ad.m_viewportSize.y) * 2.0f - 1.0f;
        cursorPos.y = -cursorPos.y; // window origin is top-left, ndc is bottom-left
        ad.m_cursorRayOrigin = { Camera::m_position.x, Camera::m_position.y, Camera::m_position.z };
        ad.m_cursorRayDirection = { mouseRay.x, mouseRay.y, mouseRay.z };
        // Fill the key state array; using GetAsyncKeyState here but this could equally well be done via the window proc.
        // All key states have an equivalent (and more descriptive) 'Action_' enum.
        ad.m_keyDown[Im3d::Mouse_Left] = Input::mouseButtonDown(SIN_MOUSE_BUTTON_LEFT);

        Im3d::NewFrame();
        g_transform = GlmMat4ToIm3dMat4(transform.to_mat4());
        _inUse = Im3d::Gizmo("GizmoUnified", g_transform);
        Im3d::EndFrame();

        Im3d::Mat4 resultMatrix = Gizmo::getTransform();
        Im3d::Vec3 pos = resultMatrix.getTranslation();
        Im3d::Vec3 euler = ToEulerXYZ(resultMatrix.getRotation());
        Im3d::Vec3 scale = resultMatrix.getScale();

        transform.setPosition(glm::vec3(pos.x, pos.y, pos.z));
        transform.setRotation(glm::vec3(euler.x, euler.y, euler.z) * 180.0f / (float)SIN_PI);
        transform.setScale(glm::vec3(scale.x, scale.y, scale.z));
    }

    inline void draw(const glm::vec2& viewport) {
        GLint prevViewport[4];
        glGetIntegerv(GL_VIEWPORT, prevViewport);

        GLboolean prevBlendEnabled = glIsEnabled(GL_BLEND);
        GLboolean prevDepthTestEnabled = glIsEnabled(GL_DEPTH_TEST);
        GLboolean prevCullFaceEnabled = glIsEnabled(GL_CULL_FACE);

        GLint prevBlendEquation;
        glGetIntegerv(GL_BLEND_EQUATION, &prevBlendEquation);

        GLint prevBlendSrc, prevBlendDst;
        glGetIntegerv(GL_BLEND_SRC, &prevBlendSrc);
        glGetIntegerv(GL_BLEND_DST, &prevBlendDst);

        glEnable(GL_BLEND);
        glBlendEquation(GL_FUNC_ADD);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_PROGRAM_POINT_SIZE);
        glDisable(GL_DEPTH_TEST);

        glViewport(0, 0, static_cast<GLsizei>(viewport.x), static_cast<GLsizei>(viewport.y));

        for (Im3d::U32 i = 0, n = Im3d::GetDrawListCount(); i < n; ++i) {
            const Im3d::DrawList& drawList = Im3d::GetDrawLists()[i];

            Shader* shader = nullptr;
            GLenum prim;

            switch (drawList.m_primType) {
            case Im3d::DrawPrimitive_Points:
                prim = GL_POINTS;
                shader = OpenGLRenderer::getShaderByName("im3d_points");
                glDisable(GL_CULL_FACE);
                break;
            case Im3d::DrawPrimitive_Lines:
                prim = GL_LINES;
                shader = OpenGLRenderer::getShaderByName("im3d_lines");
                glDisable(GL_CULL_FACE);
                break;
            case Im3d::DrawPrimitive_Triangles:
                prim = GL_TRIANGLES;
                shader = OpenGLRenderer::getShaderByName("im3d_triangles");
                break;
            default:
                IM3D_ASSERT(false);
                return;
            }

            if (!shader) {
                std::cerr << "Shader not found for primitive type!" << std::endl;
                continue;
            }

            glBindVertexArray(g_Im3dVertexArray);
            glBindBuffer(GL_ARRAY_BUFFER, g_Im3dVertexBuffer);

            glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)drawList.m_vertexCount * sizeof(Im3d::VertexData),
                (GLvoid*)drawList.m_vertexData, GL_STREAM_DRAW);

            shader->use();
            shader->setVec2("uViewport", viewport);

            glDrawArrays(prim, 0, (GLsizei)drawList.m_vertexCount);
        }

        glViewport(prevViewport[0], prevViewport[1], prevViewport[2], prevViewport[3]);

        if (prevBlendEnabled) glEnable(GL_BLEND); else glDisable(GL_BLEND);
        glBlendEquation(prevBlendEquation);
        glBlendFunc(prevBlendSrc, prevBlendDst);

        if (prevDepthTestEnabled) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);
        if (prevCullFaceEnabled) glEnable(GL_CULL_FACE); else glDisable(GL_CULL_FACE);

        glDisable(GL_PROGRAM_POINT_SIZE);
    }

    inline void resetHover() {
        Im3d::Context& ctx = Im3d::GetContext();
        ctx.reset();
        ctx.resetId();
    }
}