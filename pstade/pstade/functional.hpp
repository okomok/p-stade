#ifndef PSTADE_FUNCTIONAL_HPP
#define PSTADE_FUNCTIONAL_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// std::unary/binary_negate requires 'Predicate'
// to be Adaptable, which seems to be deprecated.
// See [1] at Boost.Phoenix2 about 'deduce_result'.
//
// [1] <boost/spirit/phoenix/detail/type_deduction.hpp>


#include <boost/mpl/if.hpp> // if_c
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/utility/enable_if.hpp> // disable_if
#include <pstade/adl_barrier.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/by_value.hpp>
#include <pstade/instance.hpp>
#include <pstade/oui_non.hpp>


namespace pstade {

PSTADE_ADL_BARRIER(functional) {


namespace not_detail {


    template< class Predicate >
    struct baby_fun
    {
        explicit baby_fun(Predicate const& pred) :
            m_pred(pred)
        { }

        template< class Unused, class T0, class T1 = void >
        struct result
        {
            typedef bool type;
        };

        template< class Result, class T0 >
        Result call(T0& a0)
        {
            return !m_pred(a0);
        }

        template< class Result, class T0, class T1 >
        Result call(T0& a0, T1& a1)
        {
            return !m_pred(a0, a1);
        }

    private:
        Predicate m_pred;
    };


    struct baby
    {
        template< class Unused, class Predicate >
        struct result
        {
            typedef typename egg::by_value<Predicate>::type pred_t;
            typedef egg::function< baby_fun<pred_t> > type;
        };

        template< class Result, class Predicate >
        Result call(Predicate& pred)
        {
            return Result(pred);
        }
    };


} // namespace not_detail


PSTADE_EGG_FUNCTION_(not_, not_detail::baby)


struct equal_to_fun
{
    typedef bool result_type;

    template< class X, class Y >
    bool operator()(X const& x, Y const& y) const
    {
        return x == y;
    }
};


PSTADE_INSTANCE(equal_to_fun const, equal_to, value)


struct less_fun
{
    typedef bool result_type;

    template< class X, class Y >
    bool operator()(X const& x, Y const& y) const
    {
        return x < y;
    }
};


PSTADE_INSTANCE(less_fun const, less, value)


struct plus_failed_to_deduce_result_type
{ };


namespace plus_detail {


    template< class X, class Y >
    struct deduce_result
    {
    private:
        typedef typename boost::remove_cv<X>::type x_t;
        typedef typename boost::remove_cv<Y>::type y_t;

        template< class X_, class Y_ > static
        oui test(X_ const&);

        template< class X_, class Y_ > static
        typename boost::disable_if<boost::is_same<X_, Y_>,
        non>::type test(Y_ const&);

        template< class X_, class Y_ > static
        plus_failed_to_deduce_result_type test(...);

        static x_t x;
        static y_t y;

        static bool const is_x =
            sizeof( test<x_t, y_t>(x + y) ) == sizeof(oui);

    public:
        typedef typename boost::mpl::if_c< is_x,
            x_t, y_t
        >::type type;
    };


    struct baby
    {
        template< class Unused, class X, class Y >
        struct result :
            deduce_result<X, Y>
        { };

        template< class Result, class X, class Y >
        Result call(X const& x, Y const& y)
        {
            return x + y;
        }
    };


} // namespace plus_detail


PSTADE_EGG_FUNCTION(plus, plus_detail::baby)


} // ADL barrier

} // namespace pstade


#endif
