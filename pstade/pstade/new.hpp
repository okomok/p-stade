#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_NEW_HPP
#define PSTADE_NEW_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <memory> // auto_ptr
#include <boost/pointee.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/compose.hpp>
#include <pstade/construct.hpp>
#include <pstade/preprocessor.hpp>


namespace pstade {


    template<class X>
    struct op_new_ :
        callable<op_new_<X>, X *>
    {
        template<class Myself, PSTADE_CALLABLE_APPLY_PARAMS(A)>
        struct apply
        {
            typedef X *type;
        };

        // 0ary
        template<class Result>
        Result call() const
        {
            return new X();
        }

        // 1ary-
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_CALLABLE_MAX_ARITY, <pstade/new.hpp>))
        #include BOOST_PP_ITERATE()
    };


    // There is no 'new_' yet.
    // Yet another 63 functions seems bad?


    template<class P>
    struct op_new_ptr :
        boost::result_of<op_compose(
            op_construct<P>,
            op_new_<typename boost::pointee<P>::type>
        )>::type
    { };


    template<class X>
    struct op_new_auto :
        op_new_ptr< std::auto_ptr<X> >
    { };


    template<class X>
    struct op_new_shared :
        op_new_ptr< boost::shared_ptr<X> >
    { };


} // namespace pstade


PSTADE_CALLABLE_NULLARY_RESULT_OF_TEMPLATE((pstade)(op_new_), 1)


#endif
#else
#define n BOOST_PP_ITERATION()


template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
Result call(PSTADE_PP_ENUM_REF_PARAMS(n, A, a)) const
{
    return new X(BOOST_PP_ENUM_PARAMS(n, a));
}


#undef n
#endif
