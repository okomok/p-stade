#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_DETAIL_LITTLE_RETURN_RESULT_HPP
#define BOOST_EGG_DETAIL_LITTLE_RETURN_RESULT_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This can't be implemented by fusing;
// fuse/unfuse requires a functor to support result_of.


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/egg/apply_decl.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_MAX_LINEAR_ARITY
#include <boost/egg/forward.hpp>
#include <boost/egg/result_of.hpp>
#include <boost/egg/detail/if_use_default.hpp>


namespace boost { namespace egg { namespace details {


    template<class Base, class Return, class Strategy, class Tag>
    struct little_return_result
    {
        typedef Tag tag_type;

        Base m_base;

        Base const &base() const
        {
            return m_base;
        }

    // 0ary
        typedef typename
            eval_if_use_default< Return, result_of_<Base const()> >::type
        nullary_result_type;

        template<class Re>
        Re call() const
        {
            return m_base();
        }

    // 1ary-
        template<class Me, BOOST_EGG_APPLY_DECL_PARAMS(BOOST_EGG_MAX_LINEAR_ARITY, A)>
        struct BOOST_EGG_APPLY_DECL;

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_EGG_MAX_LINEAR_ARITY, <boost/egg/detail/little_return_result.hpp>))
        #include BOOST_PP_ITERATE()
    };


} } } // namespace boost::egg::details


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Me, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Me, BOOST_PP_ENUM_PARAMS(n, A)> :
        eval_if_use_default< Return,
            result_of_<Base const(BOOST_EGG_FORWARDING_META_ARGS(n, A, Strategy const))>
        >
    { };

    template<class Re, BOOST_PP_ENUM_PARAMS(n, class A)>
    Re call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, &a)) const
    {
        return m_base(BOOST_EGG_FORWARDING_ARGS(n, a, Strategy const));
    }


#undef  n
#endif
