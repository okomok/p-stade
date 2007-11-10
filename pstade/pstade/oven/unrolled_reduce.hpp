#ifndef PSTADE_OVEN_UNROLLED_REDUCE_HPP
#define PSTADE_OVEN_UNROLLED_REDUCE_HPP
#include "../detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or reduce at
// http://www.boost.org/LICENSE_1_0.txt)


#include <utility> // pair
#include <boost/assert.hpp>
#include <boost/mpl/int.hpp>
#include <boost/next_prior.hpp>
#include <boost/range/begin.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/specified.hpp>
#include "./concepts.hpp"
#include "./distance.hpp"
#include "./traversal_tags.hpp"


namespace pstade { namespace oven {


namespace unrolled_reduce_detail {


    namespace here = unrolled_reduce_detail;


    template< class BinaryFun, class ItStPair > inline
    ItStPair aux(boost::mpl::int_<0>, BinaryFun fun, ItStPair is)
    {
        return is;
    }

    template< class BinaryFun, class ItStPair > inline
    ItStPair aux(boost::mpl::int_<1>, BinaryFun fun, ItStPair is)
    {
        return std::make_pair(boost::next(is.first), fun(is.second, *is.first) );
    }

    template< class BinaryFun, class ItStPair, int N > inline
    ItStPair aux(boost::mpl::int_<N>, BinaryFun fun, ItStPair is)
    {
        static int const leftN = N/2;
        static int const rightN = N - leftN;

        return here::aux(
            boost::mpl::int_<rightN>(), fun,
            here::aux(boost::mpl::int_<leftN>(), fun, is)
        );
    }


    template< class N >
    struct baby
    {
        template< class Myself, class Range, class State, class BinaryFun >
        struct apply :
            boost::remove_cv<State>
        { };

        template< class Result, class Range, class State, class BinaryFun >
        Result call(Range& rng, State& init, BinaryFun& fun) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            BOOST_ASSERT(is_random_access(rng) ? N::value == distance(rng) : true);

            return here::aux(
                boost::mpl::int_<N::value>(),
                fun, 
                std::make_pair(boost::begin(rng), init)
            ).second;
        }
    };


} // namespace unrolled_reduce_detail


template< class N >
struct pod_of_unrolled_reduce
{
    typedef egg::function< unrolled_reduce_detail::baby<N> > type;
};


template< class N >
struct X_unrolled_reduce :
    pod_of_unrolled_reduce<N>::type
{ };

template< int N >
struct X_unrolled_reduce_c :
    X_unrolled_reduce< boost::mpl::int_<N> >
{ };


#define  PSTADE_EGG_SPECIFIED_PARAMS ((3), unrolled_reduce, X_unrolled_reduce, (class))
#include PSTADE_EGG_SPECIFIED()

#define  PSTADE_EGG_SPECIFIED_PARAMS ((3), unrolled_reduce_c, X_unrolled_reduce_c, (int))
#include PSTADE_EGG_SPECIFIED()


} } // namespace pstade::oven


#endif
