#ifndef BOOST_EGG_TUPLE_GET_HPP
#define BOOST_EGG_TUPLE_GET_HPP
#include "../detail/prefix.hpp"


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/int.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/egg/pstade/affect.hpp>
#include <boost/egg/pstade/apple/is_pair.hpp>
#include <boost/egg/pstade/enable_if.hpp>
#include "../by_perfect.hpp"
#include "../specified.hpp"
#include "./config.hpp"
#include "./element.hpp"

#if defined(BOOST_EGG_TUPLE_SUPPORTS_FUSION)
    #include <boost/fusion/include/advance.hpp>
    #include <boost/fusion/include/begin.hpp>
    #include <boost/fusion/include/boost_tuple.hpp> // lets 'boost::tuple' be FusionSequence
    #include <boost/fusion/include/deref.hpp>
    #include <boost/fusion/include/mpl.hpp> // lets FusionSequence be MPLSequence
    #include <boost/fusion/include/std_pair.hpp> // lets 'std::pair' be FusionSequence
#endif


namespace pstade { namespace egg {


    namespace tuple_get_detail {


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
        struct little
        {
            template<class Myself, class Tuple>
            struct apply :
#if defined(BOOST_EGG_TUPLE_SUPPORTS_FUSION)
                boost::fusion::result_of::deref<
                    typename boost::fusion::result_of::advance<
                        typename boost::fusion::result_of::begin<Tuple>::type,
                        N
                    >::type
                >
#else
                affect<Tuple&, typename tuple_element<N, Tuple>::type>
#endif
            { };

            template<class Result, class Tuple>
            Result call(Tuple& t
#if !defined(BOOST_EGG_TUPLE_SUPPORTS_FUSION)
                , typename disable_if< apple::is_pair<Tuple> >::type = 0
#endif
            ) const
            {
#if defined(BOOST_EGG_TUPLE_SUPPORTS_FUSION)
                namespace fusion = boost::fusion;
                return fusion::deref(fusion::advance<N>(fusion::begin(t)));
#else
                return boost::tuples::get<N::value>(t);
#endif
            }

#if !defined(BOOST_EGG_TUPLE_SUPPORTS_FUSION)
            template<class Result, class Pair>
            Result call(Pair& p,
                typename enable_if< apple::is_pair<Pair> >::type = 0) const
            {
                return pair_get< Result, boost::mpl::int_<N::value> >::call(p);
            }
#endif
        };


    } // namespace tuple_get_detail


    template<class N>
    struct X_tuple_get :
        function<tuple_get_detail::little<N>, by_perfect>
    { };

    #define  BOOST_EGG_SPECIFIED_PARAMS (tuple_get, X_tuple_get, (class), (1))
    #include BOOST_EGG_SPECIFIED()


    template<int N>
    struct X_tuple_get_c :
        X_tuple_get< boost::mpl::int_<N> >
    { };

    #define  BOOST_EGG_SPECIFIED_PARAMS (tuple_get_c, X_tuple_get_c, (int), (1))
    #include BOOST_EGG_SPECIFIED()


} } // namespace pstade::egg


#endif
