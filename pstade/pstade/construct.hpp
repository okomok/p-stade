#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_CONSTRUCT_HPP
#define PSTADE_CONSTRUCT_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/auto_castable.hpp>
#include <pstade/callable.hpp>
#include <pstade/fuse.hpp>
#include <pstade/nonassignable.hpp>
#include <pstade/unfuse.hpp>
#include <pstade/preprocessor.hpp>


namespace pstade {


    template<class X>
    struct construct :
        callable<construct<X>, X>
    {
        PSTADE_CALLABLE_PRIMARY_APPLY
        {
            typedef X type;
        };

        // 0ary
        template<class Result>
        Result call() const
        {
            return Result();
        }

        // workaround for vexing parse
        X call() const
        {
            return X();
        }

        // 1ary-
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_CALLABLE_MAX_ARITY, <pstade/construct.hpp>))
        #include BOOST_PP_ITERATE()
 
    };


    namespace constructed_detail {


        template<class Arguments>
        struct temp :
            private nonassignable
        {
            template<class X>
            operator X() const
            {
                return fuse(construct<X>())(m_args);
            }

            template<class X>
            X get() const
            {
                return fuse(construct<X>())(m_args);
            }

            explicit temp(Arguments& args) :
                m_args(args)
            { }

        private:
            Arguments m_args;
        };


        struct base :
            callable<base>
        {
            template<class Myself, class Arguments>
            struct apply
            {
                typedef temp<Arguments> const type;
            };

            template<class Result, class Arguments>
            Result call(Arguments& args) const
            {
                // 'args' is destructed as soon as this 'call' returns.
                // So, 'temp' must *copy* it to 'm_args'.
                return Result(args); 
            }
        };


        struct aux :
            boost::result_of<op_unfuse(base)>::type
        {
            template<class X>
            operator X() const
            {
                return X();
            }
        };


    } // namespace constructed_detail            


    PSTADE_CONSTANT(constructor, (constructed_detail::aux))


} // namespace pstade


#endif
#else
#define n BOOST_PP_ITERATION()


template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
Result call(PSTADE_PP_ENUM_REF_PARAMS(n, A, a)) const
{
    return Result(BOOST_PP_ENUM_PARAMS(n, a));
}


#undef n
#endif
