#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_DETAIL_FUNCTIONAL2_HPP
#define BOOST_EGG_DETAIL_FUNCTIONAL2_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/facilities/identity.hpp>
#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/egg/bll/return_type.hpp>
#include <boost/egg/by_perfect.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/detail/adl_barrier.hpp>
#include <boost/egg/detail/derived_from.hpp>
#include <boost/egg/detail/if_use_default.hpp>
#include <boost/egg/detail/pp_array_iterate.hpp>


namespace boost { namespace egg {


#define id BOOST_PP_IDENTITY


#define entries \
    (20,( \
        (id(<<),  shift_left,    lambda::bitwise_action<lambda::leftshift_action>), \
        (id(>>),  shift_right,   lambda::bitwise_action<lambda::rightshift_action>), \
        (id(*),   multiplies,    lambda::arithmetic_action<lambda::multiply_action>), \
        (id(/),   divides,       lambda::arithmetic_action<lambda::divide_action>), \
        (id(%),   modulus,       lambda::arithmetic_action<lambda::remainder_action>), \
        (id(+),   plus,          lambda::arithmetic_action<lambda::plus_action>), \
        (id(-),   minus,         lambda::arithmetic_action<lambda::minus_action>), \
        (id(<),   less,          lambda::relational_action<lambda::less_action>), \
        (id(>),   greater,       lambda::relational_action<lambda::greater_action>), \
        (id(<=),  less_equal,    lambda::relational_action<lambda::lessorequal_action>), \
        (id(>=),  greater_equal, lambda::relational_action<lambda::greaterorequal_action>), \
        (id(==),  equal_to,      lambda::relational_action<lambda::equal_action>), \
        (id(!=),  not_equal_to,  lambda::relational_action<lambda::notequal_action>), \
        (id(||),  logical_or,    lambda::logical_action<lambda::or_action>), \
        (id(&&),  logical_and,   lambda::logical_action<lambda::and_action>), \
        (id(&),   bitwise_and,   lambda::bitwise_action<lambda::and_action>), \
        (id(|),   bitwise_or,    lambda::bitwise_action<lambda::or_action>), \
        (id(^),   bitwise_xor,   lambda::bitwise_action<lambda::xor_action>), \
        (BOOST_PP_COMMA, comma,  lambda::other_action<lambda::comma_action>), \
        (id(->*), mem_ptr,       lambda::other_action<lambda::member_pointer_action>) \
    ) ) \
/**/
    #define  BOOST_EGG_PP_ARRAY_ITERATION_PARAMS (entries, <boost/egg/detail/functional2.hpp>)
    #include BOOST_EGG_PP_ARRAY_ITERATE()
#undef  entries


#define entries \
    (10,( \
        (id(<<=), shift_left_assign,   lambda::bitwise_assignment_action<lambda::leftshift_action>), \
        (id(>>=), shift_right_assign,  lambda::bitwise_assignment_action<lambda::rightshift_action>), \
        (id(*=),  multiplies_assign,   lambda::arithmetic_assignment_action<lambda::multiply_action>), \
        (id(/=),  divides_assign,      lambda::arithmetic_assignment_action<lambda::divide_action>), \
        (id(%=),  modulus_assign,      lambda::arithmetic_assignment_action<lambda::remainder_action>), \
        (id(+=),  plus_assign,         lambda::arithmetic_assignment_action<lambda::plus_action>), \
        (id(-=),  minus_assign,        lambda::arithmetic_assignment_action<lambda::minus_action>), \
        (id(&=),  bitwise_and_assign,  lambda::bitwise_assignment_action<lambda::and_action>), \
        (id(|=),  bitwise_or_assign,   lambda::bitwise_assignment_action<lambda::or_action>), \
        (id(^=),  bitwise_xor_assign,  lambda::bitwise_assignment_action<lambda::xor_action>) \
    ) ) \
/**/
    #define  BOOST_EGG_PP_ARRAY_ITERATION_PARAMS (entries, <boost/egg/detail/functional2.hpp>)
    #include BOOST_EGG_PP_ARRAY_ITERATE()
#undef  entries


#undef  id


} } // namespace boost::egg


#endif
#else
#define entry BOOST_EGG_PP_ARRAY_ITERATION()
#define op   BOOST_PP_TUPLE_ELEM(3, 0, entry)
#define name BOOST_PP_TUPLE_ELEM(3, 1, entry)
#define act  BOOST_PP_TUPLE_ELEM(3, 2, entry)


    namespace BOOST_PP_CAT(name, _detail) {


        template<class Return>
        struct little
        {
            template<class Me, class A1, class A2>
            struct apply :
                details::eval_if_use_default< Return,
                    lambda::return_type_2<act, A1, A2>
                >
            { };

            template<class Re, class A1, class A2>
            Re call(A1 &a1, A2 &a2) const
            {
                return a1 op() a2;
            }
        };


    } // namespace BOOST_PP_CAT(name, _detail)


    template<class Return = use_default, class Strategy = by_perfect>
    struct BOOST_PP_CAT(X_, name) : details::derived_from<
        function<BOOST_PP_CAT(name, _detail)::little<Return>, Strategy> >
    { };

BOOST_EGG_ADL_BARRIER(functional2) {
    typedef BOOST_PP_CAT(X_, name)<>::base_class BOOST_PP_CAT(T_, name);
    BOOST_EGG_CONST((BOOST_PP_CAT(T_, name)), name) = {{}};
}


#undef  act
#undef  name
#undef  op
#undef  entry
#endif
