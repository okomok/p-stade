#ifndef BOOST_EGG_IEQUAL_TO_HPP
#define BOOST_EGG_IEQUAL_TO_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <locale>
#include <boost/egg/const.hpp>


namespace boost { namespace egg {


    struct T_iequal_to
    {
        typedef bool result_type;

        template<class CharT>
        bool operator()(CharT ch1, CharT ch2, std::locale const &loc) const
        {
            return std::tolower(ch1, loc) == std::tolower(ch2, loc);
        }

        template<class CharT>
        bool operator()(CharT ch1, CharT ch2) const
        {
            return (*this)(ch1, ch2, std::locale());
        }
    };

    BOOST_EGG_CONST((T_iequal_to), iequal_to) = {};


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
