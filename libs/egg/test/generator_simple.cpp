#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/generator.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/result_of.hpp>
#include <pstade/egg/const.hpp>


namespace egg = pstade::egg;
using namespace egg;


// In general, it is unlikely that a document specifies
// "this class template doesn't define nested `type`".
template<class T, class U>
struct my_pair
{
    typedef int type; // doesn't affect.

    my_pair(T, U) {};
};

typedef generator< my_pair< deduce<boost::mpl::_1, as_value>, deduce<boost::mpl::_2, as_value> > >::type T_make_my_pair;
BOOST_MPL_ASSERT((boost::is_same< pstade::result_of<T_make_my_pair(int&, double)>::type, my_pair<int, double> >));
PSTADE_EGG_CONST((T_make_my_pair), make_my_pair) = PSTADE_EGG_GENERATOR();

typedef generator< my_pair< deduce<boost::mpl::_1, as_cref>, deduce<boost::mpl::_2, as_ref> > >::type T_make_my_pair_cref;
BOOST_MPL_ASSERT((boost::is_same< pstade::result_of<T_make_my_pair_cref(int&, double)>::type, my_pair<int const&, double const&> >));


// must make a "new type".
struct id_metafun :
    boost::mpl::lambda< deduce<boost::mpl::_1, as_ref> >::type
{ };

typedef generator< id_metafun >::type T_id;
BOOST_MPL_ASSERT((boost::is_same< pstade::result_of<T_id(int&)>::type, int& >));
BOOST_MPL_ASSERT((boost::is_same< pstade::result_of<T_id(int const&)>::type, int const& >));
BOOST_MPL_ASSERT((boost::is_same< pstade::result_of<T_id(int)>::type, int const& >));
PSTADE_EGG_CONST((T_id), id) = PSTADE_EGG_GENERATOR();


void pstade_minimal_test()
{
    int i = 10;
    BOOST_CHECK( &(id(i)) == &i );

    my_pair<int, int> p = make_my_pair(1, 2);
    (void)p;
}
