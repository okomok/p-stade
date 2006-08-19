#ifndef PSTADE_LEXICAL_CAST_HPP
#define PSTADE_LEXICAL_CAST_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/lexical_cast.hpp>
#include <pstade/egg/baby_auto.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>


namespace pstade {


template< class To, class From > inline
To lexical_cast(From const& from)
{
    return boost::lexical_cast<To>(from);
}


struct lexical_cast_class
{
    template< class To, class From >
    static To call(From const& from)
    {
        return pstade::lexical_cast<To>(from);
    }
};


PSTADE_EGG_FUNCTION(lexical, egg::baby_auto<lexical_cast_class>)
PSTADE_EGG_PIPABLE(lexicalized, egg::baby_auto<lexical_cast_class>)


} // namespace pstade


#endif
