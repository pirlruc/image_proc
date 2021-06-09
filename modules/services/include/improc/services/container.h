#ifndef IMPROC_SERVICES_CONTAINER_H
#define IMPROC_SERVICES_CONTAINER_H

#ifdef WITH_DEBUG
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <spdlog/spdlog.h>
#endif

#include <improc/services/exception.h>

#include <unordered_map>
#include <any>

namespace improc
{
    template <typename key_type>
    class Container
    {
        private:
            std::unordered_map<key_type,std::any> hash_table_;

        public:
            Container();

            std::any&   operator[]  (const key_type& key);

            void        Add         (const key_type& key, const std::any& item);
            std::any    Get         (const key_type& key);

            void        Erase       (const key_type& key);
            void        Clear();

            size_t      Size() const;
    };

    typedef Container<std::string>  StringKeyContainer;
}

#endif