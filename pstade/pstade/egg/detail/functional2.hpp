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
#include <boost/preprocessor/facilities/identity.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/use_default.hpp>
#include "../bll/return_type.hpp"
#include "../by_perfect.hpp"


namespace pstade { namespace egg {


#define id BOOST_PP_IDENTITY


#define entries \
    (20,( \
        (id(<<),  shift_left,    boost::lambda::bitwise_action<boost::lambda::leftshift_action>), \
        (id(>>),  shift_right,   boost::lambda::bitwise_action<boost::lambda::rightshift_action>), \
        (id(*),   multiplies,    boost::lambda::arithmetic_action<boost::lambda::multiply_action>), \
        (id(/),   divides,       boost::lambda::arithmetic_action<boost::lambda::divide_action>), \
        (id(%),   modulus,       boost::lambda::arithmetic_action<boost::lambda::remainder_action>), \
        (id(+),   plus,          boost::lambda::arithmetic_action<boost::lambda::plus_action>), \
        (id(-),   minus,         boost::lambda::arithmetic_action<boost::lambda::minus_action>), \
        (id(<),   less,          boost::lambda::relational_action<boost::lambda::less_action>), \
        (id(>),   greater,       boost::lambda::relational_action<boost::lambda::greater_action>), \
        (id(<=),  less_equal,    boost::lambda::relational_action<boost::lambda::lessorequal_action>), \
        (id(>=),  greater_equal, boost::lambda::relational_action<boost::lambda::greaterorequal_action>), \
        (id(==),  equal_to,      boost::lambda::relational_action<boost::lambda::equal_action>), \
        (id(!=),  not_equal_to,  boost::lambda::relational_action<boost::lambda::notequal_action>), \
        (id(||),  logical_or,    boost::lambda::logical_action<boost::lambda::or_action>), \
        (id(&&),  logical_and,   boost::lambda::logical_action<boost::lambda::and_action>), \
        (id(&),   bitwise_and,   boost::lambda::bitwise_action<boost::lambda::and_action>), \
        (id(|),   bitwise_or,    boost::lambda::bitwise_action<boost::lambda::or_action>), \
        (id(^),   bitwise_xor,   boost::lambda::bitwise_action<boost::lambda::xor_action>), \
        (BOOST_PP_COMMA, comma,  boost::lambda::other_action<boost::lambda::comma_action>), \
        (id(->*), mem_ptr,       boost::lambda::other_action<boost::lambda::member_pointer_action>) \
    ) ) \
/**/
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC(BOOST_PP_ARRAY_SIZE(entries)), <pstade/egg/detail/functional2.hpp>))
    #include BOOST_PP_ITERATE()
#undef  entries


#define entries \
    (10,( \
        (id(<<=), shift_left_assign,   boost::lambda::bitwise_assignment_action<boost::lambda::leftshift_action>), \
        (id(>>=), shift_right_assign,  boost::lambda::bitwise_assignment_action<boost::lambda::rightshift_action>), \
        (id(*=),  multiplies_assign,   boost::lambda::arithmetic_assignment_action<boost::lambda::multiply_action>), \
        (id(/=),  divides_assign,      boost::lambda::arithmetic_assignment_action<boost::lambda::divide_action>), \
        (id(%=),  modulus_assign,      boost::lambda::arithmetic_assignment_action<boost::lambda::remainder_action>), \
        (id(+=),  plus_assign,         boost::lambda::arithmetic_assignment_action<boost::lambda::plus_action>), \
        (id(-=),  minus_assign,        boost::lambda::arithmetic_assignment_action<boost::lambda::minus_action>), \
        (id(&=),  bitwise_and_assign,  boost::lambda::bitwise_assignment_action<boost::lambda::and_action>), \
        (id(|=),  bitwise_or_assign,   boost::lambda::bitwise_assignment_action<boost::lambda::or_action>), \
        (id(^=),  bitwise_xor_assign,  boost::lambda::bitwise_assignment_action<boost::lambda::xor_action>) \
    ) ) \
/**/
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC(BOOST_PP_ARRAY_SIZE(entries)), <pstade/egg/detail/functional2.hpp>))
    #include BOOST_PP_ITERATE()
#undef  entries


#undef  id


} } // namespace pstade::egg


#endif
#else
#define entry BOOST_PP_ARRAY_ELEM(BOOST_PP_ITERATION(), entries)
#define op   BOOST_PP_TUPLE_ELEM(3, 0, entry)
#define name BOOST_PP_TUPLE_ELEM(3, 1, entry)
#define act  BOOST_PP_TUPLE_ELEM(3, 2, entry)


    namespace BOOST_PP_CAT(name, _detail) {


        template<class Return>
        struct little
        {
            template<class Me, class A1, class A2>
            struct apply :
                eval_if_use_default< Return,
                    boost::lambda::return_type_2<act, A1, A2>
                >
            { };

            template<class Re, class A1, class A2>
            Re call(A1& a1, A2& a2) const
            {
                return a1 op() a2;
            }
        };


    } // namespace BOOST_PP_CAT(name, _detail)


    template<class Return = boost::use_default, class Strategy = by_perfect>
    struct BOOST_PP_CAT(X_, name) :
        function<BOOST_PP_CAT(name, _detail)::little<Return>, Strategy>
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
