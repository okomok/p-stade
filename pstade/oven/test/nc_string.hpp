#ifndef PSTADE_OVEN_TEST_NC_STRING_HPP
#define PSTADE_OVEN_TEST_NC_STRING_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "../detail/prelude.hpp"
#include <string>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>


namespace pstade { namespace oven { namespace test {


struct nc_string :
    std::string
{
private:
    typedef std::string super_t;

public:
    template< class Iterator >
    explicit nc_string(Iterator first, Iterator last) :
        super_t(first, last)
    { }

    template< class Range >
    explicit nc_string(Range const& rng) :
        super_t(boost::begin(rng), boost::end(rng))
    { }

    explicit nc_string(char const* s) :
        super_t(s)
    { }

private:
    nc_string(nc_string const&);
    nc_string& operator=(nc_string const&);
};


} } } // namespace pstade::oven::test


#endif
