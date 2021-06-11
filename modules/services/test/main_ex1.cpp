#include <improc/services/context.h>
#include <improc/services/base_service.h>

#include <container.cpp>
#include <context.cpp>
#include <base_service.cpp>

#include <iostream>

class Increment : public improc::StringKeyBaseService
{
    public:
        Increment() : improc::StringKeyBaseService() {}
        void    Load   (const Json::Value& service_json) 
        {
            this->inputs_.push_back("ori");
        }

        void    Run    (improc::StringKeyContext&  context)
        {
            context["ori"] = std::any_cast<int>(context.Get("ori")) + 1;
        }
};

class Subtract : public improc::StringKeyBaseService
{
    private: 
        int number_to_subtract_ = 0;

    public:
        Subtract() : improc::StringKeyBaseService() {}
        void    Load   (const Json::Value& service_json) 
        {
            this->number_to_subtract_ = 2;
            this->inputs_.push_back("ori");
        }

        void    Run    (improc::StringKeyContext&  context)
        {
            context["ori"] = std::any_cast<int>(context.Get("ori")) - this->number_to_subtract_;
        }
};

class Multiply : public improc::StringKeyBaseService
{
    private: 
        int number_to_multiply_ = 1;

    public:
        Multiply() : improc::StringKeyBaseService() {}
        void    Load   (const Json::Value& service_json) 
        {
            this->number_to_multiply_ = 3;
            this->inputs_.push_back("ori");
        }

        void    Run    (improc::StringKeyContext&  context)
        {
            context["ori"] = std::any_cast<int>(context.Get("ori")) * this->number_to_multiply_;
        }
};

int main()
{
    Json::Value dummy {};
    std::cout << "--- PROTOTYPE BEGINNING ---" << std::endl;

    improc::StringKeyContext cntxt {};
    cntxt.Add("ori",2);
    std::cout << "Start, ori = " << std::any_cast<int>(cntxt.Get("ori")) << std::endl;

    Increment increment {};
    Subtract  subtract  {};
    Multiply  multiply  {};
    increment.Load(dummy);
    subtract.Load(dummy);
    multiply.Load(dummy);

    increment.Run(cntxt);
    std::cout << "Increment, ori = " << std::any_cast<int>(cntxt.Get("ori")) << std::endl;

    subtract.Run(cntxt);
    std::cout << "Subtract, ori = " << std::any_cast<int>(cntxt.Get("ori")) << std::endl;

    multiply.Run(cntxt);
    std::cout << "Multiply, ori = " << std::any_cast<int>(cntxt.Get("ori")) << std::endl;

    increment.Run(cntxt);
    std::cout << "Increment, ori = " << std::any_cast<int>(cntxt.Get("ori")) << std::endl;
    return 0;
}