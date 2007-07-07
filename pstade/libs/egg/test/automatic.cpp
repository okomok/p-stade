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
            typedef ::pstade::egg::automatic<PSTADE_UNPARENTHESIZE(Lambda)>::type op; \
        } \
        \
        typedef BOOST_PP_CAT(pstade_automatic_workarea_of_, Object)::op BOOST_PP_CAT(op_, Object); \
        PSTADE_POD_CONSTANT( (BOOST_PP_CAT(op_, Object)), Object ) = PSTADE_EGG_AUTOMATIC_INITIALIZER();
    /**/




template<class To>
struct op_cast0
{
    typedef To result_type;

    To operator()() const
    {
        return 10;
    }
};

PSTADE_AUTOMATIC(auto_cast0, (op_cast0<boost::mpl::_1>))


template<class To>
struct op_cast1
{
    typedef To result_type;

    template<class From0>
    To operator()(From0 from0) const
    {
        return from0;
    }
};

PSTADE_AUTOMATIC(auto_cast1, (op_cast1<_>))


template<class To>
struct op_cast2
{
    typedef To result_type;

    template<class From0, class From1>
    To operator()(From0 from0, From1 from1) const
    {
        return from0 + from1;
    }
};

PSTADE_AUTOMATIC(auto_cast2, (op_cast2<_>))


void pstade_minimal_test()
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
}

