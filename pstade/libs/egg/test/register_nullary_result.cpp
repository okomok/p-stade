#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/register_nullary_result.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/egg/function_facade.hpp>
#include <pstade/egg/function.hpp>
#include <boost/mpl/assert.hpp>
#include <pstade/result_of.hpp>
#include <boost/type_traits/is_same.hpp>


namespace egg = pstade::egg;
using namespace egg;
using pstade::result_of;



struct three :
    function_facade<three, boost::use_default, int>
{
    template<class R>
    R call() const
    {
        return 3;
    };
};


namespace my { namespace your {

    struct three :
        function_facade<three, boost::use_default, int>
    {
        template<class R>
        R call() const
        {
            return 3;
        };
    };


} }



template<class A, class B>
struct four :
    function_facade<four<A, B>, boost::use_default, int>
{
    template<class R>
    R call() const
    {
        return 4;
    };
};


namespace my {

template<class A, class B>
struct four :
    function_facade<four<A, B>, boost::use_default, int>
{
    template<class R>
    R call() const
    {
        return 4;
    };
};


}



namespace my { namespace our {

template<int N, class A, int M, class B>
struct five :
    function_facade<five<N, A, M, B>, boost::use_default, int>
{
    template<class R>
    R call() const
    {
        return 4;
    };
};


} }


PSTADE_EGG_REGISTER_NULLARY_RESULT_OF_TYPE(three)
PSTADE_EGG_REGISTER_NULLARY_RESULT_OF_TYPE(my::your::three)

PSTADE_EGG_REGISTER_NULLARY_RESULT_OF_TEMPLATE(four, (class)(class))
PSTADE_EGG_REGISTER_NULLARY_RESULT_OF_TEMPLATE(my::four, 2)
PSTADE_EGG_REGISTER_NULLARY_RESULT_OF_TEMPLATE(my::our::five, (int)(class)(int)(class))


BOOST_MPL_ASSERT((boost::is_same<result_of<three()>::type, int>));
BOOST_MPL_ASSERT((boost::is_same<result_of<my::your::three()>::type, int>));
BOOST_MPL_ASSERT((boost::is_same<result_of<four<int,int>()>::type, int>));
BOOST_MPL_ASSERT((boost::is_same<result_of<my::four<int, int>()>::type, int>));
BOOST_MPL_ASSERT((boost::is_same<result_of<my::our::five<3, int, 2, int>()>::type, int>));


BOOST_MPL_ASSERT((boost::is_same<result_of<three const()>::type, int>));
BOOST_MPL_ASSERT((boost::is_same<result_of<my::your::three const()>::type, int>));
BOOST_MPL_ASSERT((boost::is_same<result_of<four<int,int> const()>::type, int>));
BOOST_MPL_ASSERT((boost::is_same<result_of<my::four<int, int> const()>::type, int>));
BOOST_MPL_ASSERT((boost::is_same<result_of<my::our::five<3, int, 2, int> const()>::type, int>));


void pstade_minimal_test()
{

}
