#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_UNFUSE_HPP
#define PSTADE_UNFUSE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This could be implementedy by 'compose' with 'pack',
// but this is the basis together with 'fuse'.


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/pack.hpp>
#include <pstade/preprocessor.hpp>


namespace pstade {


    namespace unfuse_detail {


        template< class Function >
        struct op_result :
            callable<
                op_result<Function>,
                typename boost::result_of<Function(boost::tuples::tuple<>)>::type
            >
        {

            template< class Myself, PSTADE_CALLABLE_APPLY_PARAMS(A) >
            struct apply
            { };


            // 0ary

            template< class Result >
            Result call() const
            {
                return m_fun(
                    pstade::pack(
                    )
                );
            }


            // 1ary

            template< class Myself, class A0 >
            struct apply< Myself, A0 > :
                boost::result_of< Function(
                    boost::tuples::tuple<
                        A0&
                    >
                ) >
            { };

            template< class Result, class A0 >
            Result call( A0& a0 ) const
            {
                return m_fun(
                    pstade::pack(
                        a0
                    )
                );
            }


            // 2ary-

            #define  BOOST_PP_ITERATION_PARAMS_1 (3, (2, PSTADE_CALLABLE_MAX_ARITY, <pstade/unfuse.hpp>))
            #include BOOST_PP_ITERATE()


            explicit op_result() // for ForwardIterator
            { }

            explicit op_result(Function const& fun) :
                m_fun(fun)
            { }

            typedef Function base_type;

            Function const& base() const
            {
                return m_fun;
            }

        private:
            Function m_fun;

        }; // struct op_result


    } // namespace unfuse_detail


    PSTADE_OBJECT_GENERATOR(unfuse, (unfuse_detail::op_result< deduce<_1, to_value> >))


} // namespace pstade


PSTADE_CALLABLE_NULLARY_RESULT_OF_TEMPLATE((pstade)(unfuse_detail)(op_result), 1)


#endif
#else
#define n BOOST_PP_ITERATION()


template< class Myself, BOOST_PP_ENUM_PARAMS(n, class A) >
struct apply< Myself, BOOST_PP_ENUM_PARAMS(n, A) > :
    boost::result_of< Function(
        boost::tuples::tuple<
            PSTADE_PP_ENUM_REFS(n, A)
        >
    ) >
{ };

template< class Result, BOOST_PP_ENUM_PARAMS(n, class A) >
Result call( PSTADE_PP_ENUM_REF_PARAMS(n, A, a) ) const
{
    return m_fun(
        pstade::pack(
            BOOST_PP_ENUM_PARAMS(n, a)
        )
    );
}


#undef n
#endif
