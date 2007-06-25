#ifndef PSTADE_UNEVALUATED_HPP
#define PSTADE_UNEVALUATED_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Copyright Eric Niebler 2006. Distributed under the Boost 
// Software License, Version 1.0. (See accompanying 
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt) 


// What:
//
// Used with Boost.Concept and Boost.Typeof.


#include <stdexcept> // logic_error
#include <boost/assert.hpp>
#include <boost/throw_exception.hpp>


namespace pstade {


    template<class X> inline
    X unevaluated()
    { 
        BOOST_ASSERT("unevaluated was evaluated." && false);
        std::logic_error err("unevaluated was evaluated.");
        boost::throw_exception(err);
    }


} // namespace pstade


#endif
