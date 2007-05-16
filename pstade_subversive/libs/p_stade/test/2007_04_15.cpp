#include <pstade/vodka/drink.hpp>


// PStade.p_stade;
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/callable.hpp>
#include <pstade/oven/reverse_iterator.hpp>
#include <vector>

typedef pstade::oven::reverse_iterator<std::_Vector_iterator<int,std::allocator<int> > > iter_t;

//BOOST_MPL_ASSERT((boost::is_same< int, boost::detail::iterator_traits<iter_t>::value_type>));
BOOST_MPL_ASSERT((boost::is_same<__w64 int, pstade::callable_argument<__w64 int&>::type>));


int main()
{
    iter_t it;
    boost::detail::iterator_traits<iter_t>::value_type v = 0;
    *it = v;
}
