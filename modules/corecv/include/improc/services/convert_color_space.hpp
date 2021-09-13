#ifndef IMPROC_SERVICES_CONVERT_COLOR_SPACE_HPP
#define IMPROC_SERVICES_CONVERT_COLOR_SPACE_HPP

#include <improc/improc_defs.hpp>
#include <improc/corecv/logger_improc.hpp>
#include <improc/corecv/color_space.hpp>
#include <improc/corecv/image.hpp>
#include <servproc/services/base_service.hpp>

namespace improc {
    template <typename key_type>
    class IMPROC_EXPORTS ConvertColorSpace : public servproc::BaseService<key_type>
    {
        private:
            static constexpr unsigned int   kImageDataKeyIndex  = 0;
            static constexpr unsigned int   kColorSpaceKeyIndex = 1;
            
            std::optional<ColorSpace>       from_color_space_;
            std::vector<ColorSpace>         to_color_space_;

        public:
            ConvertColorSpace();

            void                            Load(const Json::Value& convert_color_space_json)   override;
            void                            Run (servproc::Context<key_type>& context) const    override;
    };

    typedef ConvertColorSpace<std::string>    StringKeyConvertColorSpace;
}

#include <convert_color_space.tpp>

#endif