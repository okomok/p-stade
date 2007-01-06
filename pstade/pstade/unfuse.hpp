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
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/pack.hpp>
#include <pstade/preprocessor.hpp>


namespace pstade {


    namespace unfuse_detail {


        template<class Function, class Pack = op_pack>
        struct op_result :
            callable<
                op_result<Function, Pack>,
                typename boost::result_of<Function(
                    typename boost::result_of<Pack()>::type
                )>::type
            >
        {
            template<class Myself, PSTADE_CALLABLE_APPLY_PARAMS(A)>
            struct apply
            { }; // complete for SFINAE.

            // 0ary
            template< class Result >
            Result call() const
            {
                return m_fun(
                    m_pack()
                );
            }

            // 1ary-
            #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_CALLABLE_MAX_ARITY, <pstade/unfuse.hpp>))
            #include BOOST_PP_ITERATE()

            explicit op_result() // for ForwardIterator
            { }

            explicit op_result(Function const& f, Pack const& p = pack) :
                m_fun(f), m_pack(p)
            { }

            typedef Function base_type;

            Function const& base() const
            {
                return m_fun;
            }

        private:
            Function m_fun;
            Pack m_pack;
        };


    } // namespace unfuse_detail


    PSTADE_OBJECT_GENERATOR(unfuse,
        (unfuse_detail::op_result< deduce<_1, to_value>, deduce<_2, to_value, op_pack> >))


} // namespace pstade


PSTADE_CALLABLE_NULLARY_RESULT_OF_TEMPLATE((pstade)(unfuse_detail)(op_result), 2)


#endif
#else
#define n BOOST_PP_ITERATION()


template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)> :
    boost::result_of<Function(
        typename boost::result_of<Pack(PSTADE_PP_ENUM_REFS(n, A))>::type
    )>
{ };

template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
Result call(PSTADE_PP_ENUM_REF_PARAMS(n, A, a)) const
{
    return m_fun(
        m_pack(BOOST_PP_ENUM_PARAMS(n, a))
    );
}


#undef n
#endif
