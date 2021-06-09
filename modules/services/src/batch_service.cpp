#include <improc/services/batch_service.h>

template <typename key_type>
improc::BatchService<key_type>::BatchService() {}

template <typename key_type>
improc::BatchService<key_type>::Load( const improc::ServicesFactory<key_type>& factory
                                    , const Json::Value& batch_service_json )
{
    #ifdef WITH_DEBUG
    SPDLOG_TRACE("");
    spdlog::trace("Loading service batch...");
    #endif
}

template <typename key_type>
improc::BatchService<key_type>::Run(improc::Context<key_type>& context)
{
    #ifdef WITH_DEBUG
    SPDLOG_TRACE("");
    spdlog::trace("Running service batch...");
    #endif

    for (auto const& [key,service] : this->data_)
    {
        #ifdef WITH_DEBUG
        SPDLOG_TRACE("");
        spdlog::trace("Running service with key {}...",key);
        #endif

        service->Run(context);
    }
}
