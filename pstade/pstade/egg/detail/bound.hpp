#ifndef PSTADE_EGG_DETAIL_BOUND_HPP
#define PSTADE_EGG_DETAIL_BOUND_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// You can't unwrap a reference_wrapper so that
// a "nested" bind doesn't try to copy an unwrapped object.
// e.g. bind(bind, ...boost::ref(x));
// OTOH, Boost.Lambda unwraps one. That behavior seems a defect.


#include <cstddef> // size_t
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_array.hpp>
#include <pstade/pass_by.hpp>


namespace pstade { namespace egg { namespace detail {


    template<class A>
    struct bound;

    // To be Regular, not const-qualified.
    template<class A>
    struct bound<A const>
    {
        BOOST_MPL_ASSERT_NOT((boost::is_array<A>)); // different from Boost.Lambda way.
        typedef typename pass_by_value<A>::type type;
    };


    // const lvalue, because operator() is const.
    template<class A>
    struct unbound
    {
        BOOST_MPL_ASSERT_NOT((boost::is_array<A>));
        typedef A const &type;
    };


    struct as_bound
    {
        template<class A>
        struct apply :
            bound<A>
        { };
    };


} } } // namespace pstade::egg::detail


#endif
