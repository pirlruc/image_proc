#ifndef IMPROC_EXCEPTIONS_HPP
#define IMPROC_EXCEPTIONS_HPP
 
#include <exception>
 
namespace improc {
    class file_processing_error: public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Error processing file";
        }
    };

    class not_supported_data_type: public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Not supported data type";
        }
    };

    class not_supported_color_conversion: public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Not supported color conversion";
        }
    };

    class invalid_color_space: public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Invalid color space";
        }
    };
}
 
#endif