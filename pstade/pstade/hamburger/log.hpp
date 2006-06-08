#ifndef PSTADE_HAMBURGER_LOG_HPP
#define PSTADE_HAMBURGER_LOG_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/instance.hpp>
#include <pstade/napkin/dout.hpp>
#include <pstade/napkin/lock_ostream.hpp>
#include <pstade/statement.hpp>


namespace pstade { namespace hamburger {


PSTADE_INSTANCE(napkin::lock_ostream, log, value)


namespace log_detail {


    PSTADE_STATEMENT(Init,
        log_().reset(napkin::dout);
        log_() << "<pstade-hamburger-log>";
    )


} // namespace log_detail


} } // namespace pstade::hamburger


#endif
