#ifndef PSTADE_VERIFY_HPP
#define PSTADE_VERIFY_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pipable.hpp>


namespace pstade {


    struct op_verify :
        callable<op_verify>
    {
        template<class Myself, class X, class Assert = void>
        struct apply
        {
            typedef X& type;
        };

        template<class Result, class X, class Assert>
        Result call(X& x, Assert& a) const
        {
            a(x);
            return x;
        }

        template<class Result, class X>
        Result call(X& x) const
        {
            BOOST_ASSERT(!!x); // 'operator!' is safer.
            return x;
        }
    };


    PSTADE_CONSTANT(verify, (op_verify))
    PSTADE_PIPABLE(verified, (op_verify))


} // namespace pstade


#endif
