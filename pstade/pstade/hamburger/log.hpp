#ifndef PSTADE_HAMBURGER_LOG_HPP
#define PSTADE_HAMBURGER_LOG_HPP


// PStade.Hamburger
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/constant.hpp>
#include <pstade/instance.hpp>
#include <pstade/napkin/dout.hpp>
#include <pstade/napkin/lock_ostream.hpp>
#include <pstade/statement.hpp>


namespace pstade { namespace hamburger {


    PSTADE_INSTANCE((napkin::lock_ostream), log, (napkin::dout))


    template< class StringOutputable >
    void log_reset(StringOutputable& out)
    {
        log.reset(out);
        log << "<hamburger-log>";
    }


    namespace log_detail {


        struct init
        {
            init()
            {
                PSTADE_INSTANCE_OF(log) << "<hamburger-log>";
            }

            ~init()
            {
                PSTADE_INSTANCE_OF(log) << "</hamburger-log>";
            }
        };


        PSTADE_CONSTANT(i, (init))


    } // namespace log_detail


} } // namespace pstade::hamburger


#endif
