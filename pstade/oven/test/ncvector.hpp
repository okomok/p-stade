#ifndef PSTADE_OVEN_TEST_NCVECTOR_HPP
#define PSTADE_OVEN_TEST_NCVECTOR_HPP


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
struct ncvector :
    std::vector<T>
{
private:
    typedef std::vector<T> super_t;

public:
    explicit ncvector()
    { }

    template< class Iterator >
    explicit ncvector(Iterator first, Iterator last) :
        super_t(first, last)
    { }

    template< class Range >
    explicit ncvector(Range const& rng) :
        super_t(boost::begin(rng), boost::end(rng))
    { }

private:
    ncvector(ncvector const&);
    ncvector& operator=(ncvector const&);
};


} } } // namespace pstade::oven::test


#endif
