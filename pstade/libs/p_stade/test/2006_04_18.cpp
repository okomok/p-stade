#include <pstade/vodka/begin.hpp>
#include <boost/test/minimal.hpp>


#include <boost/utility/result_of.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <pstade/wine.hpp>


#include <iostream>
#include <string>


template< class T >
struct customization;

struct hello_tag { };


template< class Hello >
struct hello_result :
    boost::result_of<customization<Hello>(hello_tag)>
{ };


template< class Hello >
typename hello_result<Hello>::type hello(Hello h)
{
    return customization<Hello>()(h, hello_tag());
}


// a customization
//

struct my_hello { };

template< >
struct customization<my_hello>
{
    template< class >
    struct result;

    template< class MyHello >
    struct result<MyHello(hello_tag)>
    {
        typedef std::string type;
    };

    template< class MyHello >
    std::string operator()(MyHello, hello_tag)
    {
        return "hello";
    }
};


/////////////////////////////////////////////////////////////////////////////////
//


namespace pstade {


class hello_access
{
public:
    template< class T > static
    void detail_call(T& x)
    {
        return x.pstade_hello();
    }
};


namespace hello_detail {


    PSTADE_HAS_TYPE(pstade_helloable)


    struct member_function
    {
        template< class T > static
        void call(T& x)
        {
            return hello_access::detail_call(x);
        }
    };


    template< class T > inline
    void pstade_hello(T& x)
    {
        pstade_hello(x, pstade::overload());
    }

    struct adl_customization
    {
        template< class T > static
        void call(T& x)
        {
            return pstade_hello(x);
        }
    };


} // namespace hello_detail


template< class Helloable > inline
void hello(Helloable& h)
{
    typedef typename
    boost::mpl::if_< hello_detail::has_pstade_helloable<Helloable>,
        hello_detail::member_function,
        hello_detail::adl_customization
    >::type impl_t;

    return impl_t::call(h);
}


} // namespace pstade


// user customizations
//

// intrusive way
//
struct X
{
    typedef X pstade_helloable;

private:
    friend class pstade::hello_access;

    void pstade_hello()
    {
        std::cout << "X\n";
    }
};

// class hierarchy
//
struct Base { };
struct Derived : Base { };

inline void pstade_hello(Base&, pstade::overload)
{
    std::cout << "Base or Derived\n";
};

// type set
//
struct A { };
namespace Bs { struct B { }; }
struct C { };
namespace Ds
{
    struct D { };

    inline void pstade_hello(D& d)
    {
        std::cout << "D\n";
    }
}

template< class T >
struct is_ABCD :
    boost::mpl::or_<
        boost::is_same<T, A>,
        boost::is_same<T, Bs::B>,
        boost::is_same<T, C>,
        boost::is_same<T, Ds::D>
    >
{ };

template< class T >
typename boost::enable_if< is_ABCD<T>, void >::type
pstade_hello(T& x, pstade::overload)
{
    std::cout << "A, B, C, or D\n";
}

inline void pstade_hello(A& a, pstade::overload)
{
    std::cout << "A\n";
}


void test()
{
    X x;
    Base base;
    Derived derived;
    A a;
    Bs::B b;
    C c;
    Ds::D d;

    pstade::hello(x);           // X
    pstade::hello(base);        // Base or Derived
    pstade::hello(derived);     // Base or Derived
    pstade::hello(a);           // A
    pstade::hello(b);           // A, B, C, or D
    pstade::hello(c);           // A, B, C, or D
    pstade::hello(d);           // D
}


void test1()
{
    my_hello h;
    hello(h);
}


int test_main(int, char*[])
{
    ::test();
    ::test1();
    return 0;
}
