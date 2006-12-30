#ifndef PSTADE_CALLABLE1_HPP
#define PSTADE_CALLABLE1_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp> // BOOST_NESTED_TEMPLATE
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/lambda_sig.hpp>


namespace pstade {


    namespace callable_detail {


        // Add const-qualifier if rvalue is specified.
        template<class A>
        struct meta_argument :
            boost::remove_reference<
                // VC++ warns against 'A const' if 'A' is reference, so...
                typename boost::add_const<A>::type
            >
        { };


        template<class Derived, class A0>
        struct result1 : // Prefer inheritance for SFINAE.
            Derived::BOOST_NESTED_TEMPLATE apply<
                Derived,
                typename meta_argument<A0>::type
            >
        { };


    } // namespace callable_detail


    PSTADE_ADL_BARRIER(callable1) {


    template<class Derived>
    struct callable1 :
        lambda_sig
    {
        template<class FunCall>
        struct result
        { }; // complete for SFINAE.

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

    private:
        Derived const& derived() const
        {
            return static_cast<Derived const&>(*this);
        }

    }; // struct callable1


    } // ADL barrier


} // namespace pstade


#endif
