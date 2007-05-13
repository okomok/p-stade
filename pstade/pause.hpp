#ifndef PSTADE_PAUSE_HPP
#define PSTADE_PAUSE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iostream> // cin
#include <pstade/constant.hpp>


namespace pstade {


    struct op_pause
    {
        typedef int result_type;

        int operator()() const
        {
            std::cin.ignore();
            // or std::cin.get();

            return 0; // for 'main'
        }
    };


    PSTADE_CONSTANT(pause, (op_pause))


} // namespace pstade


#endif
