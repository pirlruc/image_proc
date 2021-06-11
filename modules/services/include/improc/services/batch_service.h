#ifndef IMPROC_SERVICES_BATCH_SERVICE_H
#define IMPROC_SERVICES_BATCH_SERVICE_H

#ifdef WITH_DEBUG
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <spdlog/spdlog.h>
#endif

#include <improc/improc_defs.h>
#include <improc/services/context.h>
#include <improc/services/base_service.h>

#include <map>

namespace improc
{
    template <typename key_type = std::string>
    class IMPROC_EXPORTS BatchService
    {
        private:
            std::map<key_type,improc::BaseService<key_type>*> data_;

        public:
            BatchService();

            void Load   ( const improc::ServicesFactory<key_type>& factory
                        , const Json::Value& batch_service_json );
            void Run    ( improc::Context<key_type>& context );
    };
}

#endif