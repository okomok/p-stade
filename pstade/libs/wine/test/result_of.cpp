#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/utility/result_of.hpp>
#include <pstade/functional.hpp>


template< class T >
struct chat_monchy_
{
    template< class Sig >
    struct result;

    template< class F, class Array >
    struct result<F(Array&)>
    {
        typedef int type;
    };

    template< class Array >
    int operator()(Array&)
    {
        return 0;
    };

    template< class Array >
    int operator()(Array const&)
    {
        return 0;
    };
};

#if 0

    template< class T >
    struct chat_monchy : chat_monchy_<T> { };

    // Once instantiated, VC compiles 'char_monchy_',
    // but it is of course impossible to instantiate everything
    typedef boost::result_of<chat_monchy<int>(int&)>::type x_t;


#endif



struct op1
{
    template<class FunCall>
    struct result
    { }; // definition needed

    template<class Fun>
    struct result<Fun(int)>
    {
        typedef int type;
    };

    int operator()(int x) const
    {
        return x;
    }
};


struct op2
{
    template<class FunCall>
    struct result;

    template<class Fun>
    struct result<Fun(int&)>
    {
        typedef int type;
    };

    int operator()(int& x) const
    {
        return x;
    }
};


template< class F >
typename boost::result_of<F(int&)>::type
bar(F f, int x)
{
    return f(x);
};


int
bar(op1 f, int x)
{
    return f(x);
};


// const qualifier check

int a_fun(int)
{
    return 1;
}

template<class F>
struct forwarding
{
    typename boost::result_of<F (int)>::type
    operator()() const
    {
        return m_f(3);
    }

    explicit forwarding(F const& f) :
        m_f(f)
    { }

    F m_f;
};

template<class F>
forwarding<F> make_forwarding(F f)
{
    return forwarding<F>(f);
};


void test()
{

#if 0
    {
        int array[] = { 1,2,3 };
        boost::result_of<chat_monchy<int>(int (&)[3])>::type result
            = ::chat_monchy<int>()(array);

        (void)result;
    }

    {
        int const array[] = { 1,2,3 };
        boost::result_of<chat_monchy<int>(int const (&)[3])>::type result
            = ::chat_monchy<int>()(array);

        (void)result;
    }

    {
        int i = 10;
        boost::result_of<chat_monchy<int>(int&)>::type result
            = ::chat_monchy<int>()(i);

        (void)result;
    }
#endif
#if 0
    {
        int i = 10;
        boost::result_of<chat_monchy_<int>(int&)>::type result
            = ::chat_monchy_<int>()(i);

        (void)result;
    }
#endif
#if 0
    {
        ::bar(op1(), 1);
        ::bar(op2(), 1);
    }
#endif
    {
        ::make_forwarding(&a_fun)();
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
