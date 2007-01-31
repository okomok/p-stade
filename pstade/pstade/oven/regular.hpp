#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_OVEN_REGULAR_HPP
#define PSTADE_OVEN_REGULAR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Neither 'is_assignable' nor 'is_default_constructible'
// seems impossible to implement.
// Notice that 'is_lambda_functor' can't be the detection;
// e.g. 'forward(lambda::_1)', which is neither assignable
// nor a lambda functor.


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/lambda_result_of.hpp> // inclusion guaranteed
#include <pstade/object_generator.hpp>
#include <pstade/to_shared_ptr.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/preprocessor.hpp>


namespace pstade { namespace oven {


namespace regular_detail {


    template< class Function >
    struct op_result :
        callable<
            op_result<Function>,
            typename boost::result_of<Function()>::type
        >
    {
        template< class Myself, PSTADE_CALLABLE_APPLY_PARAMS(A) >
        struct apply
        { }; // complete for SFINAE.

        // 0ary
        template< class Result >
        Result call() const
        {
            return (*m_pfun)();
        }

        // 1ary-
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_CALLABLE_MAX_ARITY, <pstade/oven/regular.hpp>))
        #include BOOST_PP_ITERATE()

        explicit op_result()
        { }

        template< class Pointer >
        explicit op_result(Pointer p,
            typename enable_if< is_shared_ptr_constructible<Function, Pointer> >::type = 0
        ) :
            m_pfun(to_shared_ptr(p))
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


} // namespace regular_detail


PSTADE_OBJECT_GENERATOR(regular, (regular_detail::op_result< deduce<_1, to_value> >))


// This must be made from scrach; see "./shared.hpp"

struct op_shared_regular
{
    template< class FunCall >
    struct result;

    template< class Fun, class Pointer >
    struct result<Fun(Pointer)>
    {
        typedef
            regular_detail::op_result<
                typename shared_pointee<Pointer>::type
            >
        type;
    };

    template< class Pointer >
    typename result<void(Pointer)>::type
    operator()(Pointer p) const
    {
        return typename result<void(Pointer)>::type(p);
    }
};

PSTADE_CONSTANT(shared_regular, (op_shared_regular))


} } // namespace pstade::oven


PSTADE_CALLABLE_NULLARY_RESULT_OF_TEMPLATE((pstade)(oven)(regular_detail)(op_result), 1)


#endif
#else
#define n BOOST_PP_ITERATION()


template< class Myself, BOOST_PP_ENUM_PARAMS(n, class A) >
struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)> :
    boost::result_of<Function(PSTADE_PP_ENUM_PARAMS_WITH(n, A, &))>
{ };

template< class Result, BOOST_PP_ENUM_PARAMS(n, class A) >
Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
{
    return (*m_pfun)(BOOST_PP_ENUM_PARAMS(n, a));
}


#undef n
#endif
