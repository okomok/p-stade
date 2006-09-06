#ifndef PSTADE_TOMATO_WINDOW_CREATE_RESULT_HPP
#define PSTADE_TOMATO_WINDOW_CREATE_RESULT_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/sdk/windows.hpp>
#include <pstade/instance.hpp>


namespace pstade { namespace tomato {


PSTADE_INSTANCE(LRESULT const, create_success, (0))
PSTADE_INSTANCE(LRESULT const, create_failure, (-1))


} } // namespace pstade::tomato


#endif
