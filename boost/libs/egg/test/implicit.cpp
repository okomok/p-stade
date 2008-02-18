

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



#include <pstade/unparenthesize.hpp>
#include <pstade/pod_constant.hpp>
#include <boost/mpl/placeholders.hpp>


    #define PSTADE_IMPLICIT(Object, Lambda) \
        namespace BOOST_PP_CAT(pstade_implicit_workarea_of_, Object) { \
            using namespace ::boost::mpl::placeholders; \
            typedef ::pstade::egg::implicit<PSTADE_UNPARENTHESIZE(Lambda)>::type op; \
        } \
        \
        typedef BOOST_PP_CAT(pstade_implicit_workarea_of_, Object)::op BOOST_PP_CAT(T_, Object); \
        PSTADE_POD_CONSTANT( (BOOST_PP_CAT(T_, Object)), Object ) = BOOST_EGG_IMPLICIT();
    /**/




template<class To>
struct T_cast0
{
    typedef To result_type;

    To operator()() const
    {
        return 10;
    }
};

PSTADE_IMPLICIT(auto_cast0, (T_cast0<boost::mpl::_1>))


template<class To>
struct T_cast1
{
    typedef To result_type;

    template<class From0>
    To operator()(From0 from0) const
    {
        return from0;
    }
};

PSTADE_IMPLICIT(auto_cast1, (T_cast1<_>))


template<class To>
struct T_cast2
{
    typedef To result_type;

    template<class From0, class From1>
    To operator()(From0 from0, From1 from1) const
    {
        return from0 + from1;
    }
};

PSTADE_IMPLICIT(auto_cast2, (T_cast2<_>))


void egg_test()
{
    {
        int i = auto_cast0();
        BOOST_CHECK( i == 10 );
    }
#if 0 // todo:
    {
        int i = auto_cast0;
        BOOST_CHECK( i == 10 );
    }
#endif
    {
        int i = auto_cast1(12);
        BOOST_CHECK( i == 12 );
    }
    {
        int i = auto_cast2(3, 6);
        BOOST_CHECK( i == 9 );
    }

    {
        int const& i = auto_cast1(12);
        BOOST_CHECK( i == 12 );
    }
    {
        int const& i = auto_cast2(3, 6);
        BOOST_CHECK( i == 9 );
    }
}

