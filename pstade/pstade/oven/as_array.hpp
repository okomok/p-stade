#ifndef PSTADE_OVEN_AS_ARRAY_HPP
#define PSTADE_OVEN_AS_ARRAY_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // size_t
#include <boost/mpl/eval_if.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/remove_extent.hpp>
#include <pstade/auxiliary.hpp>
#include <pstade/callable.hpp>
#include <pstade/enable_if.hpp>
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace as_array_detail {


    template< class Array >
    struct array_to_range
    {
        typedef typename
            boost::remove_extent<Array>::type *
        iter_t;

        typedef
            iter_range<iter_t> const
        type;
    };


    template< class MaybeArray >
    struct to_range :
        boost::mpl::eval_if< boost::is_array<MaybeArray>,
            array_to_range<MaybeArray>,
            boost::add_reference<MaybeArray>
        >
    { };


    struct op :
        callable<op>
    {
        template< class Myself, class MaybeArray >
        struct apply :
            to_range<MaybeArray>
        { };

        template< class Result, class T, std::size_t sz >
        Result call(T (&arr)[sz]) const
        {
            // cast precisely for enabler.
            return Result(static_cast<T *>(arr), static_cast<T *>(arr) + sz);
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
