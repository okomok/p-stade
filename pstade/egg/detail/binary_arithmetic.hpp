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
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/type_traits/detail/yes_no_type.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/pod_constant.hpp>
#include "../by_cref.hpp"


#define PSTADE_EGG_BINARY_ARITHMETIC() <pstade/egg/detail/binary_arithmetic_include.hpp>


namespace pstade { namespace egg { namespace detail {


    template<class X, class Y>
    struct error_failed_to_deduce_arithmetic_operation_result_type;


    template<class X, class Y>
    boost::type_traits::yes_type are_you_x(X const&);

    template<class X, class Y>
    boost::type_traits::no_type  are_you_x(Y const&, typename disable_if< boost::is_same<X, Y> >::type = 0);

    template<class X, class Y>
    error_failed_to_deduce_arithmetic_operation_result_type<X, Y> are_you_x(...);


} } } // namespace pstade::egg::detail


#endif
