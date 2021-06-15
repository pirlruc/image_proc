#ifndef IMPROC_SERVICES_FACTORY_H
#define IMPROC_SERVICES_FACTORY_H

#ifdef WITH_DEBUG
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <spdlog/spdlog.h>
#endif

#include <improc/improc_defs.h>
#include <improc/services/base_service.h>
#include <improc/services/container.h>

#include <functional>

namespace improc
{
    template<typename key_type,typename service_type>
    std::shared_ptr<BaseService<key_type>> LoadFromJson(const Json::Value& service_json);

    template<typename service_type>
    std::shared_ptr<StringKeyBaseService> LoadFromJson(const Json::Value& service_json);

    template <typename key_type>
    class IMPROC_EXPORTS ServicesFactory : public Container<key_type,std::function<std::shared_ptr<BaseService<key_type>>(const Json::Value&)>>
    {
        public:
            ServicesFactory();
    };

    typedef Container<std::string,std::function<std::shared_ptr<StringKeyBaseService>(const Json::Value&)>> StringKeyServicesFactory;
}

#endif