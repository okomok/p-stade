#ifndef PSTADE_EGG_TO_LOWER_HPP
#define PSTADE_EGG_TO_LOWER_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <locale> // tolower
#include <pstade/adl_barrier.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pod_constant.hpp>
#include "./function.hpp"


namespace pstade { namespace egg {


    namespace to_lower_detail {


        struct baby
        {
            template<class Myself, class CharT, class Locale = void>
            struct apply :
                pass_by_value<CharT>
            { };

            template<class Result, class CharT>
            Result call(CharT ch, std::locale const& loc) const
            {
                return std::tolower(ch, loc);
            }

            template<class Result, class CharT>
            Result call(CharT ch) const
            {
                return std::tolower(ch, std::locale());
            }
        };


    } // namespace to_lower_detail


    typedef function<to_lower_detail::baby> op_to_lower;

    PSTADE_ADL_BARRIER(to_lower) { // for 'boost'
        PSTADE_POD_CONSTANT((op_to_lower), to_lower) = {{}};
    }


} } // namespace pstade::egg


#endif
