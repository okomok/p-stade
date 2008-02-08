#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/mpL_std_pair.hpp>
#include <pstade/lightweight_test.hpp>


#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/empty.hpp>


namespace mpl = boost::mpl;


namespace test1 {

    typedef std::pair<int, int> seq_t;
    typedef mpl::vector<int, int> ans_t;

    BOOST_MPL_ASSERT((boost::is_same<mpl::at_c<seq_t, 0>::type, int>));
    BOOST_MPL_ASSERT((boost::is_same<mpl::at_c<seq_t, 1>::type, int>));
    BOOST_MPL_ASSERT((mpl::equal<seq_t, ans_t>));
    BOOST_MPL_ASSERT((mpl::equal_to<mpl::size<seq_t>::type, mpl::size<ans_t>::type>));

}

namespace test2 {

    typedef std::pair<int, char const> seq_t;
    typedef mpl::vector<int, char const> ans_t;

    BOOST_MPL_ASSERT((boost::is_same<mpl::at_c<seq_t, 0>::type, int>));
    BOOST_MPL_ASSERT((boost::is_same<mpl::at_c<seq_t, 1>::type, char const>));
    BOOST_MPL_ASSERT((mpl::equal<seq_t, ans_t>));

    typedef mpl::iterator_range<mpl::begin<seq_t>::type, mpl::next<mpl::begin<seq_t>::type>::type> f_t;
    typedef mpl::iterator_range<mpl::next<mpl::begin<seq_t>::type>::type, mpl::end<seq_t>::type> s_t;

    BOOST_MPL_ASSERT((mpl::equal<f_t, mpl::vector<int> >));
    BOOST_MPL_ASSERT((mpl::equal<s_t, mpl::vector<char const> >));
    
    typedef mpl::iterator_range<mpl::next<mpl::begin<seq_t>::type>::type, mpl::prior<mpl::end<seq_t>::type>::type> e_t;
    BOOST_MPL_ASSERT((mpl::empty<e_t>));
}


void pstade_lightweight_test()
{ }
