#ifndef IMPROC_SERVICES_SEQUENCE_SERVICE_H
#define IMPROC_SERVICES_SEQUENCE_SERVICE_H

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
    /**
     * @brief Define an orderered sequence of services that should be executed together
     * 
     * @tparam key_type 
     */
    template <typename key_type>
    class IMPROC_EXPORTS SequenceService
    {
        private:
            struct Service
            {
                key_type                                type;
                std::shared_ptr<BaseService<key_type>>  data;
            };

            std::vector<Service>                        data_;

        public:
            SequenceService();

            void    Load   ( const ServicesFactory<key_type>& factory
                           , const Json::Value& sequence_service_json );
            void    Run    ( improc::Context<key_type>& context ) const;

            size_t  Size() const;
    };

    typedef SequenceService<std::string>   StringKeySequenceService;
}

#include <sequence_service.tpp>

#endif