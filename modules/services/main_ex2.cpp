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
            context.Add("ori-1",std::any_cast<int>(context.Get("ori")) + 1);
        }
};

class Subtract : public improc::StringKeyBaseService
{
    public:
        Subtract() : improc::StringKeyBaseService() {}
        void    Load   (const Json::Value& service_json) 
        {
            this->inputs_.push_back("ori-2");
            this->inputs_.push_back("ori-1");
        }

        void    Run    (improc::StringKeyContext&  context)
        {
            context["ori"] = std::any_cast<int>(context.Get("ori-2")) - std::any_cast<int>(context.Get("ori-1"));
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
            context.Add("ori-2",std::any_cast<int>(context.Get("ori")) * this->number_to_multiply_);
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
    Multiply  multiply  {};
    Subtract  subtract  {};
    increment.Load(dummy);
    multiply.Load(dummy);
    subtract.Load(dummy);

    increment.Run(cntxt);
    std::cout << "Increment, ori   = " << std::any_cast<int>(cntxt.Get("ori")) << std::endl;
    std::cout << "Increment, ori-1 = " << std::any_cast<int>(cntxt.Get("ori-1")) << std::endl;

    multiply.Run(cntxt);
    std::cout << "Multiply, ori   = " << std::any_cast<int>(cntxt.Get("ori")) << std::endl;
    std::cout << "Multiply, ori-2 = " << std::any_cast<int>(cntxt.Get("ori-2")) << std::endl;

    subtract.Run(cntxt);
    std::cout << "Subtract, ori   = " << std::any_cast<int>(cntxt.Get("ori")) << std::endl;
    std::cout << "Subtract, ori-2 = " << std::any_cast<int>(cntxt.Get("ori-2")) << std::endl;
    std::cout << "Subtract, ori-1 = " << std::any_cast<int>(cntxt.Get("ori-1")) << std::endl;
    return 0;
}