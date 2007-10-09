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
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/pod_constant.hpp>
#include "../by_cref.hpp"


#define PSTADE_EGG_CHAR_CONVERSION(O, F) \
    struct BOOST_PP_CAT(baby_, O) \
    { \
        template<class Myself, class CharT, class Locale = void> \
        struct apply : \
            boost::remove_cv<CharT> \
        { }; \
        \
        template<class Result, class CharT> \
        Result call(CharT& ch, std::locale const& loc) const \
        { \
            return F(ch, loc); \
        } \
        \
        template<class Result, class CharT> \
        Result call(CharT& ch) const \
        { \
            return F(ch, std::locale()); \
        } \
    }; \
    \
    typedef pstade::egg::function<BOOST_PP_CAT(baby_, O), by_cref> BOOST_PP_CAT(T_, O); \
    \
    PSTADE_ADL_BARRIER(char_conversion) { \
        PSTADE_POD_CONSTANT((BOOST_PP_CAT(T_, O)), O) = {{}}; \
    } \
/**/


#endif
