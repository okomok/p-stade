#ifndef PSTADE_VERIFY_HPP
#define PSTADE_VERIFY_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Never throws, use in destructors.
// 'x || (assert(false), false);' is better?


#include <boost/assert.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/pipable.hpp>


namespace pstade {


namespace verify_detail {


    struct baby
    {
        template< class Myself, class T >
        struct apply :
            boost::add_reference<T>
        { };

        template< class Result, class T >
        Result call(T& x) const
        {
            BOOST_ASSERT(!!x); // 'operator!' is safer.
            return x;
        }
    };


} // namespace verify_detail


PSTADE_EGG_FUNCTION(verify, verify_detail::baby)
PSTADE_PIPABLE(verified, verify_fun)


} // namespace pstade


#endif
