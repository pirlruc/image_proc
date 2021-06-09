#include <improc/services/container.h>
#include <container.cpp>

#include <improc/services/base_service.h>
#include <improc/services/factory.h>
#include <improc/services/context.h>
#include <base_service.cpp>
#include <factory.cpp>
#include <context.cpp>

#include <iostream>
#include <cassert>
#include <cstdint>

#include <functional>
class Test
{
    int number_;

    public:
        Test();
        Test(int number);
        void load(int number);
        Test loadT(int number);
        void display();
};

Test::Test(int number)
{
    this->number_ = number;
}

void Test::load(int number) 
{
    this->number_ = number;
}

Test Test::loadT(int number) 
{
    this->number_ += number;
    return *this;
}

void Test::display()
{
    std::cout << this->number_ + 1 << std::endl;
}

typedef improc::BaseService<std::string>    StringBaseService;
typedef improc::Context<std::string>        StringContext;
class Service : public StringBaseService
{
    private:
        int test_ = 0;

    public:
        Service() : StringBaseService() {}
        void    Load   (const Json::Value&          service_json) 
        {
            this->test_ = 1;
        }

        void    Run    (StringContext&  context)
        {
            context.Add("teste_1",1);
        }

        void Print() 
        {
            std::cout << this->test_ << std::endl;
        }
};

class Service2 : public StringBaseService
{
    private:
        int test_ = 0;

    public:
        Service2() : StringBaseService() {}
        void    Load   (const Json::Value&          service_json) 
        {
            this->test_ = 2;
        }

        void    Run    (StringContext&  context)
        {
            context.Add("teste_2",2);
        }

        void Print() 
        {
            std::cout << this->test_ << std::endl;
        }
};

int main()
{
    // CONTAINER TESTS
    improc::Container<int> cntx {};
    cntx.Add(1,"Test 1");
    std::cout << cntx.Size() << std::endl;
    // cntx.Add(1,"Teste 2");
    cntx.Add(2,45);
    std::cout << cntx.Size() << std::endl;
    // cntx.Get(3);
    assert(cntx.Get(1).type() == typeid(const char*));
    assert(cntx.Get(2).type() == typeid(int));
    std::cout << cntx.Get(1).type().name() << ": " << std::any_cast<const char*>(cntx.Get(1)) << std::endl;
    std::cout << cntx.Get(2).type().name() << ": " << std::any_cast<int>(cntx.Get(2)) << std::endl;

    cntx.Erase(3);
    std::cout << cntx.Size() << std::endl;
    cntx.Erase(1);
    std::cout << cntx.Size() << std::endl;

    cntx.Clear();
    std::cout << cntx.Size() << std::endl;

    // FACTORY TESTS
    improc::ServicesFactory<std::string> factory;
    factory.Add("test_service_1",Service());
    // factory.Add("test_service_1",serv1);
    factory.Add("test_service_2",Service());
    // factory.Get("test_service_3");
    factory.Add("test_service_3",Service2());
    std::cout << "Default values..." << std::endl;
 
    StringContext context;
    Service service1 = std::any_cast<Service>(factory.Get("test_service_1"));
    Json::Value test_json;
    service1.Load(test_json);
    service1.Run(context);
    std::cout << "Service 1 -> "  << std::any_cast<int>(context.Get("teste_1")) << std::endl;
    std::cout << "In Factory" << std::endl;
    std::any_cast<Service>(factory.Get("test_service_1")).Print();
    std::cout << "In Service" << std::endl;
    service1.Print();

    std::cout << "Service 1:" << factory.Get("test_service_1").type().name() << std::endl;
    std::cout << "Service 2:" << factory.Get("test_service_3").type().name() << std::endl;

    Service2 service2 = std::any_cast<Service2>(factory.Get("test_service_3"));
    service2.Load(test_json);
    service2.Run(context);
    std::cout << "Service 2 -> "  << std::any_cast<int>(context.Get("teste_2")) << std::endl;
    std::cout << "In Factory" << std::endl;
    std::any_cast<Service2>(factory.Get("test_service_3")).Print();
    std::cout << "In Service" << std::endl;
    service2.Print();
 
    // SERVICES USING FUNCTION HANDLES
    std::cout << "SERVICES" << std::endl;
    std::function<void(Test& test, int)> test_const1 = &Test::load;
    Test test_1 = Test(40);
    test_const1(test_1,30);
    test_1.display();

    using std::placeholders::_1;
    std::function<Test(int)> test_const2 = std::bind(&Test::loadT,test_1,_1);
    Test test_2 = test_const2(35);
    test_1.display();
    test_2.display();
    return 0;
}