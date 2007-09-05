#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/pipable.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/pod_constant.hpp>
#include <boost/mpl/placeholders.hpp>
#include <pstade/unparenthesize.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/facilities/identity.hpp>
#include "./large_arity_id0.hpp"


    #define PSTADE_decl_pipable(O, F) \
        namespace BOOST_PP_CAT(pstade_egg_pipable_workarea_of_, O) { \
            using namespace boost::mpl::placeholders; \
            typedef pstade::egg::result_of_pipable<PSTADE_UNPARENTHESIZE(F)>::type pipe; \
        } \
        PSTADE_POD_CONSTANT((BOOST_PP_CAT(pstade_egg_pipable_workarea_of_, O)::pipe), O) = PSTADE_EGG_PIPABLE_L {} PSTADE_EGG_PIPABLE_R; \
    /**/



struct my_fun_t
{
    typedef int result_type;

    int operator()(int x) const
    {
        return x + 1;
    }
};

PSTADE_decl_pipable(my_fun, (my_fun_t))


struct your_fun_t
{
    typedef int result_type;

    int operator()(std::string str, int x, int y) const
    {
        return x + y;
    }
};

PSTADE_decl_pipable(your_fun, (your_fun_t))


using namespace pstade::egg;

result_of_pipable<op_large_arity_id0, by_cref>::type const lar = PSTADE_EGG_PIPABLE_L {} PSTADE_EGG_PIPABLE_R;


void pstade_minimal_test()
{
    BOOST_CHECK( (3|my_fun) == 4 );
    BOOST_CHECK( (3|my_fun()) == 4 );
    BOOST_CHECK( ("hello"|your_fun(1, 2)) == 3 );

    {
        using namespace large_arity_helpers;
        BOOST_CHECK( &(i0|lar(i1,i2,i3,i4,i5,i6,i7,ci8,ci9)) == &i0 );        
    }
}
