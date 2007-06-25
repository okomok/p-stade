#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_POLYMORPHIC_HPP
#define PSTADE_POLYMORPHIC_HPP


#include <boost/version.hpp>
#if BOOST_VERSION >= 103500
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Converts DeferredCallableObject into PolymorphicFunctionObject.
// Remember that gcc sometimes fails to compile trivial code for some reason.
//
// Wow, PolymorphicFunctionObject was deprecated.


#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/deferred.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/preprocessor.hpp>


#if !defined(PSTADE_POLYMORPHIC_MAX_ARITY)
    #define PSTADE_POLYMORPHIC_MAX_ARITY 5
#endif


namespace pstade {


    namespace polymorphic_detail {


        template<class Callable>
        struct return_op
        {
            template<PSTADE_PP_ENUM_PARAMS_WITH(BOOST_PP_INC(PSTADE_POLYMORPHIC_MAX_ARITY), class A, = void)>
            struct result
            { };

            #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_POLYMORPHIC_MAX_ARITY, <pstade/polymorphic.hpp>))
            #include BOOST_PP_ITERATE()

            explicit return_op()
            { }

            explicit return_op(Callable fun) :
                m_fun(fun)
            { }

            typedef Callable base_type;

            Callable base() const
            {
                return m_fun;
            }

        private:
            Callable m_fun;
        };


    } // namespace polymorphic_detail


    PSTADE_OBJECT_GENERATOR(polymorphic, (polymorphic_detail::return_op< deduce<_1, as_value> >))


} // namespace pstade


#endif // BOOST_VERSION >= 103500


#endif
#else
#define n BOOST_PP_ITERATION()


// Can take only lvalues; Fusion algorithms usually give only lvalues.
// Fusion brings a non-reference type into 'result' even if it is a lvalue.

template<BOOST_PP_ENUM_PARAMS(n, class A)>
struct result<BOOST_PP_ENUM_PARAMS(n, A)> :
    boost::result_of<
        PSTADE_DEFERRED(Callable const)(
            PSTADE_PP_ENUM_PARAMS_WITH(n, typename boost::add_reference<A, >::type)
        )
    >
{ };

template<BOOST_PP_ENUM_PARAMS(n, class A)>
typename result<PSTADE_PP_ENUM_PARAMS_WITH(n, A, &)>::type
operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
{
    return m_fun(BOOST_PP_ENUM_PARAMS(n, a));
}


#undef n
#endif
