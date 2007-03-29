#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_PERFECT_HPP
#define PSTADE_PERFECT_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Works around the forwarding problem.
// You can choose:
//     perfect(lambda::_1)(1); or
//     lambda::_1(1|as_ref);
//
// Also, this can add 'boost::result_of/lambda::sig' support
// by passing the extra argument, as 'lambda::ret' does.
// Thus, you can change the result type of the function.


// Note:
//
// This class cannot be implemented by using 'fuse' and 'unfuse',
// for they need a function supporting 'result_of', which this class will make!


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/const_function.hpp>
#include <pstade/constant.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/use_default.hpp>


namespace pstade {


    namespace perfect_detail {


        template<class ResultType, class Signature>
        struct result_of_aux :
            use_default_eval_to< ResultType, boost::result_of<Signature> >
        { };


        template<class Function, class ResultType = boost::use_default>
        struct return_op :
            callable<
                return_op<Function, ResultType>,
                typename result_of_aux<ResultType, PSTADE_CONST_FUNCTION(Function)()>::type
            >
        {
            template<class Myself, PSTADE_CALLABLE_APPLY_PARAMS(A)>
            struct apply
            { }; // complete for SFINAE.

            // 0ary
            template<class Result>
            Result call() const
            {
                return m_fun();
            }

            // 1ary-
            #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_CALLABLE_MAX_ARITY, <pstade/perfect.hpp>))
            #include BOOST_PP_ITERATE()

            explicit return_op()
            { }

            explicit return_op(Function const& fun) :
                m_fun(fun)
            { }

            Function const& base() const
            {
                return m_fun;
            }

        private:
            Function m_fun;
        };


    } // namespace perfect_detail


    template<class ResultType = boost::use_default>
    struct op_perfect :
        callable< op_perfect<ResultType> >
    {
        template<class Myself, class Function>
        struct apply
        {
            typedef
                perfect_detail::return_op<
                    typename pass_by_value<Function>::type,
                    ResultType
                >
            type;
        };
   
        template<class Result, class Function>
        Result call(Function& fun) const
        {
            return Result(fun);
        }
    };


    template<class Function> inline
    typename boost::result_of<op_perfect<>(Function&)>::type
    perfect(Function fun)
    {
        return op_perfect<>()(fun);
    }

    template<class ResultType, class Function> inline
    typename boost::result_of<op_perfect<ResultType>(Function&)>::type
    perfect(Function fun)
    {
        return op_perfect<ResultType>()(fun);
    }


} // namespace pstade


PSTADE_CALLABLE_NULLARY_RESULT_OF_TEMPLATE(pstade::perfect_detail::return_op, 2)


#endif
#else
#define n BOOST_PP_ITERATION()


template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)> :
    result_of_aux<ResultType, PSTADE_CONST_FUNCTION(Function)(PSTADE_PP_ENUM_PARAMS_WITH(n, A, &))>
{ };

template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
{
    return m_fun(BOOST_PP_ENUM_PARAMS(n, a));
}


#undef n
#endif
