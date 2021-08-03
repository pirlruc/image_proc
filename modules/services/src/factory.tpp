template <typename key_type>
improc::ServicesFactory<key_type>::ServicesFactory() : improc::Container<key_type,std::function<std::shared_ptr<improc::BaseService<key_type>>(const Json::Value&)>>() {}

template<typename key_type,typename service_type>
std::shared_ptr<improc::BaseService<key_type>> improc::LoadServiceFromJson(const Json::Value& service_json)
{
    SPDLOG_LOGGER_CALL( improc::ServicesLogger::get()->data()
                      , spdlog::level::trace
                      , "Creating shared pointer for key {} service {}..."
                      , typeid(key_type).name(), typeid(service_type).name() );
    std::shared_ptr<improc::BaseService<key_type>> service {std::make_shared<service_type>(service_type())};
    service->Load(service_json);
    return service;
}

template<typename service_type>
std::shared_ptr<improc::StringKeyBaseService> improc::LoadServiceFromJson(const Json::Value& service_json)
{
    SPDLOG_LOGGER_CALL( improc::ServicesLogger::get()->data()
                      , spdlog::level::trace
                      , "Creating shared pointer for key string service {}..."
                      , typeid(service_type).name() );
    std::shared_ptr<improc::StringKeyBaseService> service {std::make_shared<service_type>(service_type())};
    service->Load(service_json);
    return service;
}
