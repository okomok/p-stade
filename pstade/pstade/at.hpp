#ifndef PSTADE_AT_HPP
#define PSTADE_AT_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy tuple_at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/int.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/affect.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/specified.hpp>


#include <boost/version.hpp>
#if BOOST_VERSION >= 103500
    #include <boost/fusion/sequence/intrinsic/at.hpp>
    #include <boost/fusion/sequence/intrinsic/value_at.hpp>
#endif


namespace pstade {


    // at_first

    template<class Pair>
    struct element_at_first
    {
        typedef typename Pair::first_type type;
    };

    struct op_at_first :
        callable<op_at_first>
    {
        template<class Myself, class Pair>
        struct apply :
            affect<Pair&, typename element_at_first<Pair>::type>
        { };

        template<class Result, class Pair>
        Result call(Pair& p) const
        {
            return p.first;
        }
    };

    PSTADE_CONSTANT(at_first, (op_at_first))


    // at_second

    template<class Pair>
    struct element_at_second
    {
        typedef typename Pair::second_type type;
    };

    struct op_at_second :
        callable<op_at_second>
    {
        template<class Myself, class Pair>
        struct apply :
            affect<Pair&, typename element_at_second<Pair>::type>
        { };

        template<class Result, class Pair>
        Result call(Pair& p) const
        {
            return p.second;
        }
    };

    PSTADE_CONSTANT(at_second, (op_at_second))


    // tuple_at

    template<class Tuple, class N>
    struct tuple_element_at :
        boost::tuples::element<N::value, typename boost::remove_cv<Tuple>::type>
    { };

    template<class N>
    struct op_tuple_at :
        callable< op_tuple_at<N> >
    {
        template<class Myself, class Tuple>
        struct apply :
            affect<Tuple&, typename tuple_element_at<Tuple, N>::type>
        { };

        template<class Result, class Tuple>
        Result call(Tuple& t) const
        {
            return boost::tuples::get<N::value>(t);
        }
    };

    PSTADE_SPECIFIED1(tuple_at, op_tuple_at, 1)


    // tuple_at_c

    template<class Tuple, int N>
    struct tuple_element_at_c :
        tuple_element_at< Tuple, boost::mpl::int_<N> >
    { };

    template<int N>
    struct op_tuple_at_c :
        op_tuple_at< boost::mpl::int_<N> >
    { };

    PSTADE_SPECIFIED1(tuple_at_c, op_tuple_at_c, (int))



#if BOOST_VERSION >= 103500


    // fusion_at

    template<class FusionSeq, class N>
    struct fusion_element_at :
        boost::fusion::result_of::value_at<FusionSeq, N>
    { };

    template<class N>
    struct op_fusion_at :
        callable< op_fusion_at<N> >
    {
        template<class Myself, class FusionSeq>
        struct apply :
            affect<FusionSeq&, typename fusion_element_at<FusionSeq, N>::type>
        { };

        template<class Result, class FusionSeq>
        Result call(FusionSeq& s) const
        {
            return boost::fusion::at<N>(s);
        }
    };

    PSTADE_SPECIFIED1(fusion_at, op_fusion_at, 1)


    // fusion_at_c

    template<class FusionSeq, int N>
    struct fusion_element_at_c :
        fusion_element_at< FusionSeq, boost::mpl::int_<N> >
    { };

    template<int N>
    struct op_fusion_at_c :
        op_fusion_at< boost::mpl::int_<N> >
    { };

    PSTADE_SPECIFIED1(fusion_at_c, op_fusion_at_c, (int))


#endif // BOOST_VERSION >= 103500


} // namespace pstade


#endif
