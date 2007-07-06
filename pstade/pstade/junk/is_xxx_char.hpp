#ifndef PSTADE_EGG_DETAIL_IS_XXX_CHAR_HPP
#define PSTADE_EGG_DETAIL_IS_XXX_CHAR_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <locale>
#include <boost/preprocessor/cat.hpp>
#include <pstade/preprocessor.hpp> // PSTADE_PP_CAT3
#include "../object.hpp"


#define PSTADE_EGG_IS_XXX_CHAR(T) \
    struct PSTADE_PP_CAT3(op_, is_, T) \
    { \
        typedef bool result_type; \
        \
        template<class CharT> \
        bool operator()(CharT ch, std::locale const& loc) const \
        { \
            return std::BOOST_PP_CAT(is, T)(ch, loc); \
        } \
        \
        template<class CharT> \
        bool operator()(CharT ch) const \
        { \
            return (*this)(ch, std::locale()); \
        } \
    }; \
    \
    PSTADE_EGG_OBJECT((PSTADE_PP_CAT3(op_, is_, T)), BOOST_PP_CAT(is_, T)) = {}; \
/**/


#endif
