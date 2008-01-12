#ifndef BOOST_EGG_BLL_OPTIONAL_HPP
#define BOOST_EGG_BLL_OPTIONAL_HPP
#include "../detail/prefix.hpp"


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/optional/optional_fwd.hpp>
#include "./extension_fwd.hpp"


namespace boost { namespace lambda {


    template<class T>
    struct return_type_1< other_action<contentsof_action>, boost::optional<T> >
    {
        typedef T& type;
    };

    template<class T>
    struct return_type_1< other_action<contentsof_action>, boost::optional<T> const >
    {
        typedef T const& type;
    };

    template<class T>
    struct return_type_1< other_action<contentsof_action>, boost::optional<T&> >
    {
        typedef T& type;
    };

    template<class T>
    struct return_type_1< other_action<contentsof_action>, boost::optional<T&> const >
    {
        typedef T& type;
    };


} } // namespace boost::lambda


#endif
