#ifndef IMPROC_CORECV_IMAGE_H
#define IMPROC_CORECV_IMAGE_H

#include <improc/improc_defs.h>
#include <improc/exception.h>
#include <improc/corecv/logger_improc.h>

#include <opencv2/core.hpp>

namespace improc {
    class IMPROC_EXPORTS Image
    {
        private:
            cv::Mat                     data_;

        public:
            Image();
            Image(const cv::Mat& image_data);

            void                        set_data(const cv::Mat& image_data);
            cv::Mat                     get_data();
            Image                       clone();
    };
}

#endif