#ifndef PSTADE_OVEN_TRANSFORMED_HPP
#define PSTADE_OVEN_TRANSFORMED_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/plain.hpp>
#include <pstade/result_of.hpp>
#include <pstade/use_default.hpp>
#include "./concepts.hpp"
#include "./detail/little_to_adaptor.hpp"
#include "./detail/transform_iterator.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace transformed_detail {


    template< class Reference, class Value >
    struct little
    {
        template< class Myself, class Range, class UnaryFun >
        struct apply
        {
            typedef typename
                range_iterator<Range>::type
            base_iter_t;

            typedef typename
                pass_by_value<UnaryFun>::type
            fun_t;

            typedef typename
                iterator_read<base_iter_t>::type
            read_t;

            typedef typename
                eval_if_use_default<
                    Reference,
                    result_of<fun_t const(read_t)>
                >::type
            ref_t;

            typedef typename
                eval_if_use_default<
                    Value,
                    plain<ref_t>
                >::type
            val_t;

            typedef
                detail::transform_iterator<
                    fun_t,
                    base_iter_t,
                    ref_t,
                    val_t
                >
            iter_t;

            typedef
                iter_range<iter_t> const
            type;
        };

        template< class Result, class Range, class UnaryFun >
        Result call(Range& rng, UnaryFun& fun) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

            typedef typename Result::iterator iter_t;
            return Result(
                iter_t(boost::begin(rng), fun),
                iter_t(boost::end(rng),   fun)
            );
        }
    };


} // namespace transformed_detail


template<
    class Reference = boost::use_default,
    class Value     = boost::use_default
>
struct X_make_transformed :
    egg::function< transformed_detail::little<Reference, Value> >
{ };


PSTADE_OVEN_LITTLE_TO_ADAPTOR(transformed, (X_make_transformed<>::little_type))


} } // namespace pstade::oven


#endif
