#ifndef PSTADE_GRAVY_CREATE_RESULT_HPP
#define PSTADE_GRAVY_CREATE_RESULT_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/instance.hpp>
#include "./include/windows.hpp"


namespace pstade { namespace gravy {


    PSTADE_INSTANCE((LRESULT) const, create_success, (0))
    PSTADE_INSTANCE((LRESULT) const, create_failure, (-1))


} } // namespace pstade::gravy


#endif
