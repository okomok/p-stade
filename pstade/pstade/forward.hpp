#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_FORWARD_HPP
#define PSTADE_FORWARD_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Works around the forwarding problem.
// You can choose:
//     pstade::forward(lambda::_1)(1); or
//     lambda::_1(1|to_reference);
//
// Also, this can add 'boost::result_of/lambda::sig' support
// by passing the extra argument, as 'lambda::ret' does.


#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/to_type.hpp>


namespace pstade {


    namespace forward_detail {

        
        struct use_default;


        template< class Result_, class Signature >
        struct result_of_aux :
            boost::mpl::eval_if< boost::is_same<Result_, use_default>,
                boost::result_of<Signature>,
                boost::mpl::identity<Result_>
            >
        { };


        template< class Result_, class Function >
        struct baby_fun
        {

            // PSTADE_EGG_MAX_ARITY (primary)
            template< class Myself, BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(PSTADE_EGG_MAX_ARITY, class A, void) >
            struct apply :
                result_of_aux< Result_,
                    Function( PSTADE_PP_ENUM_REF_PARAMS(PSTADE_EGG_MAX_ARITY, A) )
                >
            { };

            template< class Result, BOOST_PP_ENUM_PARAMS(PSTADE_EGG_MAX_ARITY, class A) >
            Result call( PSTADE_PP_ENUM_REF_PARAMS_WITH_OBJECTS(PSTADE_EGG_MAX_ARITY, A, a) )
            {
                return
                    m_fun(
                       BOOST_PP_ENUM_PARAMS(PSTADE_EGG_MAX_ARITY, a)
                    );
            }

            // 0ary
            typedef typename
                result_of_aux< Result_,
                    Function(
                    )
                >::type
            nullary_result_type;

            template< class Result >
            Result call( ) const
            {
                return
                    m_fun(
                    );
            }

            // 1ary
            template< class Myself, class A0 >
            struct apply< Myself, A0 > :
                result_of_aux< Result_,
                    Function(
                        A0&
                    )
                >
            { };

            template< class Result, class A0 >
            Result call( A0& a0 ) const
            {
                return
                    m_fun(
                        a0
                    );
            }

            // 2ary-
        #define PSTADE_max_arity BOOST_PP_DEC(PSTADE_EGG_MAX_ARITY)
            #define  BOOST_PP_ITERATION_PARAMS_1 (3, (2, PSTADE_max_arity, <pstade/forward.hpp>))
            #include BOOST_PP_ITERATE()
        #undef  PSTADE_max_arity

            explicit baby_fun() // DefaultConstructible iff 'Function' is.
            { }

            explicit baby_fun(Function const& fun) :
                m_fun(fun)
            { }

            Function const& base() const
            {
                return m_fun;
            }

        private:
            mutable Function m_fun;

        }; // struct baby_fun


        struct baby
        {
            template< class Myself, class Function, class TypeResult = void >
            struct apply
            {
                typedef typename pass_by_value<Function>::type fun_t;
                typedef typename to_type<TypeResult>::type result_t;
                typedef egg::function< baby_fun<result_t, fun_t> > type;
            };
       
            template< class Result, class Function, class TypeResult >
            Result call(Function& fun, TypeResult) const
            {
                return Result(fun);
            }

            template< class Myself, class Function >
            struct apply<Myself, Function>
            {
                typedef typename pass_by_value<Function>::type fun_t;
                typedef egg::function< baby_fun<use_default, fun_t> > type;
            };

            template< class Result, class Function >
            Result call(Function& fun) const
            {
                return Result(fun);
            } 
        };

            
    } // namespace forward_detail


    PSTADE_EGG_FUNCTION(forward, forward_detail::baby)
    PSTADE_PIPABLE(forwarded, forward_fun)


} // namespace pstade


#endif
#else
#define n BOOST_PP_ITERATION()


template< class Myself, BOOST_PP_ENUM_PARAMS(n, class A) >
struct apply< Myself, BOOST_PP_ENUM_PARAMS(n, A) > :
    result_of_aux< Result_,
        Function(
            PSTADE_PP_ENUM_REF_PARAMS(n, A)
        )
    >
{ };

template< class Result, BOOST_PP_ENUM_PARAMS(n, class A) >
Result call( PSTADE_PP_ENUM_REF_PARAMS_WITH_OBJECTS(n, A, a) ) const
{
    return
        m_fun(
            BOOST_PP_ENUM_PARAMS(n, a)
        );
}


#undef n
#endif
