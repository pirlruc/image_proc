#include <improc_infrastructure_config.h>

#include <iostream>

int main()
{
    std::cout   << "improc_infrastructure Version: " 
                << IMPROC_INFRASTRUCTURE_VERSION_MAJOR 
                << "."
                << IMPROC_INFRASTRUCTURE_VERSION_MINOR
                << "."
                << IMPROC_INFRASTRUCTURE_VERSION_PATCH
                << std::endl;
    return 0;
}
