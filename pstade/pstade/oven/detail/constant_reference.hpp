#ifndef PSTADE_OVEN_DETAIL_CONSTANT_REFERENCE_HPP
#define PSTADE_OVEN_DETAIL_CONSTANT_REFERENCE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// A helper metafunction to implement constant iterators.
// This seems more useful rather than something like
// 'constant_iterator' which makes coding cumbersome.
// See "../merge_iterator.hpp" or "../cycle_iterator".


#include <boost/iterator/iterator_traits.hpp>
#include <boost/type_traits/add_const.hpp>
#include <pstade/affect.hpp>


namespace pstade { namespace oven { namespace detail {


template< class Iterator >
struct constant_reference
{
    typedef typename boost::iterator_reference<Iterator>::type ref_t;
    typedef typename boost::iterator_value<Iterator>::type val_t;

    typedef typename affect_cvr<
        ref_t,
        typename boost::add_const<val_t>::type
    >::type type;
};


} } } // namespace pstade::oven::detail


#endif
