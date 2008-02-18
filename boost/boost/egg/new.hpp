#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_NEW_HPP
#define BOOST_EGG_NEW_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/egg/apply_decl.hpp>
#include <boost/egg/by_perfect.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_MAX_LINEAR_ARITY
#include <boost/egg/forward.hpp>
#include <boost/egg/register_nullary_result.hpp>


namespace boost { namespace egg {


    namespace new_detail {


        template<class T, class Strategy>
        struct little
        {
        // 0ary
            typedef T *nullary_result_type;

            template<class Re>
            Re call() const
            {
                return new T();
            }

        // 1ary-
            template<class Me, BOOST_EGG_APPLY_DECL_PARAMS(BOOST_EGG_MAX_LINEAR_ARITY, A)>
            struct apply
            {
                typedef T *type;
            };

            #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_EGG_MAX_LINEAR_ARITY, <boost/egg/new.hpp>))
            #include BOOST_PP_ITERATE()
        };


    } // namespace new_detail


    template<class T, class Strategy = by_perfect>
    struct X_new :
        function<new_detail::little<T, Strategy>, Strategy>
    { };


} } // namespace boost::egg


BOOST_EGG_REGISTER_NULLARY_RESULT_OF_TEMPLATE(boost::egg::X_new, (class)(class))


#include <boost/egg/detail/suffix.hpp>
#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Re, BOOST_PP_ENUM_PARAMS(n, class A)>
    Re call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, &a)) const
    {
        return new T(BOOST_EGG_FORWARDING_ARGS(n, a, Strategy const));
    }


#undef  n
#endif
