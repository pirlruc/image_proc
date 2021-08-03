#ifndef IMPROC_SERVICES_FACTORY_H
#define IMPROC_SERVICES_FACTORY_H

#include <improc/improc_defs.h>
#include <improc/services/logger_services.h>
#include <improc/services/base_service.h>
#include <improc/services/container.h>

#include <functional>

namespace improc
{
    template <typename key_type>
    class IMPROC_EXPORTS ServicesFactory : public Container<key_type,std::function<std::shared_ptr<BaseService<key_type>>(const Json::Value&)>>
    {
        public:
            ServicesFactory();
    };

    typedef ServicesFactory<std::string>    StringKeyServicesFactory;

    template<typename key_type,typename service_type>
    IMPROC_EXPORTS std::shared_ptr<BaseService<key_type>>   LoadServiceFromJson(const Json::Value& service_json);

    template<typename service_type>
    IMPROC_EXPORTS std::shared_ptr<StringKeyBaseService>    LoadServiceFromJson(const Json::Value& service_json);
}

#include <factory.tpp>

#endif