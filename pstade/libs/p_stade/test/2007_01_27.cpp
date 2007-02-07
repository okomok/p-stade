 
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <iostream>
#include <boost/noncopyable.hpp>


struct my_string :
    private boost::noncopyable
{
    my_string(char const *p) : impl(p) { }

    std::string impl;
};

std::ostream& operator<<(std::ostream& s, my_string& my)
{
    return s << my.impl.c_str();
}


int main() 
{
    namespace lambda = boost::lambda;
    using namespace lambda;
//    (std::cout << _1 << _2)("hello", 10);
    (std::cout << _1 << _2)("hello", make_const(10));

  //  my_string s("hello");
//    (std::cout << _1 << _2)(s, make_const(10));
} 
