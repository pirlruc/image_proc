#ifndef IMPROC_SERVICES_CONTEXT_H
#define IMPROC_SERVICES_CONTEXT_H

#include <improc/improc_defs.h>
#include <improc/services/container.h>

#include <spdlog/spdlog.h>

#include <string>
namespace improc
{
    template <typename key_type>
    class IMPROC_EXPORTS Context : public Container<key_type,std::any>
    {
        public:
            Context();
    };

    typedef Context<std::string>    StringKeyContext;
}

#include <context.tpp>

#endif