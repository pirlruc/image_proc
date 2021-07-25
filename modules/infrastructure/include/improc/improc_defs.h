#ifndef IMPROC_EXPORTS
    #if defined _WIN32 || defined WINCE
        #define IMPROC_EXPORTS __declspec(dllexport)
    #elif defined __GNUC__ && __GNUC__ >= 4 || defined __APPLE__
        #define IMPROC_EXPORTS __attribute__ ((visibility ("default")))
    #else
        #define IMPROC_EXPORTS
    #endif
#endif
