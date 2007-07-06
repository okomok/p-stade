#ifndef PSTADE_LOCALE_HPP
#define PSTADE_LOCALE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cctype>
#include <locale>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/preprocessor.hpp>


namespace pstade {


namespace locale {


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

    #undef  PSTADE_def_pred
    #undef  PSTADE_ctypes


    // to_lower/to_upper
    //

    struct op_to_lower :
        callable<op_to_lower>
    {
        template< class Myself, class CharT, class Locale = void >
        struct apply :
            pass_by_value<CharT>
        { };

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

    struct op_to_upper :
        callable<op_to_upper>
    {
        template< class Myself, class CharT, class Locale = void >
        struct apply :
            pass_by_value<CharT>
        { };

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

    PSTADE_ADL_BARRIER(to_lower_upper) { // for 'boost'
        PSTADE_CONSTANT(to_lower, (op_to_lower))
        PSTADE_CONSTANT(to_upper, (op_to_upper))
    }


    // iequal_to
    //

    struct op_iequal_to
    {
        typedef bool result_type;

        template< class CharT >
        bool operator()(CharT ch1, CharT ch2, std::locale const& loc) const
        {
            return std::tolower(ch1, loc) == std::tolower(ch2, loc);
        }

        template< class CharT >
        bool operator()(CharT ch1, CharT ch2) const
        {
            return (*this)(ch1, ch2, std::locale());
        }
    };

    PSTADE_CONSTANT(iequal_to, (op_iequal_to))


} // namespace locale


using namespace locale;


} // namespace pstade


#endif
