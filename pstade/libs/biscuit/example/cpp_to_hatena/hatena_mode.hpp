#ifndef PSTADE_LIBS_BISCUIT_EXAMPLE_CPP_TO_HATENA_HATENA_MODE_HPP
#define PSTADE_LIBS_BISCUIT_EXAMPLE_CPP_TO_HATENA_HATENA_MODE_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/instance.hpp>


namespace cpp_to_hatena {


namespace hatena_mode_detail {

    PSTADE_INSTANCE(bool, is_on, (true))

}


inline
void set_hatena_mode(bool on)
{
    hatena_mode_detail::is_on = on;
}


inline
bool is_hatena_mode()
{
    return hatena_mode_detail::is_on;
}


} // namespace cpp_to_hatena


#endif
