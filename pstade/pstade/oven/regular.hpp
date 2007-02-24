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
// This is essentially same as what Boost.Function does.
//
// Neither 'is_assignable' nor 'is_default_constructible'
// seems impossible to implement.
// Notice that 'is_lambda_functor' can't be the detection;
// e.g. 'forward(lambda::_1)', which is neither assignable
// nor a lambda functor.
//
// You can't determine whether or not a lambda functor is
// sharable or not. ('boost::is_stateless' is too strict.)
// So, it is cloned by default. If you know it's stateless
// and want to optimize copying, use 'regular_stateless'.


#include <boost/mpl/if.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/clone_ptr.hpp>
#include <pstade/function.hpp>
#include <pstade/lambda_result_of.hpp> // inclusion guaranteed
#include <pstade/pass_by.hpp>
#include <pstade/preprocessor.hpp>


namespace pstade { namespace oven {


namespace regular_detail {


    struct raw_ptr_tag { };
    struct shared_ptr_tag { };
    struct clone_ptr_tag { };


    template< class Function, class PtrTag >
    struct ptr_of :
        boost::mpl::if_< boost::is_same<PtrTag, raw_ptr_tag>,
            Function *,
            typename boost::mpl::if_< boost::is_same<PtrTag, clone_ptr_tag>,
                clone_ptr<Function>,
                boost::shared_ptr<Function>
            >::type
        >
    { };


    template< class Function, class PtrTag >
    struct op_result :
        callable<
            op_result<Function, PtrTag>,
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

        explicit op_result(Function *pfun) :
            m_pfun(pfun)
        { }

        typedef Function base_type;

        Function const& base() const
        {
            return *m_pfun;
        }

    private:
        typename ptr_of<Function, PtrTag>::type m_pfun;
    };


    template< class Function >
    struct baby
    {
        typedef
            op_result<
                typename pass_by_value<Function>::type,
                clone_ptr_tag
            >
        result;

        result call(Function& fun)
        {
            typedef typename result::base_type fun_t;
            return result(new fun_t(fun));
        }
    };


    template< class Function >
    struct baby_stateless
    {
        typedef
            op_result<
                typename pass_by_value<Function>::type,
                shared_ptr_tag
            >
        result;

        result call(Function& fun)
        {
            typedef typename result::base_type fun_t;
            return result(new fun_t(fun));
        }
    };


    template< class Function >
    struct baby_ref
    {
        typedef
            op_result<
                Function,
                raw_ptr_tag
            >
        result;

        result call(Function& fun)
        {
            return result(&fun);
        }
    };


} // namespace regular_detail


PSTADE_FUNCTION(regular, (regular_detail::baby<_>))
PSTADE_FUNCTION(regular_stateless, (regular_detail::baby_stateless<_>))
PSTADE_FUNCTION(regular_ref, (regular_detail::baby_ref<_>))


} } // namespace pstade::oven


PSTADE_CALLABLE_NULLARY_RESULT_OF_TEMPLATE((pstade)(oven)(regular_detail)(op_result), 2)


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
