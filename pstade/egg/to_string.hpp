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
#include <boost/preprocessor/facilities/identity.hpp>
#include <pstade/pod_constant.hpp>
#include "./auxiliary.hpp"
#include "./lexical_cast.hpp"


namespace pstade { namespace egg {


    typedef
        result_of_auxiliary0<
            xp_lexical_cast<std::string>
        >::type
    op_to_string;

    PSTADE_POD_CONSTANT((op_to_string), to_string) = PSTADE_EGG_AUXILIARY_RESULT_INITIALIZER(BOOST_PP_IDENTITY({}));


    typedef
        result_of_auxiliary0<
            xp_lexical_cast<std::wstring>
        >::type
    op_to_wstring;

    PSTADE_POD_CONSTANT((op_to_wstring), to_wstring) = PSTADE_EGG_AUXILIARY_RESULT_INITIALIZER(BOOST_PP_IDENTITY({}));


} } // namespace pstade::egg


#endif
