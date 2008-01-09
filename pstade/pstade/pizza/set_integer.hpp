#ifndef PSTADE_PIZZA_SET_INTEGER_HPP
#define PSTADE_PIZZA_SET_INTEGER_HPP


// PStade.Pizza
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/copy.hpp>
#include <pstade/egg/lexical.hpp>
#include <pstade/gravy/sdk/tchar.hpp>
#include <pstade/gravy/tstring.hpp>
#include "./set_string.hpp"


namespace pstade { namespace pizza {


template< class Profile, class CStringizable, class IntegerT >
void set_integer(Profile& pr, const CStringizable& valueName, IntegerT value)
{
    pizza::set_string(pr, valueName,
        egg::copy<gravy::tstring>(value|egg::lexical()).c_str()
    );
}


} } // namespace pstade::pizza


#endif
