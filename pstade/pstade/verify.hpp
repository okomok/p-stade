#ifndef PSTADE_VERIFY_HPP
#define PSTADE_VERIFY_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Never throws, use in destructors.


#include <boost/assert.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>


namespace pstade {


namespace verify_detail {


    struct baby
    {
        template< class Unused, class T >
        struct result :
            boost::add_reference<T>
        { };

        template< class Result, class T >
        Result call(T& x)
        {
            BOOST_ASSERT(!!x); // I prefer 'operator!'.
            return x;
        }
    };


} // namespace verify_detail


PSTADE_EGG_FUNCTION(verify, verify_detail::baby)
PSTADE_EGG_PIPABLE(verified, verify_detail::baby)


} // namespace pstade


#endif
