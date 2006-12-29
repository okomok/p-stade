#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/lambda_result.hpp>


#include <vector>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <pstade/functional.hpp>
#include <pstade/lambda_placeholders.hpp>


template< class Iterator, class Function >
typename boost::result_of<Function(typename boost::iterator_reference<Iterator>::type)>::type
foo(Iterator it, Function fun)
{ return fun(*it); }


void test()
{
    using namespace pstade;
    namespace lambda = boost::lambda;

    {
        int i = 12;
        boost::result_of<op_lambda_1(int)>::type result = lambda::_1(i);
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
                    boost::result_of<pstade::op_identity(int)>::type
                >(identity, lambda::_1)
            )
       );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
