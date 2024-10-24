
<<<<<<< HEAD
=======
/*
███    █▄  ███▄▄▄▄    ▄█        ▄██████▄   ▄█    █▄     ▄████████ ████████▄  
███    ███ ███▀▀▀██▄ ███       ███    ███ ███    ███   ███    ███ ███   ▀███ 
███    ███ ███   ███ ███       ███    ███ ███    ███   ███    █▀  ███    ███ 
███    ███ ███   ███ ███       ███    ███ ███    ███  ▄███▄▄▄     ███    ███ 
███    ███ ███   ███ ███       ███    ███ ███    ███ ▀▀███▀▀▀     ███    ███ 
███    ███ ███   ███ ███       ███    ███ ███    ███   ███    █▄  ███    ███ 
███    ███ ███   ███ ███▌    ▄ ███    ███ ███    ███   ███    ███ ███   ▄███ 
████████▀   ▀█   █▀  █████▄▄██  ▀██████▀   ▀██████▀    ██████████ ████████▀  
                     ▀                                                       
*/

>>>>>>> d741c32 (Implemented Scene based rendering, has issues)

// Prevent accidently selecting integrated GPU
#ifdef _MSC_VER
extern "C" {
    __declspec(dllexport) unsigned __int32 AmdPowerXpressRequestHighPerformance = 0x1;
    __declspec(dllexport) unsigned __int32 NvOptimusEnablement = 0x1;
}
#endif

<<<<<<< HEAD
#include "engine.h"
=======

#include "engine.h"
#include <iostream>
>>>>>>> d741c32 (Implemented Scene based rendering, has issues)

using namespace std;

int main()
{
    // that's for ease of debugging, remove this
    // cout << "\n\n\n<===============================================================================================>\n\n\n" << endl;

    cout << "We are all alone on life's journey, held captive by the limitations of human consciousness." << endl << endl << endl;
    Engine::init();
    Engine::run();

    // that's for ease of debugging, remove this
    // cout << "\n\n\n<===============================================================================================>\n\n\n" << endl;
}