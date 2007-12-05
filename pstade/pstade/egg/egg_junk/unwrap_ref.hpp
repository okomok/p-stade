#ifndef PSTADE_EGG_DETAIL_UNWRAP_REF_HPP
#define PSTADE_EGG_DETAIL_UNWRAP_REF_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/ref.hpp>
#include <pstade/pass_by.hpp>


namespace pstade { namespace egg { namespace detail {


    template<class X>
    struct unwrapped_of :
        pass_by_value<X>
    { };

    template<class X>
    struct unwrapped_of< boost::reference_wrapper<X> >
    {
        typedef X& type;
    };

    template<class X>
    struct unwrapped_of< boost::reference_wrapper<X> const >
    {
        typedef X& type;
    };


    template<class X> inline
    X& unwrap_ref(boost::reference_wrapper<X> x)
    {
        return x.get();
    }

    template<class X> inline
    X  unwrap_ref(X const& x)
    {
        return x;
    }


} } } // namespace pstade::egg::detail


#endif
