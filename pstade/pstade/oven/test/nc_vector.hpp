#ifndef PSTADE_OVEN_TEST_NC_VECTOR_HPP
#define PSTADE_OVEN_TEST_NC_VECTOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "../detail/prelude.hpp"
#include <vector>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>


namespace pstade { namespace oven { namespace test {


template< class T >
struct nc_vector :
    std::vector<T>
{
private:
    typedef std::vector<T> super_t;

public:
    template< class Iterator >
    explicit nc_vector(Iterator first, Iterator last) :
        super_t(first, last)
    { }

    template< class Range >
    explicit nc_vector(Range const& rng) :
        super_t(boost::begin(rng), boost::end(rng))
    { }

private:
    nc_vector(nc_vector const&);
    nc_vector& operator=(nc_vector const&);
};


} } } // namespace pstade::oven::test


#endif
