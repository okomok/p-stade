
#include <boost/bind.hpp>
#include <boost/mem_fn.hpp>




template<class F>
void check_default_c(F f)
{
    F f_;
};

template<class F>
void check_assignable(F f)
{
    F f_ = f;
    f_ = f;
};

struct A
{
    void foo(int) const {};
};

int main()
{
    A a;
    boost::bind(&A::foo, &a, 1);
    boost::mem_fn(&A::foo);
    ::check_default_c(boost::mem_fn(&A::foo));
//    ::check_default_c(boost::bind(&A::foo, &a, 1));
    ::check_assignable(boost::bind(&A::foo, &a, 1));
    ::check_assignable(boost::mem_fn(&A::foo));
}

