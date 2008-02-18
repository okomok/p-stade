#ifndef BOOST_EGG_GET_HPP
#define BOOST_EGG_GET_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/int.hpp>
#include <boost/egg/by_perfect.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_HAS_FUSIONS
#include <boost/egg/detail/adl_barrier.hpp>
#include <boost/egg/detail/affect.hpp>
#include <boost/egg/detail/enable_if.hpp>
#include <boost/egg/detail/is_std_pair.hpp>
#include <boost/egg/detail/tuple_get.hpp>
#include <boost/egg/specified.hpp>

#if defined(BOOST_EGG_HAS_FUSIONS)
    #include <boost/fusion/include/advance.hpp>
    #include <boost/fusion/include/begin.hpp>
    #include <boost/fusion/include/deref.hpp>
    #include <boost/egg/detail/is_fusion_sequence.hpp>
#endif


namespace boost { namespace egg {


    namespace details {


#if defined(BOOST_EGG_HAS_FUSIONS)

        // FusionSequence
        //

        template<class N, class Tuple>
        struct tuple_get_impl<N, Tuple,
            typename enable_if< is_fusion_sequence<Tuple> >::type>
        {
            typedef typename
                fusion::result_of::deref<
                    typename fusion::result_of::advance<
                        typename fusion::result_of::begin<Tuple>::type,
                        N
                    >::type
                >::type
            result_type;

            result_type operator()(Tuple &t) const
            {
                namespace fusion = fusion;
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
                affect<Pair &, typename Pair::first_type>::type
            result_type;

            result_type operator()(Pair &p) const
            {
                return p.first;
            }
        };

        template<class Pair>
        struct pair_get_aux<1, Pair>
        {
            typedef typename
                affect<Pair &, typename Pair::second_type>::type
            result_type;

            result_type operator()(Pair &p) const
            {
                return p.second;
            }
        };

        template<class N, class Tuple>
        struct tuple_get_impl<N, Tuple, typename enable_if< is_std_pair<Tuple> >::type> :
            pair_get_aux<N::value, Tuple>
        { };


    } // namespace details


    template<class N>
    struct X_get :
        details::X_tuple_get<N>
    { };

BOOST_EGG_ADL_BARRIER(get) {
    #define  BOOST_EGG_SPECIFIED_PARAMS (get, X_get, (class), (1))
    #include BOOST_EGG_SPECIFIED()
}

    template<int N>
    struct X_get_c :
        X_get< mpl::int_<N> >
    { };

    #define  BOOST_EGG_SPECIFIED_PARAMS (get_c, X_get_c, (int), (1))
    #include BOOST_EGG_SPECIFIED()


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
