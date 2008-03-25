

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/implicit.hpp>
#include "./egg_test.hpp"
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>



#include <boost/egg/detail/unparen.hpp>
#include <boost/egg/const.hpp>
#include <boost/mpl/placeholders.hpp>


    #define EGG_implicit_def(Object, Lambda) \
        namespace BOOST_PP_CAT(pstade_implicit_workarea_of_, Object) { \
            using namespace ::boost::mpl::placeholders; \
            typedef ::boost::egg::implicit_ref<BOOST_EGG_UNPAREN(Lambda)>::type op; \
        } \
        \
        typedef BOOST_PP_CAT(pstade_implicit_workarea_of_, Object)::op BOOST_PP_CAT(T_, Object); \
        BOOST_EGG_CONST( (BOOST_PP_CAT(T_, Object)), Object ) = BOOST_EGG_IMPLICIT_REF();
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

EGG_implicit_def(auto_cast0, (T_cast0<boost::mpl::_1>))


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

EGG_implicit_def(auto_cast1, (T_cast1<_>))



void egg_test()
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

