#ifndef PSTADE_VERIFY_HPP
#define PSTADE_VERIFY_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Never throws, use in destructors.
// 'x || (assert(false), false);' is better?


#include <boost/assert.hpp>
#include <pstade/callable.hpp>
#include <pstade/auxiliary.hpp>


namespace pstade {


    namespace verify_detail {


        struct op :
            callable<op>
        {
            template<class Myself, class T>
            struct apply
            {
                typedef T& type;
            };

            template<class Result, class T>
            Result call(T& x) const // doesn't add 'const' to 'T'.
            {
                BOOST_ASSERT(!!x); // 'operator!' is safer.
                return x;
            }
        };


    } // namespace verify_detail


    PSTADE_AUXILIARY0(verify, (verify_detail::op))


} // namespace pstade


#endif
