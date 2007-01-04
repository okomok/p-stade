#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_NEW_DELETE_HPP
#define PSTADE_NEW_DELETE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // size_t
#include <memory> // auto_ptr
#include <boost/checked_delete.hpp>
#include <boost/pointee.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/automatic.hpp>
#include <pstade/callable.hpp>
#include <pstade/compose.hpp>
#include <pstade/constant.hpp>
#include <pstade/construct.hpp>
#include <pstade/preprocessor.hpp>


namespace pstade {


    // new
    //

    template<class X>
    struct op_new :
        callable<op_new<X>, X *>
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
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_CALLABLE_MAX_ARITY, <pstade/new_delete.hpp>))
        #include BOOST_PP_ITERATE()
    };


    template<class X>
    struct op_new<X[]>
    {
        typedef X *result_type;

        X *operator()(std::size_t n) const
        {
            return new X[n];
        }
    };


    // There is no 'new_' yet.
    // Yet another 63 functions seems bad?


    // delete
    //

    struct op_delete
    {
        typedef void result_type;

        template<class X>
        void operator()(X *p) const
        {
            boost::checked_delete(p);
        }
    };

    PSTADE_CONSTANT(delete_, (op_delete))


    struct op_delete_array
    {
        typedef void result_type;

        template<class X>
        void operator()(X *p) const
        {
            boost::checked_array_delete(p);
        }
    };

    PSTADE_CONSTANT(delete_array, (op_delete_array))


    // smart pointers
    //

    template<class P>
    struct op_new_ptr :
        boost::result_of<op_compose(
            op_construct<P>,
            op_new<typename boost::pointee<P>::type>
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

    PSTADE_AUTOMATIC(shared_object, (op_new_shared< boost::pointee<_1> >))


    template<class X>
    struct op_new_shared<X[]>
    {
        typedef boost::shared_array<X> result_type;

        result_type operator()(std::size_t n) const
        {
            return result_type(new X[n]);
        }
    };


} // namespace pstade


// nullary results
//

PSTADE_CALLABLE_NULLARY_RESULT_OF_TEMPLATE((pstade)(op_new), 1)

// These macros work; 'op_compose' returns a type derived from 'callable'.
PSTADE_CALLABLE_NULLARY_RESULT_OF_TEMPLATE((pstade)(op_new_ptr), 1)
PSTADE_CALLABLE_NULLARY_RESULT_OF_TEMPLATE((pstade)(op_new_auto), 1)
PSTADE_CALLABLE_NULLARY_RESULT_OF_TEMPLATE((pstade)(op_new_shared), 1)


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
