#ifndef PSTADE_OVEN_ZIPPED_HPP
#define PSTADE_OVEN_ZIPPED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// 'tuple_transform' doesn't support non-const tuple,
// so that 'RangeTuple' must hold references for now.
// Boost.Fusion will solve it.


#include <boost/iterator/zip_iterator.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace zipped_detail {


    namespace impl = boost::detail::tuple_impl_specific;


    struct with_apply
    {
        template< class Range >
        struct apply :
            range_iterator<
                typename boost::remove_reference<Range>::type
            >
        { };
    };


    struct begin_fun : with_apply
    {
        template< class Range >
        typename apply<Range&>::type
        operator()(Range& rng) const
        {
            return boost::begin(rng);
        }
    };


    struct end_fun   : with_apply
    {
        template< class Range >
        typename apply<Range&>::type
        operator()(Range& rng) const
        {
            return boost::end(rng);
        }
    };


    template< class RangeTuple >
    struct baby
    {
        typedef
            boost::zip_iterator<
                typename impl::tuple_meta_transform<
                    RangeTuple, with_apply
                >::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result;

        result call(RangeTuple& tup)
        {
            return result(
                iter_t( impl::tuple_transform(tup, begin_fun()) ),
                iter_t( impl::tuple_transform(tup, end_fun()) )
            );
        }
    };


} // namespace zipped_detail


PSTADE_FUNCTION(make_zipped, (zipped_detail::baby<_>))
PSTADE_PIPABLE(zipped, (op_make_zipped))


} } // namespace pstade::oven


#endif
