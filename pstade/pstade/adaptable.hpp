#ifndef PSTADE_ADAPTABLE_HPP
#define PSTADE_ADAPTABLE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Converts a FunctionObject supporting 'result_of' into an Adaptable one.


#include <functional>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/deferred.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/specified.hpp>


namespace pstade {


    namespace adaptable_detail {


        template<class Callable, class A0>
        struct return_fun1 :
            std::unary_function<
                A0,
                typename boost::result_of<PSTADE_DEFERRED(Callable const)(A0&)>::type
            >
        {
            typename boost::result_of<PSTADE_DEFERRED(Callable const)(A0&)>::type
            operator()(A0& a0) const
            {
                return m_fun(a0);
            }

            explicit return_fun1(Callable fun) :
                m_fun(fun)
            { }

        private:
            Callable m_fun;
        };


        template<class Callable, class A0, class A1>
        struct return_fun2 :
            std::binary_function<
                A0, A1,
                typename boost::result_of<PSTADE_DEFERRED(Callable const)(A0&, A1&)>::type
            >
        {
            typename boost::result_of<PSTADE_DEFERRED(Callable const)(A0&, A1&)>::type
            operator()(A0& a0, A1& a1) const
            {
                return m_fun(a0, a1);
            }

            explicit return_fun2(Callable fun) :
                m_fun(fun)
            { }

        private:
            Callable m_fun;
        };


    } // namespace adaptable_detail


    template<class A0>
    struct op_adaptable_unary :
        callable< op_adaptable_unary<A0> >
    { 
        template<class Myself, class Callable>
        struct apply
        {
            typedef
                adaptable_detail::return_fun1<
                    typename pass_by_value<Callable>::type,
                    A0
                >
            type;
        };

        template<class Result, class Callable>
        Result call(Callable& fun) const
        {
            return Result(fun);
        }    
    };

    PSTADE_SPECIFIED1(adaptable_unary, op_adaptable_unary, 1)


    template<class A0, class A1>
    struct op_adaptable_binary :
        callable< op_adaptable_binary<A0, A1> >
    { 
        template<class Myself, class Callable>
        struct apply
        {
            typedef
                adaptable_detail::return_fun2<
                    typename pass_by_value<Callable>::type,
                    A0, A1
                >
            type;
        };

        template<class Result, class Callable>
        Result call(Callable& fun) const
        {
            return Result(fun);
        }    
    };

    PSTADE_SPECIFIED1(adaptable_binary, op_adaptable_binary, 2)


} // namespace pstade


#endif
