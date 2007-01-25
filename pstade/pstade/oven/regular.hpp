#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_OVEN_REGULAR_HPP
#define PSTADE_OVEN_REGULAR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/function.hpp>
#include <pstade/lambda_result_of.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/preprocessor.hpp>


namespace pstade { namespace oven {


namespace regular_detail {


    template<class Function>
    struct op_result :
        callable<
            op_result<Function>,
            typename boost::result_of<Function()>::type
        >
    {
        template<class Myself, PSTADE_CALLABLE_APPLY_PARAMS(A)>
        struct apply
        { }; // complete for SFINAE.

        // 0ary
        template<class Result>
        Result call() const
        {
            return (*m_pfun)();
        }

        // 1ary-
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_CALLABLE_MAX_ARITY, <pstade/oven/regular.hpp>))
        #include BOOST_PP_ITERATE()

        explicit op_result()
        { }

        explicit op_result(Function const& fun) :
            m_pfun(new Function(fun))
        { }

        typedef Function base_type;

        Function const& base() const
        {
            return *m_pfun;
        }

        operator Function() const
        {
            return base();
        }

    private:
        boost::shared_ptr<Function> m_pfun;
    };


    // If 'is_assignable' etc were possible,
    // we could make a functor be regular automagically.
    // Note 'is_lambda_functor' can't work around;
    // e.g. 'forward(lambda::_1)' is neither assignable
    // nor a lambd functor.


    template<class Function>
    struct baby
    {
        typedef
            op_result<
                typename pass_by_value<Function>::type
            >
        result;

        result call(Function& fun)
        {
            return result(fun);
        }
    };


} // namespace regular_detail


PSTADE_FUNCTION(regular, (regular_detail::baby<boost::mpl::_1>))


} } // namespace pstade::oven


PSTADE_CALLABLE_NULLARY_RESULT_OF_TEMPLATE((pstade)(oven)(regular_detail)(op_result), 1)


#endif
#else
#define n BOOST_PP_ITERATION()


template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)> :
    boost::result_of<Function(PSTADE_PP_ENUM_PARAMS_WITH(n, A, &))>
{ };

template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
{
    return (*m_pfun)(BOOST_PP_ENUM_PARAMS(n, a));
}


#undef n
#endif
