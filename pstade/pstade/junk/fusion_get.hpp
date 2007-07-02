#ifndef PSTADE_EGG_TUPLE_GET_HPP
#define PSTADE_EGG_TUPLE_GET_HPP
#include "../detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy tuple_at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/int.hpp>
#include <boost/tuple/tuple.hpp>
#include <pstade/affect.hpp>
#include <pstade/apple/is_pair.hpp>
#include <pstade/enable_if.hpp>
#include "../function.hpp"
#include "../specified.hpp"
#include "./element.hpp"

#include <boost/version.hpp>
#if BOOST_VERSION >= 103500
    #define PSTADE_EGG_TUPLE_FUSION_SUPPORTED
#endif

#if defined(PSTADE_EGG_TUPLE_FUSION_SUPPORTED)
    #include <boost/fusion/iterator/advance.hpp>
    #include <boost/fusion/iterator/deref.hpp>
    #include <boost/fusion/sequence/adapted/boost_tuple.hpp> // lets 'boost::tuple' be FusionSequence
    #include <boost/fusion/sequence/adapted/std_pair.hpp> // lets 'std::pair' be FusionSequence
    #include <boost/fusion/sequence/intrinsic/begin.hpp>
    #include <boost/fusion/sequence/intrinsic/mpl.hpp> // lets FusionSequence be MPLSequence
#endif


namespace pstade { namespace egg { namespace tuples {


    namespace get_detail {


        template<class Result, class N>
        struct pair_get;

        template<class Result>
        struct pair_get< Result, boost::mpl::int_<0> >
        {
            template< class Pair >
            static Result call(Pair& p)
            {
                return p.first;
            }
        };

        template<class Result>
        struct pair_get< Result, boost::mpl::int_<1> >
        {
            template< class Pair >
            static Result call(Pair& p)
            {
                return p.second;
            }
        };


        template<class N>
        struct baby
        {
            template<class Myself, class Tuple>
            struct apply :
                affect<Tuple&, typename element<N, Tuple>::type>
            { };

            template<class Result, class Tuple>
            Result call(Tuple& t
    #if !defined(PSTADE_EGG_TUPLE_FUSION_SUPPORTED)
                , typename disable_if< apple::is_pair<Tuple> >::type = 0
    #endif
            ) const
            {
    #if defined(PSTADE_EGG_TUPLE_FUSION_SUPPORTED)
                namespace fusion = boost::fusion;
                return fusion::deref(fusion::advance<N>(fusion::begin(t)));
    #else
                return boost::tuples::get<N::value>(t);
    #endif
            }

    #if !defined(PSTADE_EGG_TUPLE_FUSION_SUPPORTED)
            template<class Result, class Pair>
            Result call(Pair& p,
                typename enable_if< apple::is_pair<Pair> >::type = 0) const
            {
                return pair_get< Result, boost::mpl::int_<N::value> >::call(p);
            }
    #endif
        };


    } // namespace get_detail


    template<class N>
    struct tp_get
    {
        typedef
            function< get_detail::baby<N> >
        type;
    };


    template<class N>
    struct xp_get :
        tp_get<N>::type
    { };

    PSTADE_EGG_SPECIFIED1(get, xp_get, (class))


    template<int N>
    struct xp_get_c :
        tp_get< boost::mpl::int_<N> >::type
    { };

    PSTADE_EGG_SPECIFIED1(get_c, xp_get_c, (int))


} } } // namespace pstade::egg::tuples


#endif
