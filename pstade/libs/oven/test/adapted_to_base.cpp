#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/adapted_to_base.hpp>


#include <string>
#include <boost/range.hpp>
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>
#include <pstade/is_same.hpp>
#include <pstade/oven/filtered.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/regularized.hpp>


void test()
{
    using namespace pstade;   
    using namespace oven;

    {
        std::string src("cjaigzenqhe");
        std::string::iterator it = oven::max_element(src)|to_base;
        BOOST_CHECK( *it == 'z' );
    }

    {
        std::string src("cjaigzenqhe");
        std::string::const_iterator it = oven::max_element(src)|to_base;
        BOOST_CHECK( *it == 'z' );
    }

    {
        using namespace boost;
        std::string src("cjaigvwzenqhe");
        std::string::iterator it = oven::adapted_to<std::string::iterator>(
            oven::max_element(
                src
                    | filtered(lambda::_1 != 'z')
                    | regularized
                    | filtered(lambda::_1 != 'w')
                    | regularized
            )
        );

        BOOST_CHECK( *it == 'v' );
    }

    {
        using namespace boost;
        std::string src("cjaigvwzenqhe");
        std::string::const_iterator it =
            oven::max_element(
                src
                    | filtered(lambda::_1 != 'z')
                    | regularized
                    | filtered(lambda::_1 != 'w')
                    | regularized
            )|to_base;

        BOOST_CHECK( *it == 'v' );
    }
}



template< class T >
struct ret_ref
{
    explicit ret_ref(T& x) :
        m_x(x)
    { }

    T& base() const
    {
        return m_x;
    }

private:
    T& m_x;
};

template< class T >
ret_ref<T> make_ret_ref(T& x)
{
    return ret_ref<T>(x);
}


template< class T >
struct ret_cref
{
    explicit ret_cref(T const& x) :
        m_x(x)
    { }

    T const& base() const
    {
        return m_x;
    }

private:
    T const& m_x;
};

template< class T >
ret_cref<T> make_ret_cref(T const& x)
{
    return ret_cref<T>(x);
}


template< class T >
struct ret_val
{
    explicit ret_val(T const& x) :
        m_x(x)
    { }

    T base() const
    {
        return m_x;
    }

private:
    T m_x;
};

template< class T >
ret_val<T> make_ret_val(T const& x)
{
    return ret_val<T>(x);
}


void test_general()
{
    using namespace pstade;   
    using namespace oven;

    {
        int j = 2;
        int i = oven::adapted_to<int>( ::make_ret_cref(::make_ret_ref(j)) );
        int k = ::make_ret_cref(::make_ret_ref(j))|to_base;
        BOOST_CHECK( i == j && i == 2 && i == k );
    }
    { // as is.
        int j = 2;
        int& i = oven::adapted_to<int&>(j);
        BOOST_CHECK( pstade::is_same(i, j) );
    }
}

int test_main(int, char*[])
{
    ::test();
    ::test_general();
    return 0;
}
