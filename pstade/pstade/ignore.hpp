#ifndef PSTADE_IGNORE_HPP
#define PSTADE_IGNORE_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// TR1 tuple


#include <pstade/boost_workaround.hpp>
#include <pstade/constant.hpp>


namespace pstade {


    struct T_ignore
    {
        T_ignore()
        { }

        template<class X>
        T_ignore(X const &)
        { }

#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1500))
        T_ignore(int const &)
        { }
#endif

        template<class X>
        T_ignore const & operator=(X const &) const
        {
            return *this;
        };
    };

    PSTADE_CONSTANT(ignore, (T_ignore))


} // namespace pstade


#endif
