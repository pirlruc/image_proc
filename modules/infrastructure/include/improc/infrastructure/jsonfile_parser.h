#ifndef IMPROC_INFRASTRUCTURE_JSONFILE_PARSER_H
#define IMPROC_INFRASTRUCTURE_JSONFILE_PARSER_H

#include <improc/improc_defs.h>

#include <json/json.h>

namespace improc {
    // The namespace is just to avoid having warnings related with static template methods in the class JsonFile
    namespace jsonfile
    {
        template<typename key_type>
        IMPROC_EXPORTS key_type             ReadElement(const Json::Value& json_elem);

        template<>
        IMPROC_EXPORTS inline std::string   ReadElement(const Json::Value& json_elem);
    }
}

#include <jsonfile_parser.tpp>

#endif
