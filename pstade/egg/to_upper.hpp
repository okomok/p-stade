#ifndef PSTADE_EGG_TO_UPPER_HPP
#define PSTADE_EGG_TO_UPPER_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <locale> // toupper
#include <pstade/adl_barrier.hpp>
#include <pstade/pass_by.hpp>
#include "./function.hpp"
#include "./object.hpp"


namespace pstade { namespace egg {


    namespace to_upper_detail {


        struct baby
        {
            template<class Myself, class CharT, class Locale = void>
            struct apply :
                pass_by_value<CharT>
            { };

            template<class Result, class CharT>
            Result call(CharT ch, std::locale const& loc) const
            {
                return std::toupper(ch, loc);
            }

            template<class Result, class CharT>
            Result call(CharT ch) const
            {
                return std::toupper(ch, std::locale());
            }
        };


    } // namespace to_upper_detail


    typedef function<to_upper_detail::baby> op_to_upper;

    PSTADE_ADL_BARRIER(to_upper) { // for 'boost'
        PSTADE_EGG_OBJECT((op_to_upper), to_upper) = { {} };
    }


} } // namespace pstade::egg


#endif
