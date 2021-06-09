#ifndef IMPROC_SERVICES_FACTORY_H
#define IMPROC_SERVICES_FACTORY_H

#ifdef WITH_DEBUG
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <spdlog/spdlog.h>
#endif

#include <improc/services/base_service.h>

namespace improc
{
    template <typename key_type = std::string>
    class ServicesFactory : public Container<key_type>
    {
        public:
            ServicesFactory();
    };
}

#endif