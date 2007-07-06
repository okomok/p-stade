#ifndef PSTADE_OVEN_AS_ARRAY_HPP
#define PSTADE_OVEN_AS_ARRAY_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// References:
//
// [1] Pavol Droba, as_array, Proposal for new string algorithms in TR2, 2006.
//     http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n2059.html


#include <cstddef> // size_t
#include <boost/type_traits/is_array.hpp>
#include <pstade/auxiliary.hpp>
#include <pstade/callable.hpp>
#include <pstade/egg/to_value.hpp>
#include <pstade/enable_if.hpp>
#include "./detail/array_to_range.hpp"


namespace pstade { namespace oven {


namespace as_array_detail {


    struct op :
        callable<op>
    {
        template< class Myself, class MaybeArray >
        struct apply :
            detail::array_to_range<MaybeArray>
        { };

        template< class Result, class T, std::size_t sz >
        Result call(T (&arr)[sz]) const
        {
            return Result(egg::to_value(arr), egg::to_value(arr) + sz);
        }

        template< class Result, class Range >
        Result call(Range& rng,
            typename disable_if< boost::is_array<Range> >::type = 0) const
        {
            return rng;
        }
    };


} // namespace as_array_detail


PSTADE_AUXILIARY(0, as_array, (as_array_detail::op))


} } // namespace pstade::oven


#endif
