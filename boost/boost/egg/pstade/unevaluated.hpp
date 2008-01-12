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


#include <boost/assert.hpp>
#include <boost/egg/pstade/boost_workaround.hpp>


namespace pstade {


    template<class X> inline
    X unevaluated()
    { 
        BOOST_ASSERT(!"unevaluated");
        throw "unevaluated";
#if BOOST_WORKAROUND(__GNUC__, BOOST_TESTED_AT(4))
        // suppress warning: no return statement in function returning non-void
        return unevaluated<X>();
#endif
    }


} // namespace pstade


#endif
