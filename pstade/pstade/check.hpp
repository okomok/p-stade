#ifndef PSTADE_CHECK_HPP
#define PSTADE_CHECK_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: <boost/test/minimal.hpp>
//
//  (C) Copyright Gennadiy Rozental 2002-2005.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)


#include <sstream>
#include <string>
#include <boost/current_function.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/instance.hpp>
#include <pstade/napkin/ostream.hpp>
#include <pstade/oven/range_adaptor.hpp>


#if !defined(NDEBUG) || defined(PSTADE_CHECK_DEBUG)

    #define PSTADE_CHECK(Expr) \
        PSTADE_CHECK_MESSAGE(Expr, "") \
    /**/

    #define PSTADE_CHECK_MESSAGE(Expr, Msg) \
        pstade::check( \
            Expr, \
            pstade::check_detail::make_info(BOOST_PP_STRINGIZE(Expr), __FILE__, __LINE__, BOOST_CURRENT_FUNCTION, Msg) \
        ) \
    /**/

#else

    #define PSTADE_CHECK(Expr) \
        (Expr) \
    /**/

    #define PSTADE_CHECK_MESSAGE(Expr, Msg) \
        (Expr) \
    /**/

#endif


namespace pstade {


namespace check_detail {


    PSTADE_INSTANCE(napkin::ostream, os, ~)


    inline
    void report(std::string info)
    {
        os << "<check>" << info << "</check>";
    }


    inline
    std::string make_info(const char *expr, const char *file, int line, const char *func, const char *msg)
    {
        std::stringstream info;
        info <<
            "<file>"        << file << "</file>"        <<
            "<line>"        << line << "</line>"        <<
            "<expression>"  << expr << "</expression>"  <<
            "<function>"    << func << "</function>"    <<
            "<message>"     << msg  << "</message>";

        return info.str();
    }


    struct baby
    {
        template< class T, class StringT >
        struct apply :
            boost::add_reference<T>
        { };

        template< class Result, class T, class StringT >
        Result call(T& x, StringT& info)
        {
            if (!x)
                check_detail::report(info);

            return x;
        }
    };


} // namespace check_detail


PSTADE_EGG_FUNCTION(check, check_detail::baby)
PSTADE_OVEN_RANGE_ADAPTOR(checked, check_detail::baby)


template< class StringOutputable > inline
void check_reset_ostream(StringOutputable& out)
{
    check_detail::os.reset(out);
}


} // namespace pstade


#endif
