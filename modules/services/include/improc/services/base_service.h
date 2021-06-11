#ifndef IMPROC_SERVICES_BASE_SERVICE_H
#define IMPROC_SERVICES_BASE_SERVICE_H

#ifdef WITH_DEBUG
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <spdlog/spdlog.h>
#endif

#include <improc/improc_defs.h>
#include <improc/services/context.h>

#include <json/json.h>

#include <vector>

namespace improc{
    template <typename key_type>
    class IMPROC_EXPORTS BaseService
    {
        protected:
            std::vector<key_type> inputs_;

        public:
            BaseService();

            virtual void Load   (const Json::Value& service_json)       = 0;
            virtual void Run    (improc::Context<key_type>& context)    = 0;
    };

    typedef BaseService<std::string>    StringKeyBaseService;
}

#endif
