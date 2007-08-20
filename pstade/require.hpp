#ifndef PSTADE_REQUIRE_HPP
#define PSTADE_REQUIRE_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: <boost/test/minimal.hpp>
//
//  (C) Copyright Gennadiy Rozental 2002-2005.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)


#include <stdexcept> // runtime_error
#include <string>
#include <boost/current_function.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/throw_exception.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/what.hpp>


#define PSTADE_REQUIRE(Expr) \
    PSTADE_REQUIRE_MESSAGE(Expr, "")
/**/


#if !defined(NDEBUG) || defined(PSTADE_REQUIRE_DEBUG)

    #define PSTADE_REQUIRE_MESSAGE(Expr, Msg) \
        ::pstade::require( \
            Expr, \
            ::pstade::require_detail::make_info(BOOST_PP_STRINGIZE(Expr), __FILE__, __LINE__, BOOST_CURRENT_FUNCTION, Msg) \
        ) \
    /**/

#else

    #define PSTADE_REQUIRE_MESSAGE(Expr, Msg) \
        ::pstade::require( \
            Expr, \
            ::pstade::require_detail::make_info("", __FILE__, __LINE__, "", Msg) \
        ) \
    /**/

#endif


namespace pstade {


    struct require_error :
        std::runtime_error
    {
        explicit require_error(std::string const& what) :
            std::runtime_error(what)
        { }
    };


    namespace require_detail {


        inline
        void throw_error(std::string info)
        {
            require_error err(pstade::what("require", info));
            boost::throw_exception(err);
        }


        inline
        std::string make_info(char const *expr, char const *file, int line, char const *func, char const *msg)
        {
            // avoid stringstream and joint_range for code size
            //
            return 
                pstade::what("file",        file) +
                pstade::what("line",        line) +
                pstade::what("expression",  expr) +
                pstade::what("function",    func) +
                pstade::what("message",     msg)
            ;
        }


        struct baby
        {
            template< class Myself, class T, class StringT = void >
            struct apply :
                boost::add_reference<T>
            { };

            template< class Result, class T >
            Result call(T& x) const
            {
                if (!x)
                    require_detail::throw_error("");

                return x;
            }

            template< class Result, class T, class StringT >
            Result call(T& x, StringT& info) const
            {
                if (!x)
                    require_detail::throw_error(info);

                return x;
            }
        };


    } // namespace require_detail


    typedef egg::function<require_detail::baby> op_require;
    PSTADE_POD_CONSTANT((op_require), require) = {{}};

    PSTADE_POD_CONSTANT((egg::result_of_pipable<op_require>::type), required)
        = PSTADE_EGG_PIPABLE_L {{}} PSTADE_EGG_PIPABLE_R;


} // namespace pstade


#endif
