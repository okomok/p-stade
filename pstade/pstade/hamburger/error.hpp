#ifndef PSTADE_HAMBURGER_ERROR_HPP
#define PSTADE_HAMBURGER_ERROR_HPP


// PStade.Hamburger
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <stdexcept> // runtime_error
#include <string>


namespace pstade { namespace hamburger {


struct error :
    std::runtime_error
{
private:
    typedef std::runtime_error super_t;

public:
    explicit error(std::string what) :
        super_t(what)
    { }
};


} } // namespace pstade::hamburger


#endif
