#ifndef PSTADE_OVEN_UNROLLED_COPY_HPP
#define PSTADE_OVEN_UNROLLED_COPY_HPP
#include "../detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Copyright David Abrahams 2005. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#include <utility> // pair
#include <boost/assert.hpp>
#include <boost/mpl/int.hpp>
#include <boost/range/begin.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/specified.hpp>
#include <pstade/pass_by.hpp>
#include "./concepts.hpp"
#include "./distance.hpp"
#include "./traversal_tags.hpp"


namespace pstade { namespace oven {


namespace unrolled_copy_detail {


    namespace here = unrolled_copy_detail;


    template< class IterPair > inline
    IterPair aux(boost::mpl::int_<0>, IterPair io)
    {
        return io;
    }

    template< class IterPair > inline
    IterPair aux(boost::mpl::int_<1>, IterPair io)
    {
        *io.second++ = *io.first++;
        return std::make_pair(io.first, io.second);
    }

    template< class IterPair, int N > inline
    IterPair aux(boost::mpl::int_<N>, IterPair io)
    {
        static int const leftN = N/2;
        static int const rightN = N - leftN;

        return here::aux(
            boost::mpl::int_<rightN>(),
            here::aux(boost::mpl::int_<leftN>(), io)
        );
    }


    template< class N >
    struct baby
    {
        template< class Myself, class Range, class OutIter >
        struct apply :
            pass_by_value<OutIter>
        { };

        template< class Result, class Range, class OutIter >
        Result call(Range& rng, OutIter& out) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            BOOST_ASSERT(is_random_access(rng) ? N::value == distance(rng) : true);

            return here::aux(
                boost::mpl::int_<N::value>(),
                std::make_pair(boost::begin(rng), out)
            ).second;
        }
    };


} // namespace unrolled_copy_detail


template< class N >
struct X_unrolled_copy :
    egg::function< unrolled_copy_detail::baby<N> >
{ };

template< int N >
struct X_unrolled_copy_c :
    X_unrolled_copy< boost::mpl::int_<N> >
{ };


#define  PSTADE_EGG_SPECIFIED_PARAMS ((2), unrolled_copy, X_unrolled_copy, (class))
#include PSTADE_EGG_SPECIFIED()

#define  PSTADE_EGG_SPECIFIED_PARAMS ((2), unrolled_copy_c, X_unrolled_copy_c, (int))
#include PSTADE_EGG_SPECIFIED()


} } // namespace pstade::oven


#endif
