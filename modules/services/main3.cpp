#include <iostream>
#include <vector>

class Base
{
    protected:
        int data_;
        double output;

    public:
        Base();
        int get_data();
        virtual double run();
        virtual double get_output();
};

Base::Base() : data_(0) {}

int Base::get_data()
{
    return this->data_;
}

double Base::run()
{
    this->output = 0;
    return this->output;
}

double Base::get_output()
{
    return this->output;
}

class A : public Base
{
    private:
        int data2_;
        double output2;

    public:
        A();
        double run() override;
        double get_output() override;
};

A::A() : Base() 
{
    this-> data_  = 1;
    this-> data2_ = 3;
}

double A::run()
{
    this->output2 = this->data_ * this->data2_; 
    return this->output2;
}

double A::get_output()
{
    return this->output2;
}

class B : public Base
{
    private:
        int data3_;
        double output3;

    public:
        B();
        double run() override;
        double get_output() override;
};

B::B() : Base() 
{
    this-> data_ = 2;
    this->data3_ = 11;
}

double B::run()
{
    this->output3 = this->data_ * this->data3_; 
    return this->output3;
}

double B::get_output()
{
    return this->output3;
}

class BaseSet
{
    private:
        std::vector<Base*> base_set;

    public:
        BaseSet() {}
        void Add(Base* base_ptr) 
        {
            this->base_set.push_back(base_ptr);
        }
        
        Base* Get(size_t idx)
        {
            return this->base_set[idx];
        }

        size_t size() 
        {
            return this->base_set.size();
        }
};

int main()
{
    std::cout << "A" << std::endl;
    std::vector<Base*> base_vec;
    Base base   = Base();
    A    base_a = A();
    B    base_b = B();
    base_vec.push_back(&base);
    base_vec.push_back(&base_a); 
    base_vec.push_back(&base_b);

    std::cout << "B" << std::endl;
    for (size_t idx = 0; idx < base_vec.size(); idx++)
    {
        std::cout << "Index: "  << idx 
                  << "; Data: " << base_vec[idx]->get_data() 
                  << "; Run: "  << base_vec[idx]->run() << std::endl;
    } 
    std::cout << "C" << std::endl;

    for (size_t idx = 0; idx < base_vec.size(); idx++)
    {
        std::cout << "Index: "  << idx 
                  << "; Output: " << base_vec[idx]->get_output() << std::endl;
    } 
    std::cout << "D" << std::endl;

    BaseSet set;
    set.Add(&base);
    set.Add(&base_a);
    set.Add(&base_b);

    std::cout << "E" << std::endl;
    for (size_t idx = 0; idx < set.size(); idx++)
    {
        std::cout << "Index: "  << idx 
                  << "; Data: " << set.Get(idx)->get_data() 
                  << "; Run: "  << set.Get(idx)->run() << std::endl;
    } 
    std::cout << "F" << std::endl;

    for (size_t idx = 0; idx < set.size(); idx++)
    {
        std::cout << "Index: "  << idx 
                  << "; Output: " << set.Get(idx)->get_output() << std::endl;
    } 
    std::cout << "G" << std::endl;
    return 0;
}