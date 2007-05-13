#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/lambda_sig.hpp>


#include <string>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>


struct chat_monchy
    : pstade::lambda_sig
{
    template< class Sig >
    struct result;

    template< class F >
    struct result<F(int&)>
    {
        typedef int& type;
    };

    int& operator()(int& i) const
    {
        return i;
    }

    template< class F >
    struct result<F(std::string&, double&)>
    {
        typedef std::string& type;
    };

    std::string& operator()(std::string& s, double&) const
    {
        return s;
    }
};


void test()
{
    using namespace pstade;
    namespace lambda = boost::lambda;

    {
        int i = 12;
        BOOST_CHECK( i ==
            lambda::bind(chat_monchy(), lambda::_1)(i)
        );
    }
    {
        std::string s("hello");
        double d = 12;
        BOOST_CHECK( s ==
            lambda::bind(chat_monchy(), lambda::_1, lambda::_2)(s, d)
        );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
