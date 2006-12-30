#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_NEW_AUTO_HPP
#define PSTADE_NEW_AUTO_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <memory> // auto_ptr
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/to_type.hpp>


namespace pstade {


#define PSTADE_ctor_max_arity \
    BOOST_PP_DEC(PSTADE_CALLABLE_MAX_ARITY) \
/**/


    struct op_new_ :
        callable<op_new_>
    {
        // PSTADE_ctor_max_arity (primary)
        template<class Myself, class Type_X, BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(PSTADE_ctor_max_arity, class A, void)>
        struct apply
        {
            typedef typename to_type<Type_X>::type x_t;
            typedef std::auto_ptr<x_t> type;
        };

        // 0ary
        template<class Result, class Type_X>
        Result call(Type_X) const
        {
            typedef typename to_type<Type_X>::type x_t;
            return Result(new x_t());
        }

        // 1ary-
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_ctor_max_arity, <pstade/new.hpp>))
        #include BOOST_PP_ITERATE()
 
    }; // struct op_new_


    PSTADE_CONSTANT(new_, (op_new_))


#undef  PSTADE_ctor_max_arity


} // namespace pstade


#endif
#else
#define n BOOST_PP_ITERATION()


template<class Result, class Type_X, BOOST_PP_ENUM_PARAMS(n, class A)>
Result call(Type_X, PSTADE_PP_ENUM_REF_PARAMS(n, A, a)) const
{
    typedef typename to_type<Type_X>::type x_t;
    return Result(new x_t(BOOST_PP_ENUM_PARAMS(n, a)));
}


#undef n
#endif
