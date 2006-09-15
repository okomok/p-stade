#if 0

#include <pstade/../libs/oven/test/to_counter.cpp>
//#include <pstade/../libs/oven/test/to_stream.cpp>
//#include <pstade/../libs/biscuit/test/capture.cpp>

#else


#include <iostream>
#include <string>
#include <boost/range.hpp>
#include <boost/foreach.hpp>


struct Base
{
    Base()
    { }

    template< class T >
    Base(T const&)
    {
        BOOST_ASSERT(false);
    }
};


struct Derived : Base
{
    Derived()
    { }

/*
    // VC7.1's implicitly generated constructor
    // asserion will fail.
    Derived(Derived const& self) :
        Base(self)
    { }
*/

    // Expected implicitly generated constructor
    //
    Derived(Derived const& self) :
        Base(static_cast<Base const&>(self))
    { }

};

template< class T_ >
struct B
{
    B() { }

    template< class T >
    B(T& x) { x.error; }

    template< class T >
    B(T const& x) { x.error; }

    template< class T >
    B& operator=(T& x) { x.error; return *this; }

    template< class T >
    B& operator=(T const& x) { x.error; return *this; }
};

template< class T_ >
struct D : B<T_>
{
    D() : B<T_>() { }

    //D(const D& d) :
    //B(d) { }

    template< class T >
    D(T& x) : B<T_>(x) { }

    template< class T >
    D(T const& x) : B<T_>(x) { }

    template< class T >
    D& operator=(T& x) { B<T_>::operator=(x); return *this; }

    template< class T >
    D& operator=(T const& x) { B<T_>::operator=(x); return *this; }
};

int main()
{
    D<int> const d;
    D<int> dd(d);
    dd = d;
    /*
    std::string rng;
    boost::sub_range<std::string> const sub1(rng);
    boost::sub_range<std::string> sub2(sub1);
    sub2 = sub1;*/
}


#endif
