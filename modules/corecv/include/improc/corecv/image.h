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
            cv::UMat                    data_;

        public:
            Image();
            Image(const cv::UMat& image_data);

            void                        set_data(const cv::UMat& image_data);
            cv::UMat                    get_data();
            Image                       clone();
    }
}

#endif