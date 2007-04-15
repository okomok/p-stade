#ifndef PSTADE_OVEN_DETAIL_BRACKET_OPERATOR_HPP
#define PSTADE_OVEN_DETAIL_BRACKET_OPERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// (C) Copyright David Abrahams 2002.
// (C) Copyright Jeremy Siek    2002.
// (C) Copyright Thomas Witt    2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Rejected...
//
// It is useless to return a "convertible" type; even if the standard allows.


#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <pstade/function.hpp>
#include <pstade/pass_by.hpp>


namespace pstade { namespace oven { namespace detail {


template< class Iterator, class Difference >
struct baby_bracket_operator
{
    typedef typename
        pass_by_value<Iterator>::type
    iter_t;

    typedef typename
        boost::iterator_value<iter_t>::type
    val_t;

    typedef typename
        boost::iterator_reference<iter_t>::type
    ref_t;

    typedef typename
        boost::detail::operator_brackets_result<
            iter_t, val_t, ref_t
        >::type
    result_type;

    result_type operator()(Iterator& it, Difference& n) const
    {
        typedef boost::detail::use_operator_brackets_proxy<iter_t, ref_t> use_proxy;
        return boost::detail::make_operator_brackets_result<iter_t>(
            it + n, use_proxy()
        );
    }
};


PSTADE_FUNCTION(bracket_operator, (baby_bracket_operator<_, _>))


} } } // namespace pstade::oven::detail


#endif
