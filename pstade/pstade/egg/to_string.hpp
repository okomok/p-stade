#ifndef PSTADE_EGG_TO_STRING_HPP
#define PSTADE_EGG_TO_STRING_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <string>
#include <pstade/pod_constant.hpp>
#include "./ambi.hpp"
#include "./lexical_cast.hpp"


namespace pstade { namespace egg {


    typedef
        result_of_ambi0<
            X_lexical_cast<std::string>::function_type
        >::type
    T_to_string;

    PSTADE_POD_CONSTANT((T_to_string), to_string) = PSTADE_EGG_AMBI_L {} PSTADE_EGG_AMBI_R;


    typedef
        result_of_ambi0<
            X_lexical_cast<std::wstring>::function_type
        >::type
    T_to_wstring;

    PSTADE_POD_CONSTANT((T_to_wstring), to_wstring) = PSTADE_EGG_AMBI_L {} PSTADE_EGG_AMBI_R;


} } // namespace pstade::egg


#endif
