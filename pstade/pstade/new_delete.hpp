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
#include <boost/any.hpp>
#include <boost/checked_delete.hpp>
#include <boost/pointee.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/any_movable.hpp>
#include <pstade/automatic.hpp>
#include <pstade/callable.hpp>
#include <pstade/compose.hpp>
#include <pstade/constant.hpp>
#include <pstade/construct.hpp>
#include <pstade/fuse.hpp>
#include <pstade/nonassignable.hpp>
#include <pstade/preprocessor.hpp> // SEQ_RANGE
#include <pstade/specified.hpp>
#include <pstade/unfuse.hpp>


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

        result_type operator()(std::size_t n) const
        {
            return new X[n];
        }
    };


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
        boost::result_of<
            op_compose(
                op_construct<P>,
                op_new<typename boost::pointee<P>::type>
            )
        >::type
    { };


    template<class X>
    struct op_new_auto :
        op_new_ptr< std::auto_ptr<X> >
    { };

#if defined(PSTADE_NEW_AUTO_FUNCTION) // probably rejected; this would generate 68 functions.
    #define  PSTADE_SPECIFIED_PARAMS \
        (PSTADE_PP_SEQ_RANGE(0, BOOST_PP_INC(PSTADE_CALLABLE_MAX_ARITY)), new_auto, op_new_auto, 1)
    #include PSTADE_SPECIFIED()
#endif


    namespace auto_object_detail {

        // 'PSTADE_AUTOMATIC(auto_object, (op_new_auto< boost::pointee<_> >))'
        // doesn't work -- 'auto_ptr' is not CopyConstructible.
        // 'operator auto_ptr_ref<X>()' can't be of help, because
        // some implementations require "move sequence" to be in the same scope.
        // After all, we need a conversion operator to return lvalue.

        template<class Arguments>
        struct temp :
            private nonassignable
        {
            explicit temp(Arguments const& args) :
                m_args(args)
            { }

            template<class X>
            operator std::auto_ptr<X>& ()
            {
                std::auto_ptr<X> ptr(fuse(op_new<X>())(m_args));
                m_any = ptr;
                return m_any.base< std::auto_ptr<X> >();
            }

        private:
            Arguments m_args;
            any_movable m_any;
        };

        struct base_op :
            callable<base_op>
        {
            template<class Myself, class Arguments>
            struct apply
            {
                typedef temp<Arguments> type;
            };

            template<class Result, class Arguments>
            Result call(Arguments& args) const
            {
                return Result(args); 
            }
        };

    } // namespace auto_object_detail

    typedef boost::result_of<op_unfuse(auto_object_detail::base_op)>::type op_auto_object;
    PSTADE_CONSTANT(auto_object, (op_auto_object))


    template<class X>
    struct op_new_shared :
        op_new_ptr< boost::shared_ptr<X> >
    { };

    PSTADE_AUTOMATIC(shared_object, (op_new_shared< boost::pointee<_> >))


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

PSTADE_CALLABLE_NULLARY_RESULT_OF_TEMPLATE(pstade::op_new, 1)

// These macros work if 'nullary_result_type' is declared.
PSTADE_CALLABLE_NULLARY_RESULT_OF_TEMPLATE(pstade::op_new_ptr, 1)
PSTADE_CALLABLE_NULLARY_RESULT_OF_TEMPLATE(pstade::op_new_auto, 1)
PSTADE_CALLABLE_NULLARY_RESULT_OF_TEMPLATE(pstade::op_new_shared, 1)


#endif
#else
#define n BOOST_PP_ITERATION()


template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
{
    return new X(BOOST_PP_ENUM_PARAMS(n, a));
}


#undef n
#endif
