#ifndef PSTADE_OVEN_DETAIL_PLUS_HPP
#define PSTADE_OVEN_DETAIL_PLUS_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// <boost/spirit/phoenix/detail/type_deduction.hpp>


#include <boost/mpl/if.hpp> // if_c
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/utility/enable_if.hpp> // disable_if
#include <pstade/egg/function.hpp>


namespace pstade { namespace oven { namespace detail {


template< class X, class Y >
struct result_of_plus
{
private:
    typedef typename boost::remove_cv<X>::type x_t;
    typedef typename boost::remove_cv<Y>::type y_t;

    struct yes { char a[1]; };
    struct non { char a[2]; };
    struct cannot_deduce_result_type_of_plus { };

    template< class X_, class Y_ > static
    yes test(X_ const&);

    template< class X_, class Y_ > static
    typename boost::disable_if< boost::is_same<X_, Y_>,
    non>::type test(Y_ const&);

    template< class X_, class Y_ > static
    cannot_deduce_result_type_of_plus test(...);

    static x_t x;
    static y_t y;

    static bool const is_x =
        sizeof(yes) == sizeof(test<x_t, y_t>(x + y));

public:
    typedef typename boost::mpl::if_c< is_x,
        x_t, y_t
    >::type type;
};


struct baby_plus
{
    template< class Unused, class X, class Y >
    struct result :
        result_of_plus<X, Y>
    { };

    template< class Result, class X, class Y >
    Result call(X const& x, Y const& y)
    {
        return x + y;
    }
};


PSTADE_EGG_FUNCTION(plus, baby_plus)


} } } // namespace pstade::oven::detail


#endif
