#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/adapted_to_base.hpp>


#include <string>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>
#include <pstade/is_same.hpp>
#include <pstade/oven/algorithm.hpp>
#include <pstade/oven/filtered.hpp>
#include <pstade/oven/sub_range.hpp>
#include <pstade/oven/equals.hpp>
#include <pstade/oven/regular.hpp>
#include <pstade/oven/identities.hpp>


#include <pstade/minimal_test.hpp>


void test_()
{
    namespace lambda = boost::lambda;
    namespace oven = pstade::oven;  
    using namespace oven;

    {// as is.
        std::string src("abc");
        typedef std::string::iterator iter_t;
        iter_t a = boost::begin(src);

        {
            // rvalue
            BOOST_CHECK(a == oven::adapted_to<iter_t>(boost::begin(src)));
            iter_t it = boost::begin(src)|to_base;
            BOOST_CHECK(a == it);
        }
        {
            // lvalue
            iter_t it = boost::begin(src);
            BOOST_CHECK(a == oven::adapted_to<iter_t>(it));
            iter_t it_ = it|to_base;
            BOOST_CHECK(a == it_);
        }
        {
            // const-lvalue
            iter_t const it = boost::begin(src);
            BOOST_CHECK(a == oven::adapted_to<iter_t>(it));
            iter_t it_ = it|to_base;
            BOOST_CHECK(a == it_);
        }
    }
    {
        std::string src("cjaigzenqhe");
        std::string::iterator it = max_element(src)|to_base;
        BOOST_CHECK( *it == 'z' );
    }

    {
        std::string src("cjaigzenqhe");
        std::string::const_iterator it = max_element(src)|to_base;
        BOOST_CHECK( *it == 'z' );
    }

    {
        std::string src("cjaigvwzenqhe");
        std::string::iterator it = oven::adapted_to<std::string::iterator>(
            max_element(
                src
                    | filtered(regular(lambda::_1 != 'z'))
                    | filtered(regular(lambda::_1 != 'w'))
            )
        );

        BOOST_CHECK( *it == 'v' );
    }

    {
        std::string src("cjaigvwzenqhe");
        std::string::const_iterator it =
            max_element(
                src
                    | filtered(regular(lambda::_1 != 'z'))
                    | filtered(regular(lambda::_1 != 'w'))
            )|to_base;

        BOOST_CHECK( *it == 'v' );
    }

    // range version
    {
        std::string src("cjaigvwzenqhe");
        std::string dst = src
                    | filtered(regular(lambda::_1 != 'z'))
                    | filtered(regular(lambda::_1 != 'w'))
                    | to_base_range;
        BOOST_CHECK( equals(src, dst) );

        dst = adapted_range_to<std::string>(src
                    | filtered(regular(lambda::_1 != 'z'))
                    | filtered(regular(lambda::_1 != 'w'))
              );
        BOOST_CHECK( equals(src, dst) );
    }
    {
        std::string src("jioyhaogihehiqgnqongeqongoq");
        sub_range<std::string> rng = src|identities|identities|identities|to_base_range;
        BOOST_CHECK( equals(src, rng) );
        rng = adapted_range_to< sub_range<std::string> >(src|identities|identities|identities);
        BOOST_CHECK( equals(src, rng) );
    }
    {
        std::string src("cjaigvwzenqhe");
        sub_range<std::string> dst = src
                    | filtered(regular(lambda::_1 != 'z'))
                    | filtered(regular(lambda::_1 != 'w'))
                    | to_base_range;
        BOOST_CHECK( equals(src, dst) );

        sub_range<std::string const> cdst = src
                    | filtered(regular(lambda::_1 != 'z'))
                    | filtered(regular(lambda::_1 != 'w'))
                    | to_base_range;
        BOOST_CHECK( equals(src, cdst) );
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
    namespace oven = pstade::oven;
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


void pstade_minimal_test()
{
    ::test_();
    ::test_general();
}
