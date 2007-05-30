#ifndef PSTADE_OVEN_TEST_NC_LIST_HPP
#define PSTADE_OVEN_TEST_NC_LIST_HPP


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
struct nc_list :
    std::list<T>
{
private:
    typedef std::list<T> super_t;

public:
    template< class Iterator >
    explicit nc_list(Iterator first, Iterator last) :
        super_t(first, last)
    { }

    template< class Range >
    explicit nc_list(Range const& rng) :
        super_t(boost::begin(rng), boost::end(rng))
    { }

private:
    nc_list(nc_list const&);
    nc_list& operator=(nc_list const&);
};


} } } // namespace pstade::oven::test


#endif
