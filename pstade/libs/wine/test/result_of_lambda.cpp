#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/result_of_lambda.hpp>
#include <boost/test/minimal.hpp>


#include <vector>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <pstade/egg/identity.hpp>
#include <pstade/egg/lambda/placeholders.hpp>
#include <pstade/result_of.hpp>


template< class Iterator, class Function >
typename pstade::result_of<Function(typename boost::iterator_reference<Iterator>::type)>::type
foo(Iterator it, Function fun)
{ return fun(*it); }


void test()
{
    using namespace pstade;
    namespace lambda = boost::lambda;

    {
        int i = 12;
        pstade::result_of<egg::T_lambda_1(int)>::type result = lambda::_1(i);
        BOOST_CHECK(result == 12);
    }
    {
        std::vector<int> v;
        v.push_back(5);
        BOOST_CHECK( ::foo(v.begin(), lambda::_1) == 5 );
        BOOST_CHECK( ::foo(v.begin(), lambda::_1 * 2) == 10 );
        BOOST_CHECK( 5 ==
            ::foo(
                v.begin(),
                lambda::bind<
                    pstade::result_of<egg::T_identity(int)>::type
                >(egg::identity, lambda::_1)
            )
       );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
