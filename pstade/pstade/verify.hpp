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
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pipable.hpp>


namespace pstade {


    struct op_verify :
        callable<op_verify>
    {
        template< class Myself, class T >
        struct apply
        {
            typedef T& type;
        };

        template< class Result, class T >
        Result call(T& x) const // doesn't add 'const' to 'T'.
        {
            BOOST_ASSERT(!!x); // 'operator!' is safer.
            return x;
        }
    };


PSTADE_CONSTANT(verify, (op_verify))
PSTADE_PIPABLE(verified, (op_verify))


} // namespace pstade


#endif
