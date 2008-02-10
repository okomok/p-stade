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


#if defined(PSTADE_EGG_HAS_FUSIONS)


    namespace detail {


        template<class N, class Tuple>
        struct tuple_get_impl<N, class Tuple,
            typename enable_if< is_fusion_sequence<Tuple> >::type>
        {
            typedef typename
                boost::fusion::result_of::deref<
                    typename boost::fusion::result_of::advance<
                        typename boost::fusion::result_of::begin<Tuple>::type,
                        N
                    >::type
                >
            result_type;

            result_type operator()(Tuple& t) const
            {
                namespace fusion = boost::fusion;
                return fusion::deref(fusion::advance<N>(fusion::begin(t)));
            }
        };


    } // namespace detail


#endif // defined(PSTADE_EGG_HAS_FUSIONS)


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
