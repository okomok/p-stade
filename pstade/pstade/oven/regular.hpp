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
// We can't determine whether or not a lambda functor is
// sharable or not. ('boost::is_stateless' is too strict.)
// So, it is cloned by default. If you know it's stateless
// and want to optimize copying, use 'regular_c'.
//
// Neither 'is_assignable' nor 'is_default_constructible'
// seems impossible to implement.
// Notice that 'is_lambda_functor' can't be the detection;
// e.g. 'perfect(lambda::_1)', which is neither assignable
// nor a lambda functor.


#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/function.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/result_of_lambda.hpp> // inclusion guaranteed
#include "./detail/regularized.hpp"


namespace pstade { namespace oven {


namespace regular_detail {


    struct regularized_tag;
    struct shared_ptr_tag;
    struct raw_ptr_tag;


    template< class Function, class PimplTag >
    struct pimpl_of :
        boost::mpl::eval_if< boost::is_same<PimplTag, raw_ptr_tag>,
            boost::mpl::identity<Function *>,
            boost::mpl::eval_if< boost::is_same<PimplTag, shared_ptr_tag>,
                boost::mpl::identity< boost::shared_ptr<Function> >,
                boost::mpl::identity< detail::regularized<Function> >
            >
        >
    { };


    template< class Function, class PimplTag >
    struct return_op :
        callable<
            return_op<Function, PimplTag>,
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
            return (*m_pimpl)();
        }

        // 1ary-
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_CALLABLE_MAX_ARITY, <pstade/oven/regular.hpp>))
        #include BOOST_PP_ITERATE()

        explicit return_op()
        { }

        explicit return_op(Function *pfun) :
            m_pimpl(pfun)
        { }

        explicit return_op(Function fun) :
            m_pimpl(fun)
        { }

        typedef Function base_type;

        Function& base()
        {
            return *m_pimpl;
        }

        Function const& base() const
        {
            return *m_pimpl;
        }

    private:
        typename pimpl_of<Function, PimplTag>::type m_pimpl;
    };


    template< class Function >
    struct baby
    {
        typedef
            return_op<typename pass_by_value<Function>::type, regularized_tag>
        result_type;

        result_type operator()(Function& fun) const
        {
            return result_type(fun);
        }
    };


    template< class Function >
    struct baby_c
    {
        typedef
            return_op<typename pass_by_value<Function>::type, shared_ptr_tag>
        result_type;

        result_type operator()(Function& fun) const
        {
            typedef typename result_type::base_type fun_t;
            return result_type(new fun_t(fun));
        }
    };


    template< class Function >
    struct baby_ref
    {
        typedef
            return_op<Function, raw_ptr_tag>
        result_type;

        result_type operator()(Function& fun) const
        {
            return result_type(&fun);
        }
    };


} // namespace regular_detail


PSTADE_FUNCTION(regular, (regular_detail::baby<_>))
PSTADE_FUNCTION(regular_c, (regular_detail::baby_c<_>))
PSTADE_FUNCTION(regular_ref, (regular_detail::baby_ref<_>))


} } // namespace pstade::oven


PSTADE_CALLABLE_NULLARY_RESULT_OF_TEMPLATE(pstade::oven::regular_detail::return_op, 2)


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
    return (*m_pimpl)(BOOST_PP_ENUM_PARAMS(n, a));
}


#undef n
#endif
