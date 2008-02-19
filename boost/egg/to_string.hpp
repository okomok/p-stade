#ifndef BOOST_EGG_TO_STRING_HPP
#define BOOST_EGG_TO_STRING_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <string>
#include <boost/egg/ambi.hpp>
#include <boost/egg/by_cref.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/lexical.hpp>


namespace boost { namespace egg {


    typedef result_of_ambi0<X_lexical_cast<std::string>, by_cref>::type T_to_string;
    BOOST_EGG_CONST((T_to_string), to_string) = BOOST_EGG_AMBI({});

    typedef result_of_ambi0<X_lexical_cast<std::wstring>, by_cref>::type T_to_wstring;
    BOOST_EGG_CONST((T_to_wstring), to_wstring) = BOOST_EGG_AMBI({});


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
