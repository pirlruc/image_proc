#ifndef IMPROC_SERVICES_CONTAINER_H
#define IMPROC_SERVICES_CONTAINER_H

#ifdef WITH_DEBUG
#include <spdlog/spdlog.h>
#endif

#include <improc/exception.h>

#include <unordered_map>
#include <any>
#include <string>

namespace improc
{
    template <typename key_type,typename container_type>
    class Container
    {
        private:
            std::unordered_map<key_type,container_type> hash_table_;

        public:
            Container();

            void            Add         (const key_type& key, const container_type& item);
            container_type  Get         (const key_type& key) const;
            container_type& operator[]  (const key_type& key);

            void            Erase       (const key_type& key);
            void            Clear();

            size_t          Size() const;
    };

    typedef Container<std::string,std::any> StringKeyHeterogeneousContainer;
}

#include <container.tpp>

#endif