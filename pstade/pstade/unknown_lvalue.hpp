#ifndef PSTADE_UNKNOWN_LVALUE_HPP
#define PSTADE_UNKNOWN_LVALUE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Used with Boost.Concept and Boost.Typeof.


#include <stdexcept> // logic_error
#include <boost/assert.hpp>
#include <boost/throw_exception.hpp>


namespace pstade {


    // If you dislike to declare members in Concept class...,
    // (also, this can work around GCC bug mentioned above.)
    template<class X> inline
    X& unknown_lvalue()
    { 
        BOOST_ASSERT(false);
        boost::throw_exception(std::logic_error("never link 'pstade::unknown_lvalue'!"));
    }


} // namespace pstade


#endif
