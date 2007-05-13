#ifndef PSTADE_SAUSAGE_EXCEPTION_HPP
#define PSTADE_SAUSAGE_EXCEPTION_HPP


// PStade.Sausage
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <stdexcept> // runtime_error


namespace pstade { namespace sausage {


struct exit_exception :
    std::runtime_error
{
    exit_exception() :
        std::runtime_error("routine exit")
    { };
};


} } // namespace pstade::sausage


#endif
