#ifndef PSTADE_SYMMETRIC_HPP
#define PSTADE_SYMMETRIC_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Converts a functor to the one supporting...
//
// foo(a); a|foo(); a|foo;


#include <boost/preprocessor/cat.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/unparenthesize.hpp>


namespace pstade {


    namespace symmetric_detail {


        template<class UnaryFun>
        struct right :
            callable<right<UnaryFun>, right<UnaryFun> const&>
        {
            template<class Myself, class A>
            struct apply :
                boost::result_of<UnaryFun(A&)>
            { };

            template<class Result>
            Result call() const
            {
                return *this;
            }

            template<class Result, class A>
            Result call(A& a) const
            {
                return m_fun(a);
            }

            explicit right()
            { }

            explicit right(UnaryFun const& fun) :
                m_fun(fun)
            { }

        private:
            UnaryFun m_fun;
        };


        template<class A, class UnaryFun> inline
        typename boost::result_of<right<UnaryFun>(A&)>::type
        operator|(A& a, right<UnaryFun> const& r)
        {
            return r(a);
        };

        template<class A, class UnaryFun> inline
        typename boost::result_of<right<UnaryFun>(PSTADE_DEDUCED_CONST(A)&)>::type
        operator|(A const& a, right<UnaryFun> const& r)
        {
            return r(a);
        };


    } // namespace symmetric_detail


    PSTADE_OBJECT_GENERATOR(symmetric, (symmetric_detail::right< deduce<_1, to_value> >))


    #define PSTADE_SYMMETRIC(Object, UnaryFun) \
        typedef \
            ::boost::result_of< ::pstade::op_symmetric(PSTADE_UNPARENTHESIZE(UnaryFun)) >::type \
        BOOST_PP_CAT(op_, Object); \
        \
        PSTADE_CONSTANT(Object, (BOOST_PP_CAT(op_, Object))) \
    /**/


} // namespace pstade


PSTADE_CALLABLE_NULLARY_RESULT_OF_TEMPLATE((pstade)(symmetric_detail)(right), 1)


#endif
