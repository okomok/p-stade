#ifndef PSTADE_EGG_DETAIL_CHAR_CONVERSION_HPP
#define PSTADE_EGG_DETAIL_CHAR_CONVERSION_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <locale>
#include <boost/preprocessor/cat.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/pod_constant.hpp>
#include "../function_by_cref.hpp"


#define PSTADE_EGG_CHAR_CONVERSION(O, F) \
    struct BOOST_PP_CAT(baby_, O) \
    { \
        template<class Myself, class CharT, class Locale = void> \
        struct apply \
        { \
            typedef CharT type; \
        }; \
        \
        template<class Result, class CharT> \
        Result call(CharT const& ch, std::locale const& loc) const \
        { \
            return F(ch, loc); \
        } \
        \
        template<class Result, class CharT> \
        Result call(CharT const& ch) const \
        { \
            return F(ch, std::locale()); \
        } \
    }; \
    \
    typedef pstade::egg::function_by_cref<BOOST_PP_CAT(baby_, O)> BOOST_PP_CAT(op_, O); \
    \
    PSTADE_ADL_BARRIER(char_conversion) { \
        PSTADE_POD_CONSTANT((BOOST_PP_CAT(op_, O)), O) = {{}}; \
    } \
/**/


#endif
