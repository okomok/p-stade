#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_FUNCTIONAL2_HPP
#define PSTADE_EGG_DETAIL_FUNCTIONAL2_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/array/elem.hpp>
#include <boost/preprocessor/array/size.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/pod_constant.hpp>
#include "../bll/return_type.hpp"
#include "../by_perfect.hpp"


namespace pstade { namespace egg {


    struct little_comma
    {
        template<class Myself, class A1, class A2>
        struct apply :
            boost::lambda::return_type_2<boost::lambda::other_action<boost::lambda::comma_action>, A1, A2>
        { };

        template<class Result, class A1, class A2>
        Result call(A1& a1, A2& a2) const
        {
            // I have a feeling that egg::forward shouldn't be called,
            // because Boost.Lambda doesn't care rvalue.
            return a1 , a2;
        }
    };

    template<class Strategy = by_perfect>
    struct X_comma :
        function<little_comma, Strategy>
    { };

    PSTADE_ADL_BARRIER(functional2) {
        typedef X_comma<>::function_type T_comma;
        PSTADE_POD_CONSTANT((T_comma), comma) = {{}};
    }


#define PSTADE_entries \
    (19,( \
        (<<,  shift_left,    boost::lambda::bitwise_action<boost::lambda::leftshift_action>), \
        (>>,  shift_right,   boost::lambda::bitwise_action<boost::lambda::rightshift_action>), \
        (*,   multiplies,    boost::lambda::arithmetic_action<boost::lambda::multiply_action>), \
        (/,   divides,       boost::lambda::arithmetic_action<boost::lambda::divide_action>), \
        (%,   modulus,       boost::lambda::arithmetic_action<boost::lambda::remainder_action>), \
        (+,   plus,          boost::lambda::arithmetic_action<boost::lambda::plus_action>), \
        (-,   minus,         boost::lambda::arithmetic_action<boost::lambda::minus_action>), \
        (<,   less,          boost::lambda::relational_action<boost::lambda::less_action>), \
        (>,   greater,       boost::lambda::relational_action<boost::lambda::greater_action>), \
        (<=,  less_equal,    boost::lambda::relational_action<boost::lambda::lessorequal_action>), \
        (>=,  greater_equal, boost::lambda::relational_action<boost::lambda::greaterorequal_action>), \
        (==,  equal_to,      boost::lambda::relational_action<boost::lambda::equal_action>), \
        (!=,  not_equal_to,  boost::lambda::relational_action<boost::lambda::notequal_action>), \
        (||,  logical_or,    boost::lambda::logical_action<boost::lambda::or_action>), \
        (&&,  logical_and,   boost::lambda::logical_action<boost::lambda::and_action>), \
        (&,   bitwise_and,   boost::lambda::bitwise_action<boost::lambda::and_action>), \
        (|,   bitwise_or,    boost::lambda::bitwise_action<boost::lambda::or_action>), \
        (^,   bitwise_xor,   boost::lambda::bitwise_action<boost::lambda::xor_action>), \
        (->*, mem_ptr,       boost::lambda::other_action<boost::lambda::member_pointer_action>) \
    ) ) \
/**/
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC(BOOST_PP_ARRAY_SIZE(PSTADE_entries)), <pstade/egg/detail/functional2.hpp>))
    #include BOOST_PP_ITERATE()
#undef  PSTADE_entries


#define PSTADE_entries \
    (10,( \
        (<<=, shift_left_assign,   boost::lambda::bitwise_assignment_action<boost::lambda::leftshift_action>), \
        (>>=, shift_right_assign,  boost::lambda::bitwise_assignment_action<boost::lambda::rightshift_action>), \
        (*=,  multiplies_assign,   boost::lambda::arithmetic_assignment_action<boost::lambda::multiply_action>), \
        (/=,  divides_assign,      boost::lambda::arithmetic_assignment_action<boost::lambda::divide_action>), \
        (%=,  modulus_assign,      boost::lambda::arithmetic_assignment_action<boost::lambda::remainder_action>), \
        (+=,  plus_assign,         boost::lambda::arithmetic_assignment_action<boost::lambda::plus_action>), \
        (-=,  minus_assign,        boost::lambda::arithmetic_assignment_action<boost::lambda::minus_action>), \
        (&=,  bitwise_and_assign,  boost::lambda::bitwise_assignment_action<boost::lambda::and_action>), \
        (|=,  bitwise_or_assign,   boost::lambda::bitwise_assignment_action<boost::lambda::or_action>), \
        (^=,  bitwise_xor_assign,  boost::lambda::bitwise_assignment_action<boost::lambda::xor_action>) \
    ) ) \
/**/
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC(BOOST_PP_ARRAY_SIZE(PSTADE_entries)), <pstade/egg/detail/functional2.hpp>))
    #include BOOST_PP_ITERATE()
#undef  PSTADE_entries


} } // namespace pstade::egg


#endif
#else
#define entry BOOST_PP_ARRAY_ELEM(BOOST_PP_ITERATION(), PSTADE_entries)
#define op   BOOST_PP_TUPLE_ELEM(3, 0, entry)
#define name BOOST_PP_TUPLE_ELEM(3, 1, entry)
#define act  BOOST_PP_TUPLE_ELEM(3, 2, entry)


    struct BOOST_PP_CAT(little_, name)
    {
        template<class Myself, class A1, class A2>
        struct apply :
            boost::lambda::return_type_2<act, A1, A2>
        { };

        template<class Result, class A1, class A2>
        Result call(A1& a1, A2& a2) const
        {
            return a1 op a2;
        }
    };

    template<class Strategy = by_perfect>
    struct BOOST_PP_CAT(X_, name) :
        function<BOOST_PP_CAT(little_, name), Strategy>
    { };

    PSTADE_ADL_BARRIER(functional2) {
        typedef BOOST_PP_CAT(X_, name)<>::function_type BOOST_PP_CAT(T_, name);
        PSTADE_POD_CONSTANT((BOOST_PP_CAT(T_, name)), name) = {{}};
    }


#undef  act
#undef  name
#undef  op
#undef  entry
#endif
