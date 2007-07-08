#ifndef PSTADE_VERIFY_HPP
#define PSTADE_VERIFY_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/preprocessor/facilities/identity.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/pod_constant.hpp>


namespace pstade {


    namespace verify_detail {


        struct baby
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


    } // namespace verify_detail


    typedef egg::function<verify_detail::baby> op_verify;
    PSTADE_POD_CONSTANT((op_verify), verify) = {{}};

    PSTADE_POD_CONSTANT((egg::result_of_pipable<op_verify>::type), verified)
        = PSTADE_EGG_PIPABLE_RESULT_INITIALIZER(BOOST_PP_IDENTITY({{}});


} // namespace pstade


#endif
