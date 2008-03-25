

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/preprocessor/cat3.hpp>
#include <boost/egg/preprocessor/enum_params_with.hpp>
#include <boost/egg/preprocessor/int_n.hpp>
#include <boost/egg/preprocessor/is_seq.hpp>
#include <boost/egg/preprocessor/seq_cycle.hpp>
#include <boost/egg/preprocessor/seq_enum_args.hpp>
#include <boost/egg/preprocessor/seq_enum_params.hpp>
#include <boost/egg/preprocessor/seq_params.hpp>
#include <boost/egg/preprocessor/seq_repeat.hpp>
#include "./egg_test.hpp"


#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/logical/not.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/preprocessor/debug/assert.hpp>
#include <boost/type_traits/is_same.hpp>


namespace cat3_ {

    struct abc {};
    #define A a
    #define B b
    BOOST_EGG_PP_CAT3(A, B, c) const k = {};
    #undef  B
    #undef  A

}


namespace enum_params_with_ {

    template< BOOST_PP_ENUM_PARAMS(5, class A) >
    void foo_( BOOST_EGG_PP_ENUM_PARAMS_WITH(5, A, &) )
    {
        return;
    }

    template< BOOST_PP_ENUM_PARAMS(5, class A) >
    void cfoo_( BOOST_EGG_PP_ENUM_PARAMS_WITH(5, A, const&) )
    {
        return;
    }

    void test_()
    {
        int i = 0;
        foo_(i, i, i, i, i);
        cfoo_(1, 1, 1, 1, 1);
    }

}


namespace int_n_ {

    void test_()
    {
        int i = BOOST_EGG_PP_INT_3;
        BOOST_CHECK(i == 3);
    }

}


namespace is_seq_ {

    BOOST_PP_ASSERT(BOOST_EGG_PP_IS_SEQ((1)(2)));
    BOOST_PP_ASSERT(BOOST_PP_NOT(BOOST_EGG_PP_IS_SEQ(10)));
    BOOST_PP_ASSERT(BOOST_PP_NOT(BOOST_EGG_PP_IS_SEQ(aaa)));

}


namespace seq_ {


    template< class A >
    void cyfoo( BOOST_PP_SEQ_ENUM( BOOST_EGG_PP_SEQ_CYCLE((A)(A), 3) ) )
    { }


    template< BOOST_EGG_PP_SEQ_ENUM_PARAMS((class)(int), P) >
    struct params
    {
        typedef params< BOOST_EGG_PP_SEQ_ENUM_ARGS((class)(int), P) > self_t;
        BOOST_MPL_ASSERT((boost::is_same<self_t, params>));
    };

    params<int, 3> g_params;


    template< BOOST_PP_SEQ_ENUM(BOOST_EGG_PP_SEQ_PARAMS(3, class A)) >
    void seq_params3( BOOST_PP_SEQ_ENUM(BOOST_EGG_PP_SEQ_PARAMS(3, A)) )
    { }


    int plus(int i, int j, int k) { return i + j + k; }

    void test_()
    {
        cyfoo(1, 1, 1, 1, 1, 1);
        seq_params3(1, 1, 1);

        BOOST_CHECK( 1+1+1 == plus( BOOST_PP_SEQ_ENUM( BOOST_EGG_PP_SEQ_REPEAT(1, 3) ) ) );
    }


}


void egg_test()
{
    (void)cat3_::k;
    int_n_::test_();
    seq_::test_();
}
