#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_UNTUPLED_HPP
#define PSTADE_UNTUPLED_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This could be implementedy by 'compose' and 'tie',
// but this is the basis together with 'tupled'.


#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/tie.hpp>


namespace pstade {


    namespace untupled_detail {


        template< class Function >
        struct baby_fun
        {

            // PSTADE_EGG_MAX_ARITY (primary)
            template< class Myself, BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(PSTADE_EGG_MAX_ARITY, class A, void) >
            struct apply :
                boost::result_of<
                    Function(
                        // no 'const&', cuz this tuple is rvalue (20.5.4/1).
                        boost::tuples::tuple< PSTADE_PP_ENUM_REF_PARAMS(PSTADE_EGG_MAX_ARITY, A) >
                    )
                >
            { };

            template< class Result, BOOST_PP_ENUM_PARAMS(PSTADE_EGG_MAX_ARITY, class A) >
            Result call( PSTADE_PP_ENUM_REF_PARAMS_WITH_OBJECTS(PSTADE_EGG_MAX_ARITY, A, a) ) const
            {
                return
                    m_fun(
                       pstade::tie( BOOST_PP_ENUM_PARAMS(PSTADE_EGG_MAX_ARITY, a) )
                    );
            }

            // 0ary
            typedef typename
                boost::result_of<
                    Function(
                        boost::tuples::tuple<>
                    )
                >::type
            nullary_result_type;

            template< class Result >
            Result call() const
            {
                return
                    m_fun(
                        pstade::tie()
                    );
            }

            // 1ary
            template< class Myself, class A0 >
            struct apply< Myself, A0 > :
                boost::result_of<
                    Function(
                        boost::tuples::tuple< A0& >
                    )
                >
            { };

            template< class Result, class A0 >
            Result call( A0& a0 ) const
            {
                return
                    m_fun(
                        pstade::tie( a0 )
                    );
            }

            // 2ary-
        #define PSTADE_max_arity BOOST_PP_DEC(PSTADE_EGG_MAX_ARITY)
            #define  BOOST_PP_ITERATION_PARAMS_1 (3, (2, PSTADE_max_arity, <pstade/untupled.hpp>))
            #include BOOST_PP_ITERATE()
        #undef  PSTADE_max_arity


            explicit baby_fun() // DefaultConstructible iff 'Function' is.
            { }

            explicit baby_fun(Function const& fun) :
                m_fun(fun)
            { }

            typedef Function base_type;

            Function const& base() const
            {
                return m_fun;
            }

        private:
            mutable Function m_fun;

        }; // struct baby_fun


        struct baby
        {
            template< class Myself, class Function >
            struct apply
            {
                typedef typename pass_by_value<Function>::type fun_t;
                typedef egg::function< baby_fun<fun_t> > type;
            };

            template< class Result, class Function >
            Result call(Function& fun) const
            {
                return Result(fun);
            }
        };


    } // namespace untupled_detail


    PSTADE_EGG_FUNCTION(untupled, untupled_detail::baby)


} // namespace pstade


#endif
#else
#define n BOOST_PP_ITERATION()


template< class Myself, BOOST_PP_ENUM_PARAMS(n, class A) >
struct apply< Myself, BOOST_PP_ENUM_PARAMS(n, A) > :
    boost::result_of<
        Function(
            boost::tuples::tuple< PSTADE_PP_ENUM_REF_PARAMS(n, A) >
        )
    >
{ };

template< class Result, BOOST_PP_ENUM_PARAMS(n, class A) >
Result call( PSTADE_PP_ENUM_REF_PARAMS_WITH_OBJECTS(n, A, a) ) const
{
    return
        m_fun(
            pstade::tie( BOOST_PP_ENUM_PARAMS(n, a) )
        );
}


#undef n
#endif
