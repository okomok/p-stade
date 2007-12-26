#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if !defined(PSTADE_EGG_TEST_NUMBER)
#error Please define PSTADE_EGG_TEST_NUMBER.
#endif

#if PSTADE_EGG_TEST_NUMBER == 1
#include <pstade/egg/by_perfect/by_perfect1.hpp>
#elif PSTADE_EGG_TEST_NUMBER == 2
#include <pstade/egg/by_perfect/by_perfect2.hpp>
#elif PSTADE_EGG_TEST_NUMBER == 3
#include <pstade/egg/by_perfect/by_perfect3.hpp>
#elif PSTADE_EGG_TEST_NUMBER == 4
#include <pstade/egg/by_perfect/by_perfect4.hpp>
#elif PSTADE_EGG_TEST_NUMBER == 5
#include <pstade/egg/by_perfect/by_perfect5.hpp>
#else
#error PSTADE_EGG_TEST_NUMBER is too large.
#endif


#include <pstade/lightweight_test.hpp>


#include <pstade/result_of.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/assert.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/unused.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>


struct baby_my_first
{
    template<class Myself, BOOST_PP_ENUM_PARAMS(PSTADE_EGG_TEST_NUMBER, class A)>
    struct apply
    {
        typedef A0 &type;
    };

    template<class Result, BOOST_PP_ENUM_PARAMS(PSTADE_EGG_TEST_NUMBER, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(PSTADE_EGG_TEST_NUMBER, A, & a)) const
    {
        return a0;
    }
};

typedef pstade::egg::function<baby_my_first, BOOST_PP_CAT(pstade::egg::by_perfect, PSTADE_EGG_TEST_NUMBER)> T_my_first;
PSTADE_POD_CONSTANT((T_my_first), my_first) = {{}};


#define PSTADE_trailing_params_n BOOST_PP_DEC(PSTADE_EGG_TEST_NUMBER)
#define PSTADE_trailing_params BOOST_PP_ENUM_TRAILING_PARAMS(PSTADE_trailing_params_n, int BOOST_PP_INTERCEPT)

BOOST_MPL_ASSERT((boost::is_same<pstade::result_of<T_my_first(int         PSTADE_trailing_params)>::type, int const &>));
BOOST_MPL_ASSERT((boost::is_same<pstade::result_of<T_my_first(int &       PSTADE_trailing_params)>::type, int &      >));
BOOST_MPL_ASSERT((boost::is_same<pstade::result_of<T_my_first(int const & PSTADE_trailing_params)>::type, int const &>));


void pstade_lightweight_test()
{
    {
        int i = 10;
        pstade::result_of<T_my_first(int & PSTADE_trailing_params)>::type a
            = my_first(i BOOST_PP_ENUM_TRAILING_PARAMS(PSTADE_trailing_params_n, 999 BOOST_PP_INTERCEPT));
        BOOST_CHECK(&i == &a);
        BOOST_CHECK(a == 10);
    }
}
