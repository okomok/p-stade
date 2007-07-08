#ifndef PSTADE_OVEN_INDIRECTED_HPP
#define PSTADE_OVEN_INDIRECTED_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// References:
//
// [1] Eric Niebler, indirect_range, Boost.RangeEx, 2004.
//     http://www.boost-consulting.com/vault/index.php?directory=Algorithms


#include <boost/iterator/indirect_iterator.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include "./concepts.hpp"
#include "./detail/baby_to_adaptor.hpp"
#include "./detail/indirect_iterator.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


template<
    class Value      = boost::use_default,
    class Traversal  = boost::use_default,
    class Reference  = boost::use_default,
    class Difference = boost::use_default
>
struct tp_make_indirected 
{
    struct baby
    {
        template< class Myself, class Range >
        struct apply
        {
            typedef
                detail::indirect_iterator<
                    typename range_iterator<Range>::type,
                    Value,
                    Traversal,
                    Reference,
                    Difference
                >
            iter_t;

            typedef
                iter_range<iter_t> const
            type;
        };

        template< class Result, class Range >
        Result call(Range& rng) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            return Result(rng);
        }
    };

    typedef egg::function<baby> type;
};


template<
    class Value      = boost::use_default,
    class Traversal  = boost::use_default,
    class Reference  = boost::use_default,
    class Difference = boost::use_default
>
struct xp_make_indirected :
    tp_make_indirected<Value, Traversal, Reference, Difference>::type
{ };


PSTADE_OVEN_BABY_TO_ADAPTOR(indirected, (tp_make_indirected<>::baby))


} } // namespace pstade::oven


#endif
