#ifndef IMPROC_SERVICES_CONTEXT_H
#define IMPROC_SERVICES_CONTEXT_H

#ifdef WITH_DEBUG
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <spdlog/spdlog.h>
#endif

#include <improc/improc_defs.h>
#include <improc/services/container.h>

namespace improc
{
    template <typename key_type>
    class IMPROC_EXPORTS Context : public Container<key_type>
    {
        public:
            Context();
    };

    typedef Context<std::string>  StringKeyContext;
}

#endif