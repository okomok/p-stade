#ifndef PSTADE_MAKE_BOOL_HPP
#define PSTADE_MAKE_BOOL_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Suppress a msvc warning.


#include <pstade/pod_constant.hpp>
#include <pstade/boost_workaround.hpp>


namespace pstade {


    struct T_make_bool
    {
        typedef bool result_type;

        template<class X>
        bool operator()(X const& x) const
        {
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400))
            return x && true;
#else
            return x;
#endif
        }
    };


    PSTADE_POD_CONSTANT((T_make_bool), make_bool) = {};


} // namespace pstade


#endif
