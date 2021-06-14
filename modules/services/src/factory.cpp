#include <improc/services/factory.h>

template<typename service_type>
std::shared_ptr<improc::StringKeyBaseService> improc::LoadFromJson(const Json::Value& service_json)
{
    #ifdef WITH_DEBUG
    SPDLOG_TRACE("");
    spdlog::trace("Creating shared pointer for service {}...",service_type);
    #endif

    std::shared_ptr<improc::StringKeyBaseService> service {std::make_shared<service_type>(service_type())};
    service->Load(service_json);
    return service;
}

template <typename key_type>
improc::ServicesFactory<key_type>::ServicesFactory() : improc::Container<key_type,std::function<std::shared_ptr<improc::StringKeyBaseService>(const Json::Value&)>>() {}
