#ifndef PSTADE_ADAPTABLE_HPP
#define PSTADE_ADAPTABLE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <functional>
#include <boost/utility/result_of.hpp>
#include <pstade/const_fun.hpp>
#include <pstade/function.hpp>
#include <pstade/specified.hpp>


namespace pstade {


    namespace adaptable_detail {


        template<class A0, class Callable>
        struct return_op1 :
            std::unary_function<
                A0,
                typename boost::result_of<PSTADE_CONST_FUN_TPL(Callable)(A0&)>::type
            >
        {
            typename boost::result_of<PSTADE_CONST_FUN_TPL(Callable)(A0&)>::type
            operator()(A0& a0) const
            {
                return m_fun(a0);
            }

            explicit return_op1(Callable fun) :
                m_fun(fun)
            { }

        private:
            Callable m_fun;
        };


        template<class A0, class A1, class Callable>
        struct return_op2 :
            std::binary_function<
                A0, A1,
                typename boost::result_of<PSTADE_CONST_FUN_TPL(Callable)(A0&, A1&)>::type
            >
        {
            typename boost::result_of<PSTADE_CONST_FUN_TPL(Callable)(A0&, A1&)>::type
            operator()(A0& a0, A1& a1) const
            {
                return m_fun(a0, a1);
            }

            explicit return_op2(Callable fun) :
                m_fun(fun)
            { }

        private:
            Callable m_fun;
        };


    } // namespace adaptable_detail


    // Let adaptable_unary adaptable.
    template<class A0, class Callable>
    struct adaptable_unary_base
    {
        typedef typename
            adaptable_detail::return_op1<A0, Callable>
        result_type;

        result_type operator()(Callable& fun) const
        {
            return result_type(fun);
        }
    };

    template<class A0>
    struct op_adaptable_unary :
        function< adaptable_unary_base<A0, boost::mpl::_1> >
    { };

    PSTADE_SPECIFIED1(adaptable_unary, op_adaptable_unary, 1)


    // Let 'adaptabe2' adaptable.
    template<class A0, class A1, class Callable>
    struct adaptable_binary_base
    {
        typedef typename
            adaptable_detail::return_op2<A0, A1, Callable>
        result_type;

        result_type operator()(Callable& fun) const
        {
            return result_type(fun);
        }
    };

    template<class A0, class A1>
    struct op_adaptable_binary :
        function< adaptable_binary_base<A0, A1, boost::mpl::_1> >
    { };

    PSTADE_SPECIFIED1(adaptable_binary, op_adaptable_binary, 2)


} // namespace pstade


#endif
