#ifndef PSTADE_AT_HPP
#define PSTADE_AT_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy tuple_at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Provides Boost.Fusion-like interfaces to Boost.Tuple,
// which maybe will come with Boost v1.35.
//
// 'tuple_value_at', whose funny name comes from Boost.Fusion,
// can return reference type.
//
// 'std::pair' can't hold reference type
// because of the reference-to-reference problem.


#include <boost/mpl/int.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/affect.hpp>
#include <pstade/callable.hpp>
#include <pstade/cast_function.hpp>
#include <pstade/constant.hpp>


namespace pstade {


    // at_first

    template<class Pair>
    struct value_at_first
    {
        typedef typename Pair::first_type type;
    };

    struct op_at_first :
        callable<op_at_first>
    {
        template<class Myself, class Pair>
        struct apply :
            affect<Pair&, typename value_at_first<Pair>::type>
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
    struct value_at_second
    {
        typedef typename Pair::second_type type;
    };

    struct op_at_second :
        callable<op_at_second>
    {
        template<class Myself, class Pair>
        struct apply :
            affect<Pair&, typename value_at_second<Pair>::type>
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
    struct tuple_value_at :
        boost::tuples::element<N::value, typename boost::remove_cv<Tuple>::type>
    { };

    template<class N>
    struct op_tuple_at :
        callable< op_tuple_at<N> >
    {
        template<class Myself, class Tuple>
        struct apply :
            affect<Tuple&, typename tuple_value_at<Tuple, N>::type>
        { };

        template<class Result, class Tuple>
        Result call(Tuple& t) const
        {
            return boost::tuples::get<N::value>(t);
        }
    };

    PSTADE_CAST_FUNCTION(tuple_at, op_tuple_at, class)


    // tuple_at_c

    template<class Tuple, int N>
    struct tuple_value_at_c :
        tuple_value_at< Tuple, boost::mpl::int_<N> >
    { };

    template<int N>
    struct op_tuple_at_c :
        op_tuple_at< boost::mpl::int_<N> >
    { };

    PSTADE_CAST_FUNCTION(tuple_at_c, op_tuple_at_c, int)


} // namespace pstade


#endif
