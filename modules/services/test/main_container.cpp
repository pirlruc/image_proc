#define WITH_DEBUG

#include <improc/services/container.h>
#include <container.cpp>

#include <iostream>
#include <cassert>

int main()
{
    // CONTAINER TESTS
    improc::Container<int,std::any> cntx {};
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
    return 0;
}