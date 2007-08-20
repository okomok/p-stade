#ifndef PSTADE_CHECK_HPP
#define PSTADE_CHECK_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: <boost/test/minimal.hpp>
//
// (C) Copyright Gennadiy Rozental 2002-2005.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <sstream> // ostringstream
#include <string>
#include <boost/current_function.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/instance.hpp>
#include <pstade/napkin/ostream.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/what.hpp>


#if !defined(NDEBUG) || defined(PSTADE_CHECK_DEBUG)

    #define PSTADE_CHECK(Expr) \
        PSTADE_CHECK_MESSAGE(Expr, "") \
    /**/

    #define PSTADE_CHECK_MESSAGE(Expr, Msg) \
        ::pstade::check( \
            Expr, \
            ::pstade::check_detail::make_info(BOOST_PP_STRINGIZE(Expr), __FILE__, __LINE__, BOOST_CURRENT_FUNCTION, Msg) \
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


        PSTADE_INSTANCE((napkin::ostream), os, value)


        inline
        void report(std::string info)
        {
            os << pstade::what("check", info);
        }


        inline
        std::string make_info(char const *expr, char const *file, int line, char const *func, char const *msg)
        {
            std::ostringstream info;
            info <<
                pstade::what("file",        file) <<
                pstade::what("line",        line) <<
                pstade::what("expression",  expr) <<
                pstade::what("function",    func) <<
                pstade::what("message",     msg);

            return info.str();
        }


        struct baby
        {
            template< class Myself, class T, class StringT >
            struct apply
            {
                typedef T& type;
            };

            template< class Result, class T, class StringT >
            Result call(T& x, StringT& info) const
            {
                if (!x)
                    check_detail::report(info);

                return x;
            }
        };


    } // namespace check_detail


    typedef egg::function<check_detail::baby> op_check;
    PSTADE_POD_CONSTANT((op_check), check) = {{}};

    PSTADE_POD_CONSTANT((egg::result_of_pipable<op_check>::type), checked)
        = PSTADE_EGG_PIPABLE_L {{}} PSTADE_EGG_PIPABLE_R;


    template< class StringOutputable > inline
    void check_reset_ostream(StringOutputable& out)
    {
        check_detail::os.reset(out);
    }


} // namespace pstade


#endif
