#ifndef PSTADE_OVEN_ADJACENT_TRANSFORMED_HPP
#define PSTADE_OVEN_ADJACENT_TRANSFORMED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// The Adaptor version of 'std::adjacent_difference'.


// Question:
//
// See "../../libs/oven/example/adjacent_difference.cpp".
// Should this contain the first value of base range?
// This is symmetrical to 'scanned', which requires
// the first value to be passed. So, it's intuitive
// not to contain the first value of base range, IMO.


#include "./detail/prelude.hpp"
#include <boost/assert.hpp>
#include <boost/range/empty.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pack.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./dropped.hpp"
#include "./popped.hpp"
#include "./zipped_with.hpp"


namespace pstade { namespace oven {


template<
    class Reference = boost::use_default,
    class Value     = boost::use_default
>
struct op_make_adjacent_transformed :
    callable< op_make_adjacent_transformed<Reference, Value> >
{
    template< class Myself, class Range, class BinaryFun >
    struct apply :
        boost::result_of<
            op_make_zipped_with<Reference, Value>(
                typename boost::result_of<
                    op_pack(
                        typename boost::result_of<op_make_popped(Range&)>::type,
                        typename boost::result_of<op_make_dropped(Range&, int)>::type
                    )
                >::type,
                BinaryFun&
            )
        >
    { };

    template< class Result, class Range, class BinaryFun >
    Result call(Range& rng, BinaryFun& fun) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
        BOOST_ASSERT(!boost::empty(rng));

        return
            op_make_zipped_with<Reference, Value>()(
                pack(make_popped(rng), make_dropped(rng, 1)),
                fun
            );
    }
};


PSTADE_CONSTANT(make_adjacent_transformed, (op_make_adjacent_transformed<>))
PSTADE_PIPABLE(adjacent_transformed, (op_make_adjacent_transformed<>))


} } // namespace pstade::oven


#endif
