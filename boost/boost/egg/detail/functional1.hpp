#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_DETAIL_FUNCTIONAL1_HPP
#define BOOST_EGG_DETAIL_FUNCTIONAL1_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/egg/bll/return_type.hpp>
#include <boost/egg/by_perfect.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/detail/adl_barrier.hpp>
#include <boost/egg/detail/derived_from.hpp>
#include <boost/egg/detail/if_use_default.hpp>
#include <boost/egg/detail/bll_contentsof_hack.hpp>
#include <boost/egg/detail/pp_array_iterate.hpp>


namespace boost { namespace egg {


#define entries \
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
    #define  BOOST_EGG_PP_ARRAY_ITERATION_PARAMS (entries, <boost/egg/detail/functional1.hpp>)
    #include BOOST_EGG_PP_ARRAY_ITERATE()
#undef  entries


} } // namespace boost::egg


#endif
#else
#define entry BOOST_EGG_PP_ARRAY_ITERATION()
#define op   BOOST_PP_TUPLE_ELEM(4, 0, entry)
#define name BOOST_PP_TUPLE_ELEM(4, 1, entry)
#define post BOOST_PP_TUPLE_ELEM(4, 2, entry)
#define act  BOOST_PP_TUPLE_ELEM(4, 3, entry)


    namespace BOOST_PP_CAT(name, _detail) {


        template<class Return>
        struct little
        {
            template<class Me, class A1>
            struct apply :
                details::eval_if_use_default< Return,
                    boost::lambda::return_type_1<act, A1>
                >
            { };

            template<class Re, class A1>
            Re call(A1 &a1) const
            {
                // I have a feeling that egg::forwarding shouldn't be called,
                // because Boost.Lambda doesn't care rvalue.
    #if post == 1
                return a1 op;
    #else
                return op a1;
    #endif
            }
        };


    } // namespace BOOST_PP_CAT(name, _detail)


    template<class Return = use_default, class Strategy = by_perfect>
    struct BOOST_PP_CAT(X_, name) : details::derived_from<
        function<BOOST_PP_CAT(name, _detail)::little<Return>, Strategy> >
    { };

BOOST_EGG_ADL_BARRIER(functional1) {
    typedef BOOST_PP_CAT(X_, name)<>::base_class BOOST_PP_CAT(T_, name);
    BOOST_EGG_CONST((BOOST_PP_CAT(T_, name)), name) = {{}};
}


#undef  act
#undef  post
#undef  name
#undef  op
#undef  entry
#endif
