#ifndef IMPROC_CORECV_DEFINITIONS_HPP
#define IMPROC_CORECV_DEFINITIONS_HPP

#ifndef IMPROC_EXPORTS
    #if defined _WIN32 || defined WINCE
        #define IMPROC_EXPORTS __declspec(dllexport)
    #elif defined __GNUC__ && __GNUC__ >= 4 || defined __APPLE__
        #define IMPROC_EXPORTS __attribute__ ((visibility ("default")))
    #else
        #define IMPROC_EXPORTS
    #endif
#endif

#define IMPROC_ENUM_KEY_TYPE unsigned int

#endif