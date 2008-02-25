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
#include <boost/egg/detail/const_overloaded.hpp>
#include <boost/egg/detail/enable_if.hpp>
#include <boost/egg/detail/is_std_pair.hpp>
#include <boost/egg/detail/tuple_get.hpp>

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
            typename enable_if_< is_fusion_sequence<Tuple> >::type>
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
        struct tuple_get_impl<N, Tuple, typename enable_if_< is_std_pair<Tuple> >::type> :
            pair_get_aux<N::value, Tuple>
        { };


    } // namespace details


    template<class N>
    struct X_get :
        details::X_tuple_get<N>
    { };

BOOST_EGG_ADL_BARRIER(get) {
    template<class N, class Tuple> inline
    typename details::tuple_get_impl<N, Tuple>::result_type
    get(Tuple &t BOOST_EGG_CONST_OVERLOADED(Tuple))
    {
        return X_get<N>()(t);
    }

    template<class N, class Tuple> inline
    typename details::tuple_get_impl<N, Tuple const>::result_type
    get(Tuple const &t)
    {
        return X_get<N>()(t);
    }
}

    template<int N>
    struct X_get_c :
        X_get< mpl::int_<N> >
    { };

    template<int N, class Tuple> inline
    typename details::tuple_get_impl<mpl::int_<N>, Tuple>::result_type
    get_c(Tuple &t BOOST_EGG_CONST_OVERLOADED(Tuple))
    {
        return X_get_c<N>()(t);
    }

    template<int N, class Tuple> inline
    typename details::tuple_get_impl<mpl::int_<N>, Tuple const>::result_type
    get_c(Tuple const &t)
    {
        return X_get_c<N>()(t);
    }


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
