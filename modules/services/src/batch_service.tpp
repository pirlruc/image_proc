template <typename key_type>
improc::BatchService<key_type>::BatchService() {}

template <typename key_type>
void improc::BatchService<key_type>::Load( const improc::ServicesFactory<key_type>& factory
                                         , const Json::Value& batch_service_json )
{
    #ifdef WITH_DEBUG
    SPDLOG_TRACE("");
    spdlog::trace("Loading services for batch...");
    #endif

    const std::string kServicesKey = "services";
    if (batch_service_json.isMember(kServicesKey) == false) 
    {
        #ifdef WITH_DEBUG
        SPDLOG_ERROR("");
        spdlog::error("ERROR_01: Member {} missing on json.",kServicesKey);
        #endif

        throw improc::file_processing_error();
    }
    Json::Value service_elements = batch_service_json[kServicesKey];

    #ifdef WITH_DEBUG
    SPDLOG_DEBUG("");
    spdlog::debug("{} services in factory.",factory.Size());
    #endif

    for (Json::Value::const_iterator srvce_elem_iter = service_elements.begin(); srvce_elem_iter != service_elements.end(); ++srvce_elem_iter)
    {
        const std::string kServiceType = "type";
        const std::string kServiceArgs = "args";

        Json::Value service_args {};
        key_type    service_type {};
        for (Json::Value::const_iterator srvce_elem_field_iter = srvce_elem_iter->begin(); srvce_elem_field_iter != srvce_elem_iter->end(); ++srvce_elem_field_iter)
        {
            #ifdef WITH_DEBUG
            SPDLOG_DEBUG("");
            spdlog::debug("Analyzing field {} for service element...",srvce_elem_field_iter.name());
            #endif

            if      (srvce_elem_field_iter.name() == kServiceType)   service_type = improc::jsonfile::ReadElement<key_type>(*srvce_elem_field_iter);
            else if (srvce_elem_field_iter.name() == kServiceArgs)   service_args = *srvce_elem_field_iter;
            else 
            {
                #ifdef WITH_DEBUG
                SPDLOG_WARN("");
                spdlog::warn("WARN_02: Member {} not recognized for service element.",srvce_elem_field_iter.name());
                #endif
            }
        }
        
        if (service_type.empty() == true)
        {
            #ifdef WITH_DEBUG
            SPDLOG_ERROR("");
            spdlog::error("ERROR_03: Service type missing for service element.");
            #endif

            throw improc::file_processing_error();
        }

        #ifdef WITH_DEBUG
        SPDLOG_INFO("");
        spdlog::info("Adding service element {}...",service_type);
        #endif

        improc::BatchService<key_type>::Service service {};
        service.type = service_type;
        service.data = factory.Get(service_type)(service_args);
        this->data_.push_back(service);
    }
    #ifdef WITH_DEBUG
    SPDLOG_INFO("");
    spdlog::info("{} services added to batch.",this->data_.size());
    #endif
}

template <typename key_type>
void improc::BatchService<key_type>::Run(improc::Context<key_type>& context) const
{
    #ifdef WITH_DEBUG
    SPDLOG_TRACE("");
    spdlog::trace("Running service batch...");
    #endif

    for (auto service_iter = this->data_.begin(); service_iter != this->data_.end(); service_iter++)
    {
        #ifdef WITH_DEBUG
        SPDLOG_DEBUG("");
        spdlog::debug("Running service {}...",(*service_iter).type);
        #endif

        #ifdef WITH_DEBUG
        std::chrono::time_point<std::chrono::high_resolution_clock> service_start_time = std::chrono::high_resolution_clock::now();
        #endif

        (*service_iter).data->Run(context);
        
        #ifdef WITH_DEBUG
        std::chrono::time_point<std::chrono::high_resolution_clock> service_stop_time  = std::chrono::high_resolution_clock::now();
        auto exec_time = std::chrono::duration_cast<std::chrono::microseconds>(service_stop_time - service_start_time);
        SPDLOG_INFO("");
        spdlog::info("Service {} executed in {} ms",(*service_iter).type,exec_time.count() / 1000.0);
        #endif
    }
}

template <typename key_type>
size_t improc::BatchService<key_type>::Size() const
{
    #ifdef WITH_DEBUG
    SPDLOG_TRACE("");
    spdlog::trace("Obtaining number of services in batch...");
    #endif
    
    return this->data_.size();
}
