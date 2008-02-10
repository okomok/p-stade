#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy get
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/fusion/element.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/tuple/tuple.hpp>
#include <utility>
#include <boost/mpl/int.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/assert.hpp>
#include <pstade/egg/is_same.hpp>
#include <boost/type_traits/is_same.hpp>

#if defined(PSTADE_EGG_HAS_FUSIONS)
#include <boost/fusion/include/vector.hpp>
#endif


using namespace pstade::egg;


namespace pair_test {

    typedef std::pair<int, double> seq_t;

    BOOST_MPL_ASSERT((boost::is_same<int, fusion_element_c<seq_t, 0>::type>));
    BOOST_MPL_ASSERT((boost::is_same<double, fusion_element_c<seq_t, 1>::type>));

    BOOST_MPL_ASSERT((boost::is_same<int, fusion_element_c<seq_t const, 0>::type>));
    BOOST_MPL_ASSERT((boost::is_same<double, fusion_element_c<seq_t const, 1>::type>));

}

namespace tuple_test {

    typedef boost::tuples::tuple<int&, double> seq_t;

    BOOST_MPL_ASSERT((boost::is_same<int&, fusion_element_c<seq_t, 0>::type>));
    BOOST_MPL_ASSERT((boost::is_same<double, fusion_element_c<seq_t, 1>::type>));

    BOOST_MPL_ASSERT((boost::is_same<int&, fusion_element_c<seq_t const, 0>::type>));
    BOOST_MPL_ASSERT((boost::is_same<double, fusion_element_c<seq_t const, 1>::type>));
}


#if defined(PSTADE_EGG_HAS_FUSIONS)

namespace fusion_test {

    typedef boost::fusion::vector<int&, double> seq_t;

    BOOST_MPL_ASSERT((boost::is_same<int&, fusion_element_c<seq_t, 0>::type>));
    BOOST_MPL_ASSERT((boost::is_same<double, fusion_element_c<seq_t, 1>::type>));

    BOOST_MPL_ASSERT((boost::is_same<int&, fusion_element_c<seq_t const, 0>::type>));
    BOOST_MPL_ASSERT((boost::is_same<double, fusion_element_c<seq_t const, 1>::type>));

}

#endif


void pstade_minimal_test()
{
}
