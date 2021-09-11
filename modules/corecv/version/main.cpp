#include <improc_corecv_config.hpp>

#include <iostream>

int main()
{
    std::cout   << "improc_corecv Version: " 
                << IMPROC_CORECV_VERSION_MAJOR 
                << "."
                << IMPROC_CORECV_VERSION_MINOR
                << "."
                << IMPROC_CORECV_VERSION_PATCH
                << std::endl;
    return 0;
}
