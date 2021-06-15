#ifndef IMPROC_SERVICES_BATCH_SERVICE_H
#define IMPROC_SERVICES_BATCH_SERVICE_H

#ifdef WITH_DEBUG
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <spdlog/spdlog.h>
#endif

#include <improc/improc_defs.h>
#include <improc/exception.h>
#include <improc/services/base_service.h>
#include <improc/services/factory.h>
#include <improc/infrastructure/file.h>

#include <json/json.h>
#include <vector>

namespace improc
{
    template <typename key_type>
    class IMPROC_EXPORTS BatchService
    {
        private:
            std::vector<std::shared_ptr<BaseService<key_type>>> data_;

        public:
            BatchService();

            std::shared_ptr<BaseService<key_type>>& operator[]  (const size_t& index);

            void    Load   ( const ServicesFactory<key_type>& factory
                           , const Json::Value& batch_service_json );
            void    Run    ( improc::Context<key_type>& context ) const;

            size_t  Size() const;
    };

    typedef BatchService<std::string>   StringKeyBatchService;
}

#endif