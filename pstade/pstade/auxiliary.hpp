#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_AUXILIARY_HPP
#define PSTADE_AUXILIARY_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2004/n1742.pdf


#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/pipable.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/unparenthesize.hpp>


namespace pstade {


    // 0ary

    namespace auxiliary_detail {

        template<class UnaryFun>
        struct op_result0 :
            callable<op_result0<UnaryFun>, op_result0<UnaryFun> const&>
        {
            // as pipe

            template<class Result>
            Result call() const
            {
                return *this;
            }

            // as function call

            template<class Myself, class A0>
            struct apply :
                boost::result_of<UnaryFun(A0&)>
            { };

            template<class Result, class A0>
            Result call(A0& a0) const
            {
                return m_fun(a0);
            }

            explicit op_result0()
            { }

            explicit op_result0(UnaryFun const& fun) :
                m_fun(fun)
            { }

            typedef UnaryFun base_type;

            UnaryFun const& base() const
            {
                return m_fun;
            }

        private:
            UnaryFun m_fun;
        };

        template<class A0, class UnaryFun> inline
        typename boost::result_of<op_result0<UnaryFun>(A0&)>::type
        operator|(A0& a0, op_result0<UnaryFun> const& op)
        {
            return op(a0);
        }

        template<class A0, class UnaryFun> inline
        typename boost::result_of<op_result0<UnaryFun>(PSTADE_DEDUCED_CONST(A0)&)>::type
        operator|(A0 const& a0, op_result0<UnaryFun> const& op)
        {
            return op(a0);
        }

    } // namespace auxiliary_detail

    PSTADE_OBJECT_GENERATOR(auxiliary0,
        (auxiliary_detail::op_result0< deduce<_1, to_value> >))

    #define PSTADE_AUXILIARY0(Object, UnaryFun) \
        typedef \
            ::boost::result_of< ::pstade::op_auxiliary0(PSTADE_UNPARENTHESIZE(UnaryFun)) >::type \
        BOOST_PP_CAT(op_, Object); \
        \
        PSTADE_CONSTANT(Object, (BOOST_PP_CAT(op_, Object))) \
    /**/


    // 1ary-

#define PSTADE_max_arity BOOST_PP_DEC(PSTADE_CALLABLE_MAX_ARITY)
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_max_arity, <pstade/auxiliary.hpp>))
    #include BOOST_PP_ITERATE()
#undef  PSTADE_max_arity


} // namespace pstade


PSTADE_CALLABLE_NULLARY_RESULT_OF_TEMPLATE((pstade)(auxiliary_detail)(op_result0), 1)


#endif
#else
#define n BOOST_PP_ITERATION()


namespace auxiliary_detail {

    template<class Function>
    struct BOOST_PP_CAT(op_result, n) :
        callable< BOOST_PP_CAT(op_result, n)<Function> >
    {
        template<class Myself, PSTADE_CALLABLE_APPLY_PARAMS(A)>
        struct apply
        { };

        // as pipe

        template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
        struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)> :
            boost::result_of<
                typename boost::result_of<op_pipable(Function const&)>::type(
                    PSTADE_PP_ENUM_PARAMS_WITH(n, A, &)
                )
            >
        { };    

        template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
        Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
        {
            return pipable(m_fun)(
                BOOST_PP_ENUM_PARAMS(n, a)
            );
        }

        // as function call

        template<class Myself, BOOST_PP_ENUM_PARAMS(BOOST_PP_INC(n), class A)>
        struct apply<Myself, BOOST_PP_ENUM_PARAMS(BOOST_PP_INC(n), A)> :
            boost::result_of<
                Function(PSTADE_PP_ENUM_PARAMS_WITH(BOOST_PP_INC(n), A, &))
            >
        { };    

        template<class Result, BOOST_PP_ENUM_PARAMS(BOOST_PP_INC(n), class A)>
        Result call(BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PP_INC(n), A, & a)) const
        {
            return m_fun(BOOST_PP_ENUM_PARAMS(BOOST_PP_INC(n), a));
        }

        explicit BOOST_PP_CAT(op_result, n)()
        { }

        explicit BOOST_PP_CAT(op_result, n)(Function const& fun) :
            m_fun(fun)
        { }

        typedef Function base_type;

        Function const& base() const
        {
            return m_fun;
        }

    private:
        Function m_fun;
    };

} // namespace auxiliary_detail

PSTADE_OBJECT_GENERATOR(BOOST_PP_CAT(auxiliary, n),
    (auxiliary_detail::BOOST_PP_CAT(op_result, n)< deduce<_1, to_value> >))


#undef n
#endif
