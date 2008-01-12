#ifndef PSTADE_WHAT_HPP
#define PSTADE_WHAT_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/egg/pstade/oven/as_c_str.hpp>
#include <boost/egg/pstade/oven/copy_range.hpp>
#include <boost/egg/pstade/pod_constant.hpp>


namespace pstade {


    struct T_what
    {
        typedef std::string result_type;

        template< class Range >
        std::string operator()(std::string const& tag, Range const& msg) const
        {
            return
                '<' + tag + '>' +
                    oven::copy_range<std::string>(msg) +
                "</" + tag + '>'
            ;
        }

        std::string operator()(std::string const& tag, char const *psz) const
        {
            return (*this)(tag, psz|oven::as_c_str);
        }

        std::string operator()(std::string const& tag, int n) const
        {
            return (*this)(tag, boost::lexical_cast<std::string>(n));
        }
    };


    PSTADE_POD_CONSTANT((T_what), what) = {};


} // namespace pstade


#endif
