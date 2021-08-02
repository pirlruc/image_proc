template <typename key_type>
improc::BaseService<key_type>::BaseService() {}

template <typename key_type>
void improc::BaseService<key_type>::Load(const Json::Value& service_json)
{
    #ifdef WITH_DEBUG
    SPDLOG_TRACE("");
    spdlog::trace("Loading service inputs and outputs...");
    #endif

    for (Json::Value::const_iterator service_field_iter = service_json.begin(); service_field_iter != service_json.end(); ++service_field_iter)
    {
        const std::string kInputKey  = "inputs";
        const std::string kOutputKey = "outputs";

        #ifdef WITH_DEBUG
        SPDLOG_INFO("");
        spdlog::info("Analyzing field {} for service...",service_field_iter.name());
        #endif

        std::vector<key_type> list_args;
        if (service_field_iter.name() == kInputKey || service_field_iter.name() == kOutputKey)
        {
            if (service_field_iter->isArray() == true)
            {
                for (Json::Value::const_iterator input_iter = service_field_iter->begin(); input_iter != service_field_iter->end(); ++input_iter)
                {
                    list_args.push_back(improc::jsonfile::ReadElement<key_type>(*input_iter));
                }
            }
            else
            {
                list_args.push_back(improc::jsonfile::ReadElement<key_type>(*service_field_iter));
            }

            if (service_field_iter.name() == kInputKey)
            {
                this->inputs_  = list_args;
            }
            else // (service_field_iter.name() == kOutputKey)
            {
                this->outputs_ = list_args;
            }
        }

        if (this->inputs_.empty() != true && this->outputs_.empty() != true)  break;
    }

    if (this->inputs_.empty() == true || this->outputs_.empty() == true)
    {
        #ifdef WITH_DEBUG
        SPDLOG_ERROR("");
        spdlog::error("ERROR_01: Input or output members missing.");
        #endif

        throw improc::file_processing_error();
    }
}    
