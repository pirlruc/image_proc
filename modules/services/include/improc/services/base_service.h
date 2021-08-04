#ifndef IMPROC_SERVICES_BASE_SERVICE_H
#define IMPROC_SERVICES_BASE_SERVICE_H

#include <improc/improc_defs.h>
#include <improc/exception.h>
#include <improc/services/logger_services.h>
#include <improc/services/context.h>
#include <improc/infrastructure/file.h>
#include <improc/infrastructure/jsonfile_parser.h>

#include <json/json.h>
#include <vector>

namespace improc{
    /**
     * @brief Skeleton for base service with key_type inputs and output names.
     * 
     * @tparam key_type 
     */
    template <typename key_type>
    class IMPROC_EXPORTS BaseService
    {
        protected:
            std::vector<key_type>   inputs_;
            std::vector<key_type>   outputs_;

        public:
            BaseService();

            virtual void        Load            (const Json::Value& service_json);
            virtual void        Run             (Context<key_type>& context) const = 0;
    };

    typedef BaseService<std::string>    StringKeyBaseService;
}

#include <base_service.tpp>

#endif
