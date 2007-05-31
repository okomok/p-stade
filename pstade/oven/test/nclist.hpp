#ifndef PSTADE_OVEN_TEST_NCLIST_HPP
#define PSTADE_OVEN_TEST_NCLIST_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "../detail/prelude.hpp"
#include <list>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>


namespace pstade { namespace oven { namespace test {


template< class T >
struct nclist :
    std::list<T>
{
private:
    typedef std::list<T> super_t;

public:
    explicit nclist()
    { }

    template< class Iterator >
    explicit nclist(Iterator first, Iterator last) :
        super_t(first, last)
    { }

    template< class Range >
    explicit nclist(Range const& rng) :
        super_t(boost::begin(rng), boost::end(rng))
    { }

private:
    nclist(nclist const&);
    nclist& operator=(nclist const&);
};


} } } // namespace pstade::oven::test


#endif
