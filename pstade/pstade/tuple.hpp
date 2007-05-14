#ifndef PSTADE_TUPLE_HPP
#define PSTADE_TUPLE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy tuple_at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// 'tuple_get' works with FusionForwardSequence.


#include <boost/version.hpp>
#if BOOST_VERSION >= 103500
    #define PSTADE_TUPLE_FUSION_SUPPORTED
#endif

#include <boost/mpl/at.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/size.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/affect.hpp>
#include <pstade/apple/is_pair.hpp>
#include <pstade/apple/pair_fwd.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/specified.hpp>

#if defined(PSTADE_TUPLE_FUSION_SUPPORTED)
    #include <boost/fusion/iterator/advance.hpp>
    #include <boost/fusion/iterator/deref.hpp>
    #include <boost/fusion/sequence/adapted/boost_tuple.hpp> // lets 'boost::tuple' be FusionSequence
    #include <boost/fusion/sequence/adapted/std_pair.hpp> // lets 'std::pair' be FusionSequence
    #include <boost/fusion/sequence/intrinsic/begin.hpp>
    #include <boost/fusion/sequence/intrinsic/mpl.hpp> // lets FusionSequence be MPLSequence
#endif


namespace pstade {


    namespace tuple_detail {


        namespace mpl = boost::mpl;


        // boost::tuple' and 'std::pair' is NOT a MPLSequence.


        template<class Tuple>
        struct is_boost_tuple :
            mpl::false_
        { };

        template<
            class T0, class T1, class T2, class T3, class T4, 
            class T5, class T6, class T7, class T8, class T9
        >
        struct is_boost_tuple< boost::tuples::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> > :
            mpl::true_
        { };

        template< class Head, class Tail>
        struct is_boost_tuple< boost::tuples::cons<Head, Tail> > :
            mpl::true_
        { };


        template<class N, class Tuple>
        struct element :
            mpl::eval_if< is_boost_tuple<Tuple>,
                boost::tuples::element<N::value, Tuple>,
                mpl::at<Tuple, N>
            >
        { };

        template<class N, class T, class U>
        struct element< N, std::pair<T, U> > :
            mpl::if_< mpl::equal_to<mpl::int_<0>, N>,
                T,
                U
            >
        { };


        template<class Tuple>
        struct boost_tuple_size :
            mpl::int_<boost::tuples::length<Tuple>::value>
        { };


        template<class Tuple>
        struct size :
            mpl::eval_if< is_boost_tuple<Tuple>,
                boost_tuple_size<Tuple>,
                mpl::size<Tuple>
            >::type
        { };

        template<class T, class U>
        struct size< std::pair<T, U> > :
            mpl::int_<2>
        { };


        template<class Result, class N>
        struct pair_get;

        template<class Result>
        struct pair_get< Result, mpl::int_<0> >
        {
            template< class Pair >
            static Result call(Pair& p)
            {
                return p.first;
            }
        };

        template<class Result>
        struct pair_get< Result, mpl::int_<1> >
        {
            template< class Pair >
            static Result call(Pair& p)
            {
                return p.second;
            }
        };


    } // namespace tuple_detail


    template<class N, class Tuple>
    struct tuple_element :
        tuple_detail::element<N, typename boost::remove_cv<Tuple>::type>
    { };


    template<int N, class Tuple>
    struct tuple_element_c :
        tuple_element<boost::mpl::int_<N>, Tuple>
    { };


    template<class Tuple>
    struct tuple_size :
        tuple_detail::size<typename boost::remove_cv<Tuple>::type>
    { };


    template<class N>
    struct op_tuple_get :
        callable< op_tuple_get<N> >
    {
        template<class Myself, class Tuple>
        struct apply :
            affect<Tuple&, typename tuple_element<N, Tuple>::type>
        { };

        template<class Result, class Tuple>
        Result call(Tuple& t
#if !defined(PSTADE_TUPLE_FUSION_SUPPORTED)
            , typename disable_if< apple::is_pair<Tuple> >::type = 0
#endif
        ) const
        {
#if defined(PSTADE_TUPLE_FUSION_SUPPORTED)
            namespace fusion = boost::fusion;
            return fusion::deref(fusion::advance<N>(fusion::begin(t)));
#else
            return boost::tuples::get<N::value>(t);
#endif
        }

#if !defined(PSTADE_TUPLE_FUSION_SUPPORTED)
        template<class Result, class Pair>
        Result call(Pair& p,
            typename enable_if< apple::is_pair<Pair> >::type = 0) const
        {
            return tuple_detail::pair_get< Result, boost::mpl::int_<N::value> >::call(p);
        }
#endif
    };

    PSTADE_SPECIFIED1(tuple_get, op_tuple_get, 1)


    template<int N>
    struct op_tuple_get_c :
        op_tuple_get< boost::mpl::int_<N> >
    { };

    PSTADE_SPECIFIED1(tuple_get_c, op_tuple_get_c, (int))


} // namespace pstade


#endif
