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


namespace indirected_detail {


    template< class Value, class Traversal, class Reference, class Difference >
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


    template< class Value, class Traversal, class Reference, class Difference >
    struct pod_ 
    {
        typedef egg::function< baby<Value, Traversal, Reference, Difference> > type;
    };


} // namespace indirected_detail


template<
    class Value      = boost::use_default,
    class Traversal  = boost::use_default,
    class Reference  = boost::use_default,
    class Difference = boost::use_default
>
struct X_make_indirected :
    indirected_detail::pod_<Value, Traversal, Reference, Difference>::type
{
    typedef typename indirected_detail::pod_<Value, Traversal, Reference, Difference>::type pod_type;
};


PSTADE_OVEN_BABY_TO_ADAPTOR(indirected, (X_make_indirected<>::pod_type::baby_type))


} } // namespace pstade::oven


#endif
