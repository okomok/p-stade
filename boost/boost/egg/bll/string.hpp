#ifndef BOOST_EGG_BLL_STRING_HPP
#define BOOST_EGG_BLL_STRING_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/detail/std_string_fwd.hpp>
#include <boost/egg/bll/extension_fwd.hpp>


namespace boost { namespace lambda {


    template<class CharT, class Traits, class Alloc>
    struct plain_return_type_2< arithmetic_action<plus_action>,
        std::basic_string<CharT, Traits, Alloc>, std::basic_string<CharT, Traits, Alloc> >
    {
        typedef std::basic_string<CharT, Traits, Alloc> type;
    };


} } // namespace boost::lambda


#include <boost/egg/detail/suffix.hpp>
#endif
