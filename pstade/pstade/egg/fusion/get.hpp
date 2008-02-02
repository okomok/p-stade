#ifndef PSTADE_EGG_FUSION_GET_HPP
#define PSTADE_EGG_FUSION_GET_HPP
#include "../detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/int.hpp>
#include <boost/tuple/tuple.hpp>
#include <pstade/affect.hpp>
#include <pstade/apple/is_pair.hpp>
#include <pstade/enable_if.hpp>
#include "../by_perfect.hpp"
#include "../config.hpp" // PSTADE_EGG_HAS_FUSIONS
#include "../specified.hpp"
#include "./element.hpp"

#if defined(PSTADE_EGG_HAS_FUSIONS)
    #include <boost/fusion/include/advance.hpp>
    #include <boost/fusion/include/begin.hpp>
    #include <boost/fusion/include/boost_tuple.hpp> // lets 'boost::tuple' be FusionSequence
    #include <boost/fusion/include/deref.hpp>
    #include <boost/fusion/include/mpl.hpp> // lets FusionSequence be MPLSequence
    #include <boost/fusion/include/std_pair.hpp> // lets 'std::pair' be FusionSequence
#endif


namespace pstade { namespace egg {


    namespace fusion_get_detail {


        template<class Re, class N>
        struct pair_get;

        template<class Re>
        struct pair_get< Re, boost::mpl::int_<0> >
        {
            template< class Pair >
            static Re call(Pair& p)
            {
                return p.first;
            }
        };

        template<class Re>
        struct pair_get< Re, boost::mpl::int_<1> >
        {
            template< class Pair >
            static Re call(Pair& p)
            {
                return p.second;
            }
        };


        template<class N>
        struct little
        {
            template<class Me, class Tuple>
            struct apply :
#if defined(PSTADE_EGG_HAS_FUSIONS)
                boost::fusion::result_of::deref<
                    typename boost::fusion::result_of::advance<
                        typename boost::fusion::result_of::begin<Tuple>::type,
                        N
                    >::type
                >
#else
                affect<Tuple&, typename fusion_element<N, Tuple>::type>
#endif
            { };

            template<class Re, class Tuple>
            Re call(Tuple& t
#if !defined(PSTADE_EGG_HAS_FUSIONS)
                , typename disable_if< apple::is_pair<Tuple> >::type = 0
#endif
            ) const
            {
#if defined(PSTADE_EGG_HAS_FUSIONS)
                namespace fusion = boost::fusion;
                return fusion::deref(fusion::advance<N>(fusion::begin(t)));
#else
                return boost::tuples::get<N::value>(t);
#endif
            }

#if !defined(PSTADE_EGG_HAS_FUSIONS)
            template<class Re, class Pair>
            Re call(Pair& p,
                typename enable_if< apple::is_pair<Pair> >::type = 0) const
            {
                return pair_get< Re, boost::mpl::int_<N::value> >::call(p);
            }
#endif
        };


    } // namespace fusion_get_detail


    template<class N>
    struct X_fusion_get :
        function<fusion_get_detail::little<N>, by_perfect>
    { };

    #define  PSTADE_EGG_SPECIFIED_PARAMS (fusion_get, X_fusion_get, (class), (1))
    #include PSTADE_EGG_SPECIFIED()


    template<int N>
    struct X_fusion_get_c :
        X_fusion_get< boost::mpl::int_<N> >
    { };

    #define  PSTADE_EGG_SPECIFIED_PARAMS (fusion_get_c, X_fusion_get_c, (int), (1))
    #include PSTADE_EGG_SPECIFIED()


} } // namespace pstade::egg


#endif
