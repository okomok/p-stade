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
#include <pstade/constant.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/use_default.hpp>


namespace pstade {


    namespace forward_detail {


        template<class ResultType, class Signature>
        struct result_of_aux :
            use_default_eval_to< ResultType, boost::result_of<Signature> >
        { };


        template<class Function, class ResultType = boost::use_default>
        struct op_result :
            callable<
                op_result<Function, ResultType>,
                typename result_of_aux<ResultType, Function()>::type
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
            #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_CALLABLE_MAX_ARITY, <pstade/forward.hpp>))
            #include BOOST_PP_ITERATE()

            explicit op_result() // for ForwardIterator
            { }

            explicit op_result(Function const& fun) :
                m_fun(fun)
            { }

            Function const& base() const
            {
                return m_fun;
            }

        private:
            Function m_fun;
        };


    } // namespace forward_detail


    template<class ResultType = boost::use_default>
    struct op_forward :
        callable< op_forward<ResultType> >
    {
        template<class Myself, class Function>
        struct apply
        {
            typedef
                forward_detail::op_result<
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
    typename boost::result_of<op_forward<>(Function&)>::type
    forward(Function fun)
    {
        return op_forward<>()(fun);
    }

    template<class ResultType, class Function> inline
    typename boost::result_of<op_forward<ResultType>(Function&)>::type
    forward(Function fun)
    {
        return op_forward<ResultType>()(fun);
    }


} // namespace pstade


PSTADE_CALLABLE_NULLARY_RESULT_OF_TEMPLATE((pstade)(forward_detail)(op_result), 2)


#endif
#else
#define n BOOST_PP_ITERATION()


template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)> :
    result_of_aux<ResultType, Function(PSTADE_PP_ENUM_PARAMS_WITH(n, A, &))>
{ };

template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
{
    return m_fun(BOOST_PP_ENUM_PARAMS(n, a));
}


#undef n
#endif
