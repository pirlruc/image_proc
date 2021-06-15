#include <improc/services/batch_service.h>

template <typename key_type>
improc::BatchService<key_type>::BatchService() {}

template <typename key_type>
std::shared_ptr<improc::BaseService<key_type>>& improc::BatchService<key_type>::operator[](const size_t& index)
{
    #ifdef WITH_DEBUG
    SPDLOG_TRACE("");
    spdlog::trace("Obtaining index {} from services vector...",index);
    #endif

    return this->data_[index];
}

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
        std::string service_type {};
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
        
        this->data_.push_back(factory.Get(service_type)(service_args));
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

    size_t service_idx = 0;
    for (auto service_iter = this->data_.begin(); service_iter != this->data_.end(); service_iter++)
    {
        #ifdef WITH_DEBUG
        SPDLOG_DEBUG("");
        spdlog::debug("Running service index {}...",service_idx);
        service_idx += 1;
        #endif

        (*service_iter)->Run(context);
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