#ifndef PSTADE_OVEN_UNROLLED_FOR_EACH_HPP
#define PSTADE_OVEN_UNROLLED_FOR_EACH_HPP
#include "../detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or for_each at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/specified.hpp>
#include "./applier.hpp"
#include "./concepts.hpp"
#include "./distance.hpp"
#include "./traversal_tags.hpp"
#include "./unrolled_copy.hpp"


namespace pstade { namespace oven {


namespace unrolled_for_each_detail {


    template< class N >
    struct baby
    {
        template< class Myself, class Range, class Function >
        struct apply
        {
            typedef Function type;
        };

        template< class Result, class Range, class Function >
        Result call(Range& rng, Function& fun) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            BOOST_ASSERT(is_random_access(rng) ? N::value == distance(rng) : true);

            return X_unrolled_copy<N>()(rng, applier(fun)).function();
        }
    };


} // namespace unrolled_for_each_detail


template< class N >
struct X_unrolled_for_each :
    egg::function< unrolled_for_each_detail::baby<N> >
{ };

template< int N >
struct X_unrolled_for_each_c :
    X_unrolled_for_each< boost::mpl::int_<N> >
{ };


#define  PSTADE_EGG_SPECIFIED_PARAMS (unrolled_for_each, X_unrolled_for_each, (class), (2))
#include PSTADE_EGG_SPECIFIED()

#define  PSTADE_EGG_SPECIFIED_PARAMS (unrolled_for_each_c, X_unrolled_for_each_c, (int), (2))
#include PSTADE_EGG_SPECIFIED()


} } // namespace pstade::oven


#endif
