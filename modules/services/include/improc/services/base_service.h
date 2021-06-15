#ifndef IMPROC_SERVICES_BASE_SERVICE_H
#define IMPROC_SERVICES_BASE_SERVICE_H

#ifdef WITH_DEBUG
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <spdlog/spdlog.h>
#endif

#include <improc/improc_defs.h>
#include <improc/exception.h>
#include <improc/services/context.h>

#include <json/json.h>

#include <vector>

namespace improc{
    template <typename key_type>
    class IMPROC_EXPORTS BaseService
    {
        protected:
            std::vector<key_type>   inputs_;
            std::vector<key_type>   outputs_;

        public:
            BaseService();

            virtual void        Load            (const Json::Value& service_json);
            virtual void        Run             (Context<key_type>& context)    = 0;

        protected:
            virtual key_type    ReadKeyFromJson (const Json::Value& field_json) = 0;
    };

    class IMPROC_EXPORTS StringKeyBaseService : public BaseService<std::string>
    {
        public:
            StringKeyBaseService();

        private:
            std::string         ReadKeyFromJson (const Json::Value& field_json);
    };
}

#endif
