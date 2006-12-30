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
#include <pstade/callable2.hpp>
#include <pstade/constant.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/preprocessor.hpp>


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
        PSTADE_CONSTANT( BOOST_PP_CAT(is_, CType), (PSTADE_PP_CAT3(op_, is_, CType)) ) \
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

    } // namespace to_upper_lower_detail

    
    struct op_to_upper :
        to_upper_lower_detail::with_apply,
        callable2<op_to_upper>
    {
        template< class Result, class CharT >
        Result call(CharT ch, std::locale const& loc) const
        {
            return std::toupper(ch, loc);
        }

        template< class Result, class CharT >
        Result call(CharT ch) const
        {
            return std::toupper(ch, std::locale());
        }
    };

    struct op_to_lower :
        to_upper_lower_detail::with_apply,
        callable2<op_to_lower>
    {
        template< class Result, class CharT >
        Result call(CharT ch, std::locale const& loc) const
        {
            return std::tolower(ch, loc);
        }

        template< class Result, class CharT >
        Result call(CharT ch) const
        {
            return std::tolower(ch, std::locale());
        }
    };


    PSTADE_ADL_BARRIER(locale) { // for Boost

    PSTADE_CONSTANT(to_upper, (op_to_upper))
    PSTADE_CONSTANT(to_lower, (op_to_lower))

    } // ADL barrier


} // namespace pstade


#endif
