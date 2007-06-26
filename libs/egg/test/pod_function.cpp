#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/detail/pod_function.hpp>
#include <pstade/minimal_test.hpp>


#if !defined(PSTADE_EGG_RESULT_OF_CANT_WORK_WITH_TEMPLATE_POD)


#include <pstade/test.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/core.hpp>


struct op0
{
    typedef int result_type;

    int operator()(int i) const
    {
        return i;
    }
};

typedef pstade::egg::detail::pod_function<op0> pod_op0;

PSTADE_TEST_IS_RESULT_OF((int), pod_op0(int))


void pstade_minimal_test()
{
    namespace bll = boost::lambda;

    int i = 10;
    BOOST_CHECK( bll::bind(pod_op0(), bll::_1)(i) == 10 );
}


#else

void pstade_minimal_test()
{ }

#endif
