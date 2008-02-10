#ifndef PSTADE_EGG_GET_HPP
#define PSTADE_EGG_GET_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/int.hpp>
#include <boost/tuple/tuple.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/affect.hpp>
#include <pstade/apple/is_pair.hpp>
#include <pstade/enable_if.hpp>
#include "./by_perfect.hpp"
#include "./config.hpp" // PSTADE_EGG_HAS_FUSIONS
#include "./detail/is_fusion_sequence.hpp"
#include "./detail/tuple_get.hpp"
#include "./specified.hpp"

#if defined(PSTADE_EGG_HAS_FUSIONS)
    #include <boost/fusion/include/advance.hpp>
    #include <boost/fusion/include/begin.hpp>
    #include <boost/fusion/include/deref.hpp>
#endif


namespace pstade { namespace egg {


    namespace detail {


#if defined(PSTADE_EGG_HAS_FUSIONS)

        // FusionSequence
        //

        template<class N, class Tuple>
        struct tuple_get_impl<N, Tuple,
            typename enable_if< is_fusion_sequence<Tuple> >::type>
        {
            typedef typename
                boost::fusion::result_of::deref<
                    typename boost::fusion::result_of::advance<
                        typename boost::fusion::result_of::begin<Tuple>::type,
                        N
                    >::type
                >::type
            result_type;

            result_type operator()(Tuple& t) const
            {
                namespace fusion = boost::fusion;
                return fusion::deref(fusion::advance<N>(fusion::begin(t)));
            }
        };

#endif

        // std::pair
        //

        template<int N, class Pair>
        struct pair_get_aux;

        template<class Pair>
        struct pair_get_aux<0, Pair>
        {
            typedef typename
                affect<Pair&, typename Pair::first_type>::type
            result_type;

            result_type operator()(Pair& p) const
            {
                return p.first;
            }
        };

        template<class Pair>
        struct pair_get_aux<1, Pair>
        {
            typedef typename
                affect<Pair&, typename Pair::second_type>::type
            result_type;

            result_type operator()(Pair& p) const
            {
                return p.second;
            }
        };

        template<class N, class Tuple>
        struct tuple_get_impl<N, Tuple, typename enable_if< apple::is_pair<Tuple> >::type> :
            pair_get_aux<N::value, Tuple>
        { };


    } // namespace detail


    template<class N>
    struct X_get :
        detail::X_tuple_get<N>
    { };

PSTADE_ADL_BARRIER(get) {
    #define  PSTADE_EGG_SPECIFIED_PARAMS (get, X_get, (class), (1))
    #include PSTADE_EGG_SPECIFIED()
}

    template<int N>
    struct X_get_c :
        X_get< boost::mpl::int_<N> >
    { };

    #define  PSTADE_EGG_SPECIFIED_PARAMS (get_c, X_get_c, (int), (1))
    #include PSTADE_EGG_SPECIFIED()


} } // namespace pstade::egg


#include "./detail/suffix.hpp"
#endif
