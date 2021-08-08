#include <improc_services_config.h>

#include <iostream>

int main()
{
    std::cout   << "improc_services Version: " 
                << IMPROC_SERVICES_VERSION_MAJOR 
                << "."
                << IMPROC_SERVICES_VERSION_MINOR
                << "."
                << IMPROC_SERVICES_VERSION_PATCH
                << std::endl;
    return 0;
}
