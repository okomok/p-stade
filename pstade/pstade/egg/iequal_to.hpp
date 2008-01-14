#ifndef PSTADE_EGG_IEQUAL_TO_HPP
#define PSTADE_EGG_IEQUAL_TO_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <locale>
#include <pstade/pod_constant.hpp>


namespace pstade { namespace egg {


    struct T_iequal_to
    {
        typedef bool result_type;

        template<class CharT>
        bool operator()(CharT ch1, CharT ch2, std::locale const& loc) const
        {
            return std::tolower(ch1, loc) == std::tolower(ch2, loc);
        }

        template<class CharT>
        bool operator()(CharT ch1, CharT ch2) const
        {
            return (*this)(ch1, ch2, std::locale());
        }
    };


    PSTADE_POD_CONSTANT((T_iequal_to), iequal_to) = {};


} } // namespace pstade::egg


#endif
