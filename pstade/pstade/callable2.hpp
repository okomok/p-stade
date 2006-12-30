#ifndef PSTADE_CALLABLE2_HPP
#define PSTADE_CALLABLE2_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp> // BOOST_NESTED_TEMPLATE
#include <pstade/adl_barrier.hpp>
#include <pstade/callable1.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/lambda_sig.hpp>


namespace pstade {


    namespace callable_detail {


        template<class Derived, class A0, class A1>
        struct result2 : // Prefer inheritance for SFINAE.
            Derived::BOOST_NESTED_TEMPLATE apply<
                Derived,
                typename meta_argument<A0>::type,
                typename meta_argument<A1>::type
            >
        { };


    } // namespace callable_detail


    PSTADE_ADL_BARRIER(callable2) {


    template<class Derived>
    struct callable2 :
        lambda_sig
    {

        template<class FunCall>
        struct result
        { }; // complete for SFINAE.
    

        // 1ary

        template<class Fun, class A0>
        struct result<Fun(A0)> :
            callable_detail::result1<Derived, A0>
        { };

        template<class A0>
        typename callable_detail::result1<Derived, A0&>::type
        operator()(A0& a0) const
        {
            return derived().BOOST_NESTED_TEMPLATE call<
                typename callable_detail::result1<Derived, A0&>::type
            >(a0);
        }

        template<class A0>
        typename callable_detail::result1<Derived, PSTADE_DEDUCED_CONST(A0)&>::type
        operator()(A0 const& a0) const
        {
            return derived().BOOST_NESTED_TEMPLATE call<
                typename callable_detail::result1<Derived, PSTADE_DEDUCED_CONST(A0)&>::type
            >(a0);
        }


        // 2ary

        template<class Fun, class A0, class A1>
        struct result<Fun(A0, A1)> :
            callable_detail::result2<Derived, A0, A1>
        { };

        template<class A0, class A1>
        typename callable_detail::result2<Derived, A0&, A1&>::type
        operator()(A0& a0, A1& a1) const
        {
            return derived().BOOST_NESTED_TEMPLATE call<
                typename callable_detail::result2<Derived, A0&, A1&>::type
            >(a0, a1);
        }

        template<class A0, class A1>
        typename callable_detail::result2<Derived, A0&, PSTADE_DEDUCED_CONST(A1)&>::type
        operator()(A0& a0, A1 const& a1) const
        {
            return derived().BOOST_NESTED_TEMPLATE call<
                typename callable_detail::result2<Derived, A0&, PSTADE_DEDUCED_CONST(A1)&>::type
            >(a0, a1);
        }

        template<class A0, class A1>
        typename callable_detail::result2<Derived, PSTADE_DEDUCED_CONST(A0)&, A1&>::type
        operator()(A0 const& a0, A1& a1) const
        {
            return derived().BOOST_NESTED_TEMPLATE call<
                typename callable_detail::result2<Derived, PSTADE_DEDUCED_CONST(A0)&, A1&>::type
            >(a0, a1);
        }

        template<class A0, class A1>
        typename callable_detail::result2 <Derived, PSTADE_DEDUCED_CONST(A0)&, PSTADE_DEDUCED_CONST(A1)&>::type
        operator()(A0 const& a0, A1 const& a1) const
        {
            return derived().BOOST_NESTED_TEMPLATE call<
                typename callable_detail::result2<Derived, PSTADE_DEDUCED_CONST(A0)&, PSTADE_DEDUCED_CONST(A1)&>::type
            >(a0, a1);
        }


    private:
        Derived const& derived() const
        {
            return static_cast<Derived const&>(*this);
        }

    }; // struct callable2


    } // ADL barrier


} // namespace pstade


#endif
