#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy fusion_get
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/fusion/drop1.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/tuple/tuple.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal.hpp>
#include <pstade/egg/is_same.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/result_of.hpp>

#if defined(PSTADE_EGG_HAS_FUSIONS)
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/at.hpp>
#endif


namespace egg = pstade::egg;
using namespace egg;


typedef boost::tuples::tuple<double, int> tup_t;
typedef boost::tuples::cons<int, boost::tuples::null_type> ans_tup_t;
// lvalue
BOOST_MPL_ASSERT((boost::is_same<ans_tup_t&, pstade::result_of<T_fusion_drop1(tup_t&)>::type>));
BOOST_MPL_ASSERT((boost::is_same<ans_tup_t const&, pstade::result_of<T_fusion_drop1(tup_t const&)>::type>));
// rvalue
BOOST_MPL_ASSERT((boost::is_same<ans_tup_t const&, pstade::result_of<T_fusion_drop1(tup_t)>::type>));
BOOST_MPL_ASSERT((boost::is_same<ans_tup_t const&, pstade::result_of<T_fusion_drop1(tup_t const)>::type>));


typedef boost::tuples::tuple<double, int&> tup2_t;
typedef boost::tuples::cons<int&, boost::tuples::null_type> ans_tup2_t;
// lvalue
BOOST_MPL_ASSERT((boost::is_same<ans_tup2_t&, pstade::result_of<T_fusion_drop1(tup2_t&)>::type>));
BOOST_MPL_ASSERT((boost::is_same<ans_tup2_t const&, pstade::result_of<T_fusion_drop1(tup2_t const&)>::type>));
// rvalue
BOOST_MPL_ASSERT((boost::is_same<ans_tup2_t const&, pstade::result_of<T_fusion_drop1(tup2_t)>::type>));
BOOST_MPL_ASSERT((boost::is_same<ans_tup2_t const&, pstade::result_of<T_fusion_drop1(tup2_t const)>::type>));


#if defined(PSTADE_EGG_HAS_FUSIONS)

typedef boost::fusion::vector<double, int> seq_t;
typedef boost::fusion::vector<int> ans_seq_t;

// lvalue
BOOST_MPL_ASSERT((boost::mpl::equal<ans_seq_t, pstade::result_of<T_fusion_drop1(seq_t&)>::type>));
BOOST_MPL_ASSERT((boost::mpl::equal<ans_seq_t, pstade::result_of<T_fusion_drop1(seq_t const&)>::type>));
// rvalue
BOOST_MPL_ASSERT((boost::mpl::equal<ans_seq_t, pstade::result_of<T_fusion_drop1(seq_t)>::type>));
BOOST_MPL_ASSERT((boost::mpl::equal<ans_seq_t, pstade::result_of<T_fusion_drop1(seq_t const)>::type>));


typedef boost::fusion::vector<double, int&> seq2_t;
typedef boost::fusion::vector<int&> ans_seq2_t;
// lvalue
BOOST_MPL_ASSERT((boost::mpl::equal<ans_seq2_t, pstade::result_of<T_fusion_drop1(seq2_t&)>::type>));
BOOST_MPL_ASSERT((boost::mpl::equal<ans_seq2_t, pstade::result_of<T_fusion_drop1(seq2_t const&)>::type>));
// rvalue
BOOST_MPL_ASSERT((boost::mpl::equal<ans_seq2_t, pstade::result_of<T_fusion_drop1(seq2_t)>::type>));
BOOST_MPL_ASSERT((boost::mpl::equal<ans_seq2_t, pstade::result_of<T_fusion_drop1(seq2_t const)>::type>));

#endif


void pstade_minimal_test()
{
    int k = 999;
    tup2_t t(1.0, k);
    BOOST_CHECK( egg::is_same(boost::get<0>(fusion_drop1(t)), k) );

#if defined(PSTADE_EGG_HAS_FUSIONS)
    seq2_t s(1.0, k);
    BOOST_CHECK( egg::is_same(boost::fusion::at_c<0>(fusion_drop1(s)), k) );
#endif
}
