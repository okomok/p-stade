#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/automatic.hpp>
#include <pstade/minimal_test.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>



#include <pstade/unparenthesize.hpp>
#include <pstade/pod_constant.hpp>
#include <boost/mpl/placeholders.hpp>


    #define PSTADE_AUTOMATIC(Object, Lambda) \
        namespace BOOST_PP_CAT(pstade_automatic_workarea_of_, Object) { \
            using namespace ::boost::mpl::placeholders; \
            typedef ::pstade::egg::automatic_ref<PSTADE_UNPARENTHESIZE(Lambda)>::type op; \
        } \
        \
        typedef BOOST_PP_CAT(pstade_automatic_workarea_of_, Object)::op BOOST_PP_CAT(T_, Object); \
        PSTADE_POD_CONSTANT( (BOOST_PP_CAT(T_, Object)), Object ) = PSTADE_EGG_AUTOMATIC_REF;
    /**/



int g_int0 = 10;

template<class To>
struct T_cast0
{
    typedef To &result_type;

    To &operator()() const
    {
        return g_int0;
    }
};

PSTADE_AUTOMATIC(auto_cast0, (T_cast0<boost::mpl::_1>))


template<class To>
struct T_cast1
{
    typedef To &result_type;

    template<class From0>
    To & operator()(From0& from0) const
    {
        return from0;
    }
};

PSTADE_AUTOMATIC(auto_cast1, (T_cast1<_>))



void pstade_minimal_test()
{
    {
        int& i = auto_cast0();
        BOOST_CHECK( &i == &g_int0 );
    }
#if 0 // todo:
    {
        int i = auto_cast0;
        BOOST_CHECK( i == 10 );
    }
#endif
    {
        int a = 12;
        int& i = auto_cast1(a);
        BOOST_CHECK( &i == &a );
    }
    {
        int a = 12;
        int const & i = auto_cast1(a);
        BOOST_CHECK( &i == &a );
    }
    {
        int const a = 12;
        int const& i = auto_cast1(a);
        BOOST_CHECK( &i == &a );
    }
}

