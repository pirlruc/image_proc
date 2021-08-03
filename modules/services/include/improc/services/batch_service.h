#ifndef IMPROC_SERVICES_BATCH_SERVICE_H
#define IMPROC_SERVICES_BATCH_SERVICE_H

#include <improc/improc_defs.h>
#include <improc/exception.h>
#include <improc/services/logger_services.h>
#include <improc/services/base_service.h>
#include <improc/services/factory.h>
#include <improc/infrastructure/file.h>
#include <improc/infrastructure/jsonfile_parser.h>

#include <json/json.h>
#include <vector>

namespace improc
{
    template <typename key_type>
    class IMPROC_EXPORTS BatchService
    {
        private:
            struct Service
            {
                key_type                                type;
                std::shared_ptr<BaseService<key_type>>  data;
            };

            std::vector<Service>                        data_;

        public:
            BatchService();

            void    Load   ( const ServicesFactory<key_type>& factory
                           , const Json::Value& batch_service_json );
            void    Run    ( improc::Context<key_type>& context ) const;

            size_t  Size() const;
    };

    typedef BatchService<std::string>   StringKeyBatchService;
}

#include <batch_service.tpp>

#endif