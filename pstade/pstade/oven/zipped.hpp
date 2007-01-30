#ifndef PSTADE_OVEN_ZIPPED_HPP
#define PSTADE_OVEN_ZIPPED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/zip_iterator.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/affect.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./begin_end.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace zipped_detail {


    namespace impl = boost::detail::tuple_impl_specific;


    template< class RangeTuple >
    struct with_apply
    {
        template< class Range > // 'Range' is what 'value_at' returns.
        struct apply :
            boost::result_of<
                op_begin(typename affect<RangeTuple&, Range>::type)
            >
        { };
    };


    template< class RangeTuple >
    struct begin_fun :
        with_apply<RangeTuple>
    {
        template< class Range >
        typename range_iterator<Range>::type
        operator()(Range& rng) const
        {
            return boost::begin(rng);
        }
    };


    template< class RangeTuple >
    struct end_fun :
        with_apply<RangeTuple>
    {
        template< class Range >
        typename range_iterator<Range>::type
        operator()(Range& rng) const
        {
            return boost::end(rng);
        }
    };


    template< class RangeTuple >
    struct baby
    {
        typedef
            // As 'tuple_transform' doesn't support a non-const tuple,
            // 'const' must be added for now; Boost.Fusion will solve this.
            RangeTuple const
        rng_tuple_t;

        typedef
            boost::zip_iterator<
                typename impl::tuple_meta_transform<
                    RangeTuple, with_apply<rng_tuple_t>
                >::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result;

        result call(rng_tuple_t& tup)
        {
            return result(
                iter_t( impl::tuple_transform(tup, begin_fun<rng_tuple_t>()) ),
                iter_t( impl::tuple_transform(tup, end_fun<rng_tuple_t>()) )
            );
        }
    };


} // namespace zipped_detail


PSTADE_FUNCTION(make_zipped, (zipped_detail::baby<_>))
PSTADE_PIPABLE(zipped, (op_make_zipped))


} } // namespace pstade::oven


#endif
