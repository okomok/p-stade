#ifndef PSTADE_LOCALE_HPP
#define PSTADE_LOCALE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <locale>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/instance.hpp>
#include <pstade/pass_by.hpp>


namespace pstade {


// is_space etc.
//

#define PSTADE_ctypes \
    (space)(print)(cntrl)(upper)(lower)(alpha)(digit)(punct)(xdigit)(alnum)(graph) \
/**/

#define PSTADE_def_pred(R, _, CType) \
    struct BOOST_PP_CAT(BOOST_PP_CAT(is_, CType), _fun) \
    { \
        typedef bool result_type; \
        \
        template< class CharT > \
        bool operator()(CharT ch, std::locale const& loc) const \
        { \
            return std:: BOOST_PP_CAT(is, CType) (ch, loc); \
        } \
        \
        template< class CharT > \
        bool operator()(CharT ch) const \
        { \
            return (*this)(ch, std::locale()); \
        } \
    }; \
    \
    PSTADE_INSTANCE( \
        BOOST_PP_CAT(BOOST_PP_CAT(is_, CType), _fun) const, \
        BOOST_PP_CAT(is_, CType), value \
    ) \
/**/

BOOST_PP_SEQ_FOR_EACH(PSTADE_def_pred, ~, PSTADE_ctypes)

#undef PSTADE_def_pred
#undef PSTADE_ctypes


// to_upper/to_lower
//

namespace to_upper_lower_detail {

    struct with_apply
    {
        template< class Myself, class CharT, class Locale = void >
        struct apply :
            pass_by_value<CharT>
        { };
    };

    struct baby_up : with_apply
    {
        template< class Result, class CharT >
        Result call(CharT ch, std::locale const& loc)
        {
            return std::toupper(ch, loc);
        }

        template< class Result, class CharT >
        Result call(CharT ch)
        {
            return std::toupper(ch, std::locale());
        }
    };

    struct baby_lo : with_apply
    {
        template< class Result, class CharT >
        Result call(CharT ch, std::locale const& loc)
        {
            return std::tolower(ch, loc);
        }

        template< class Result, class CharT >
        Result call(CharT ch)
        {
            return std::tolower(ch, std::locale());
        }
    };

} // namespace to_upper_lower_detail

PSTADE_ADL_BARRIER(locale) { // for Boost

PSTADE_EGG_FUNCTION(to_upper, to_upper_lower_detail::baby_up)
PSTADE_EGG_FUNCTION(to_lower, to_upper_lower_detail::baby_lo)

} // ADL barrier


} // namespace pstade


#endif
