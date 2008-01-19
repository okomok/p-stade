#ifndef PSTADE_EGG_DETAIL_TO_AMBI0_HPP
#define PSTADE_EGG_DETAIL_TO_AMBI0_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "../ambi.hpp"
#include "../function_fwd.hpp"


namespace pstade { namespace egg { namespace detail {


    template<class Little, class Bytag>
    struct little_to_ambi0 :
        result_of_ambi0<function<Little, Bytag>, Bytag, Bytag>
    { };


    template<class Base, class Bytag>
    struct base_to_ambi0 :
        result_of_ambi0<Base, Bytag, Bytag>
    { };


} } } // namespace pstade::egg::detail


#endif
