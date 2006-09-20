#ifndef PSTADE_OVEN_TO_SEQUENCE_HPP
#define PSTADE_OVEN_TO_SEQUENCE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// 'function_output_iterator' with lambda is more generalized,
// but its syntax looks cumbersome. So we define...


#include <iterator>


namespace pstade { namespace oven {


template< class Sequence, class Iterator > inline
std::insert_iterator<Sequence> const
to_sequence(Sequence& seq, Iterator const& it)
{
    return std::insert_iterator<Sequence>(seq, it);
}


template< class Sequence > inline
std::front_insert_iterator<Sequence> const
to_front_of(Sequence& seq)
{
    return std::front_insert_iterator<Sequence>(seq);
}


template< class Sequence > inline
std::back_insert_iterator<Sequence> const
to_back_of(Sequence& seq)
{
    return std::back_insert_iterator<Sequence>(seq);
}


} } // namespace pstade::oven


#endif
