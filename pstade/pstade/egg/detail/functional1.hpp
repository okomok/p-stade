#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_FUNCTIONAL1_HPP
#define PSTADE_EGG_DETAIL_FUNCTIONAL1_HPP
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
#include "./bll_contentsof_hack.hpp"


namespace pstade { namespace egg {


#define PSTADE_entries \
    (10,( \
        (+,  posit,       0, boost::lambda::unary_arithmetic_action<boost::lambda::plus_action>), \
        (-,  negate,      0, boost::lambda::unary_arithmetic_action<boost::lambda::minus_action>), \
        (*,  dereference, 0, boost::lambda::other_action<boost::lambda::contentsof_action>), \
        (~,  complement,  0, boost::lambda::unary_arithmetic_action<boost::lambda::minus_action>), \
        (&,  address_of,  0, boost::lambda::other_action<boost::lambda::addressof_action>), \
        (!,  logical_not, 0, boost::lambda::logical_action<boost::lambda::not_action>), \
        (++, pre_inc,     0, boost::lambda::pre_increment_decrement_action<boost::lambda::increment_action>), \
        (--, pre_dec,     0, boost::lambda::pre_increment_decrement_action<boost::lambda::decrement_action>), \
        (++, post_inc,    1, boost::lambda::post_increment_decrement_action<boost::lambda::increment_action>), \
        (--, post_dec,    1, boost::lambda::post_increment_decrement_action<boost::lambda::decrement_action>) \
    ) ) \
/**/
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC(BOOST_PP_ARRAY_SIZE(PSTADE_entries)), <pstade/egg/detail/functional1.hpp>))
    #include BOOST_PP_ITERATE()
#undef  PSTADE_entries


} } // namespace pstade::egg


#endif
#else
#define entry BOOST_PP_ARRAY_ELEM(BOOST_PP_ITERATION(), PSTADE_entries)
#define op   BOOST_PP_TUPLE_ELEM(4, 0, entry)
#define name BOOST_PP_TUPLE_ELEM(4, 1, entry)
#define post BOOST_PP_TUPLE_ELEM(4, 2, entry)
#define act  BOOST_PP_TUPLE_ELEM(4, 3, entry)


    struct BOOST_PP_CAT(little_, name)
    {
        template<class Myself, class A1>
        struct apply :
            boost::lambda::return_type_1<act, A1>
        { };

        template<class Result, class A1>
        Result call(A1& a1) const
        {
#if post == 1
            return a1 op;
#else
            return op a1;
#endif
        }
    };

    template<class Strategy = by_perfect>
    struct BOOST_PP_CAT(X_, name) :
        function<BOOST_PP_CAT(little_, name), Strategy>
    { };

    PSTADE_ADL_BARRIER(functional1) {
        typedef BOOST_PP_CAT(X_, name)<>::function_type BOOST_PP_CAT(T_, name);
        PSTADE_POD_CONSTANT((BOOST_PP_CAT(T_, name)), name) = {{}};
    }


#undef  act
#undef  post
#undef  name
#undef  op
#undef  entry
#endif
