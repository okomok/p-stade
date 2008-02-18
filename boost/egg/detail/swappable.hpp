#ifndef BOOST_EGG_DETAIL_SWAPPABLE_HPP
#define BOOST_EGG_DETAIL_SWAPPABLE_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/detail/adl_barrier.hpp>
#include <boost/egg/detail/null_injector.hpp>


namespace boost { namespace egg { namespace details {


BOOST_EGG_ADL_BARRIER(swappable) {
    template< class Derived, class Injector = null_injector<Derived> >
    struct swappable :
        Injector
    {
        friend
        void swap(Derived& x, Derived& y)
        {
            x.swap(y);
        }
    };
}


} } } // namespace boost::egg::details


#endif
