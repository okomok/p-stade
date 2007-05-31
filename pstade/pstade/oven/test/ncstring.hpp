#ifndef PSTADE_OVEN_TEST_NCSTRING_HPP
#define PSTADE_OVEN_TEST_NCSTRING_HPP


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


struct ncstring :
    std::string
{
private:
    typedef std::string super_t;

public:
    explicit ncstring()
    { }

    template< class Iterator >
    explicit ncstring(Iterator first, Iterator last) :
        super_t(first, last)
    { }

    template< class Range >
    explicit ncstring(Range const& rng) :
        super_t(boost::begin(rng), boost::end(rng))
    { }

    explicit ncstring(char const* s) :
        super_t(s)
    { }

private:
    ncstring(ncstring const&);
    ncstring& operator=(ncstring const&);
};


} } } // namespace pstade::oven::test


#endif
