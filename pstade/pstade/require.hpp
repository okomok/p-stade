#ifndef PSTADE_REQUIRE_HPP
#define PSTADE_REQUIRE_HPP


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
#include <stdexcept> // runtime_error
#include <string>
#include <boost/current_function.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/throw_exception.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/oven/range_adaptor.hpp>


#define PSTADE_REQUIRE(Expr) \
    PSTADE_REQUIRE_MESSAGE(Expr, "")
/**/


#define PSTADE_REQUIRE_MESSAGE(Expr, Msg) \
    pstade::require( \
        Expr, \
        pstade::require_detail::make_info(BOOST_PP_STRINGIZE(Expr), __FILE__, __LINE__, BOOST_CURRENT_FUNCTION, Msg) \
    ) \
/**/


namespace pstade {


struct require_error :
    std::runtime_error
{
    explicit require_error(std::string what) :
        std::runtime_error(what)
    { }
};


namespace require_detail {


    inline
    void throw_exception(std::string info)
    {
        require_error err("<require>" + info + "</require>");
        boost::throw_exception(err);
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
        template< class T, class StringT = void >
        struct result :
            boost::add_reference<T>
        { };

        template< class Result, class T >
        Result call(T& x)
        {
            if (!x)
                require_detail::throw_exception("");

            return x;
        }

        template< class Result, class T, class StringT >
        Result call(T& x, StringT& info)
        {
            if (!x)
                require_detail::throw_exception(info);

            return x;
        }
    };


} // namespace require_detail


PSTADE_EGG_FUNCTION(require, require_detail::baby)
PSTADE_OVEN_RANGE_ADAPTOR(required, require_detail::baby)


} // namespace pstade


#endif
