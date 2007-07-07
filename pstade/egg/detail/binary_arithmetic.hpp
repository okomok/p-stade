#ifndef PSTADE_EGG_DETAIL_BINARY_ARITHMETIC_HPP
#define PSTADE_EGG_DETAIL_BINARY_ARITHMETIC_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// std::unary/binary_negate requires 'Predicate'
// to be Adaptable, which seems to be obsolete.
// See [1] at Boost.Phoenix2 about deduction of arithmetic results.
//
// [1] <boost/spirit/phoenix/detail/type_deduction.hpp>


#include <boost/mpl/if.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/type_traits/detail/yes_no_type.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/pod_constant.hpp>
#include "../function.hpp"


namespace pstade { namespace egg { namespace detail {


    struct error_failed_to_deduce_arithmetic_operation_result_type;


    template< class X, class Y >
    boost::type_traits::yes_type are_you_x(X const&);

    template< class X, class Y >
    boost::type_traits::no_type  are_you_x(Y const&, typename disable_if< boost::is_same<X, Y> >::type = 0);

    template< class X, class Y >
    error_failed_to_deduce_arithmetic_operation_result_type are_you_x(...);


#define PSTADE_EGG_BINARY_ARITHMETIC(F, Op) \
    template<class X, class Y> \
    struct BOOST_PP_CAT(result_of_, F) \
    { \
    private: \
        typedef typename boost::remove_const<X>::type x_t; \
        typedef typename boost::remove_const<Y>::type y_t; \
        \
        static x_t x; \
        static y_t y; \
        \
        static bool const is_x = \
            sizeof( detail::are_you_x<x_t, y_t>(x Op y) ) == sizeof(boost::type_traits::yes_type); \
        \
    public: \
        typedef typename \
            boost::mpl::if_c< is_x, \
                x_t, y_t \
            >::type \
        type; \
    }; \
    \
    struct BOOST_PP_CAT(baby_, F) \
    { \
        template<class Myself, class X, class Y> \
        struct apply : \
            BOOST_PP_CAT(result_of_, F)<X, Y> \
        { }; \
        \
        template<class Result, class X, class Y> \
        Result call(X& x, Y& y) const \
        { \
            return x Op y; \
        } \
    }; \
    \
    typedef function<BOOST_PP_CAT(baby_, F)> BOOST_PP_CAT(op_, F); \
    PSTADE_ADL_BARRIER(F) { \
        PSTADE_POD_CONSTANT((BOOST_PP_CAT(op_, F)), F) = { {} }; \
    } \
/**/


} } } // namespace pstade::egg::detail


#endif
