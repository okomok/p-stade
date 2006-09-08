#ifndef PSTADE_OVEN_TO_INSERTER_HPP
#define PSTADE_OVEN_TO_INSERTER_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// 'function_output_iterator' with lambda is more generalized,
// but its syntax looks cumbersome.


#include <iterator>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_const.hpp>


namespace pstade { namespace oven {


template< class Sequence, class Iterator > inline
std::insert_iterator<Sequence> const
to_inserter(Sequence& seq, Iterator const& it)
{
    BOOST_MPL_ASSERT_NOT((boost::is_const<Sequence>));
    return std::insert_iterator<Sequence>(seq, it);
}


template< class Sequence > inline
std::front_insert_iterator<Sequence> const
to_front_inserter(Sequence& seq)
{
    BOOST_MPL_ASSERT_NOT((boost::is_const<Sequence>));
    return std::front_insert_iterator<Sequence>(seq);
}


template< class Sequence > inline
std::back_insert_iterator<Sequence> const
to_back_inserter(Sequence& seq)
{
    BOOST_MPL_ASSERT_NOT((boost::is_const<Sequence>));
    return std::back_insert_iterator<Sequence>(seq);
}


} } // namespace pstade::oven


#endif
