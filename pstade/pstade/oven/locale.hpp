#ifndef PSTADE_OVEN_LOCALE_HPP
#define PSTADE_OVEN_LOCALE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Pending...
//


#include <locale>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/egg/by_value.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/instance.hpp>


namespace pstade { namespace oven {


    #define PSTADE_OVEN_ctypes \
        (space)(print)(cntrl)(upper)(lower)(alpha)(digit)(punct)(xdigit)(alnum)(graph) \
    /**/

    #define PSTADE_OVEN_def_pred(R, _, CType) \
        struct BOOST_PP_CAT(BOOST_PP_CAT(is_, CType), _fun) \
        { \
            typedef bool result_type; \
            \
            template< class CharT > \
            bool operator()(CharT ch, std::locale const& loc) const \
            { \
                return std:: BOOST_PP_CAT(is, CType)(ch, loc); \
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

BOOST_PP_SEQ_FOR_EACH(PSTADE_OVEN_def_pred, ~, PSTADE_OVEN_ctypes)

    #undef PSTADE_OVEN_def_pred
    #undef PSTADE_OVEN_ctypes


namespace locale_detail {


    struct to_upper_gift
    {
        template< class Unused, class CharT, class Locale = void >
        struct result :
            egg::by_value<CharT>
        { };
    };


    struct baby_to_upper : to_upper_gift
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


    struct baby_to_lower : to_upper_gift
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


} // namespace locale_detail


PSTADE_ADL_BARRIER(locale) { // for Boost

PSTADE_EGG_FUNCTION(to_upper, locale_detail::baby_to_upper)
PSTADE_EGG_FUNCTION(to_lower, locale_detail::baby_to_lower)

} // ADL barrier


} } // namespace pstade::oven


#endif
