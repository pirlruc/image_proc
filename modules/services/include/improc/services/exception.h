#ifndef IMPROC_SERVICES_EXCEPTIONS_H
#define IMPROC_SERVICES_EXCEPTIONS_H
 
#include <exception>
 
namespace improc {
    class duplicated_key: public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Key already exists";
        }
    };

    class not_found_key: public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Key does not exist";
        }
    };
}
 
#endif