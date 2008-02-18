

// Boost.Egg
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/generator.hpp>
#include "./egg_test.hpp"


#include <boost/mpl/assert.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/result_of.hpp>
#include <boost/egg/const.hpp>
#include <string>


#include "./using_egg.hpp"


// In general, it is unlikely that a document specifies
// "this class template doesn't define nested `type`".
template<class T, class U>
struct my_pair
{
    typedef int type; // doesn't affect.

    my_pair(T, U) {};

    my_pair() {};
};

typedef generator< my_pair< deduce<boost::mpl::_1, as_value, int>, deduce<boost::mpl::_2, as_value, char> >, boost::use_default, boost::use_default, use_nullary_result >::type T_make_my_pair;
BOOST_MPL_ASSERT((boost::is_same< pstade::result_of<T_make_my_pair(int&, double)>::type, my_pair<int, double> >));
BOOST_MPL_ASSERT((boost::is_same< pstade::result_of<T_make_my_pair()>::type, my_pair<int, char> >));
BOOST_EGG_CONST((T_make_my_pair), make_my_pair) = BOOST_EGG_GENERATOR();

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
BOOST_EGG_CONST((T_id), id) = BOOST_EGG_GENERATOR();

struct id_metafun_
{
    template<class A = std::string> // nullary
    struct apply
    {
        typedef typename boost::remove_cv<A>::type type;
    };
};

typedef generator< id_metafun_, boost::use_default, boost::use_default, use_nullary_result >::type T_id_;
BOOST_MPL_ASSERT((boost::is_same< pstade::result_of<T_id_(int&)>::type, int >));
BOOST_MPL_ASSERT((boost::is_same< pstade::result_of<T_id_()>::type, std::string >)); // nullary
BOOST_MPL_ASSERT((boost::is_same< pstade::result_of<T_id_(int const&)>::type, int >));
BOOST_MPL_ASSERT((boost::is_same< pstade::result_of<T_id_(int)>::type, int >));
BOOST_EGG_CONST((T_id_), id_) = BOOST_EGG_GENERATOR();


void egg_test()
{
    int i = 10;
    BOOST_CHECK( &(id(i)) == &i );

    BOOST_CHECK( id_(i) == 10 );
    BOOST_CHECK( id_().empty() );

    {
        my_pair<int, int> p = make_my_pair(1, 2);
        (void)p;
    }
    {
        my_pair<int, char> p = make_my_pair();
        (void)p;
    }
}
