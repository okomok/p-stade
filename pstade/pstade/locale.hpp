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
#include <pstade/pass_by.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/singleton.hpp>


namespace pstade {


    // is_space etc.
    //

    #define PSTADE_ctypes \
        (space)(print)(cntrl)(upper)(lower)(alpha)(digit)(punct)(xdigit)(alnum)(graph) \
    /**/

    #define PSTADE_def_pred(R, _, CType) \
        struct PSTADE_PP_CAT3(op_, is_, CType) \
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
        PSTADE_SINGLETON_CONST( BOOST_PP_CAT(is_, CType), PSTADE_PP_CAT3(op_, is_, CType) ) \
    /**/

    BOOST_PP_SEQ_FOR_EACH(PSTADE_def_pred, ~, PSTADE_ctypes)

    #undef PSTADE_def_pred
    #undef PSTADE_ctypes


    // to_upper/to_lower
    //

    namespace to_upper_lower_detail {

        struct with_result
        {
            template< class Signature >
            struct result;

            template< class _, class CharT, class Locale >
            struct result<_(CharT, Locale)> :
                pass_by_value<CharT>
            { };

            template< class _, class CharT >
            struct result<_(CharT)> :
                pass_by_value<CharT>
            { };
        };

    } // namespace to_upper_lower_detail

    
    struct op_to_upper : to_upper_lower_detail::with_result
    {
        template< class CharT >
        typename result<int(CharT, int)>::type operator()(CharT ch, std::locale const& loc) const
        {
            return std::toupper(ch, loc);
        }

        template< class CharT >
        typename result<int(CharT)>::type operator()(CharT ch) const
        {
            return std::toupper(ch, std::locale());
        }
    };

    struct op_to_lower : to_upper_lower_detail::with_result
    {
        template< class CharT >
        typename result<int(CharT, int)>::type operator()(CharT ch, std::locale const& loc) const
        {
            return std::tolower(ch, loc);
        }

        template< class CharT >
        typename result<int(CharT)>::type operator()(CharT ch) const
        {
            return std::tolower(ch, std::locale());
        }
    };


    PSTADE_ADL_BARRIER(locale) { // for Boost

    PSTADE_SINGLETON_CONST(to_upper, op_to_upper)
    PSTADE_SINGLETON_CONST(to_lower, op_to_lower)

    } // ADL barrier


} // namespace pstade


#endif
