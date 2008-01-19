#ifndef PSTADE_EGG_TO_STRING_HPP
#define PSTADE_EGG_TO_STRING_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <string>
#include <pstade/pod_constant.hpp>
#include "./ambi.hpp"
#include "./lexical.hpp"


namespace pstade { namespace egg {


    namespace to_string_detail {


        template<class String>
        struct to_ :
            result_of_ambi0<
                typename X_lexical_cast<String>::function_type,
                typename X_lexical_cast<String>::strategy_type,
                typename X_lexical_cast<String>::strategy_type
            >
        { };


    } // namespace to_string_detail


    typedef to_string_detail::to_<std::string>::type T_to_string;
    PSTADE_POD_CONSTANT((T_to_string), to_string) = PSTADE_EGG_AMBI({});

    typedef to_string_detail::to_<std::wstring>::type T_to_wstring;
    PSTADE_POD_CONSTANT((T_to_wstring), to_wstring) = PSTADE_EGG_AMBI({});


} } // namespace pstade::egg


#endif
