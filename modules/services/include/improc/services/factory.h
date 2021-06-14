#ifndef IMPROC_SERVICES_FACTORY_H
#define IMPROC_SERVICES_FACTORY_H

#ifdef WITH_DEBUG
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <spdlog/spdlog.h>
#endif

#include <improc/improc_defs.h>
#include <improc/services/base_service.h>

#include <functional>

namespace improc
{
    template<typename service_type>
    std::shared_ptr<improc::StringKeyBaseService> LoadFromJson(const Json::Value& service_json);

    template <typename key_type>
    class IMPROC_EXPORTS ServicesFactory : public Container<key_type,std::function<std::shared_ptr<improc::StringKeyBaseService>(const Json::Value&)>>
    {
        public:
            ServicesFactory();
    };

    typedef ServicesFactory<std::string>  StringKeyServicesFactory;
}

#endif