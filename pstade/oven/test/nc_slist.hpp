#ifndef PSTADE_OVEN_TEST_NC_SLIST_HPP
#define PSTADE_OVEN_TEST_NC_SLIST_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "../detail/prelude.hpp"
#include <boost/config.hpp>
#if defined(BOOST_HAS_SLIST)
    #include BOOST_SLIST_HEADER
#else
    #include <list>
#endif
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>


namespace pstade { namespace oven { namespace test {


template< class T >
struct nc_slist :
#if defined(BOOST_HAS_SLIST)
    BOOST_STD_EXTENSION_NAMESPACE::slist<T>
#else
    std::list<T>
#endif
{
private:
#if defined(BOOST_HAS_SLIST)
    typedef BOOST_STD_EXTENSION_NAMESPACE::slist<T> super_t;
#else
    typedef std::list<T> super_t;
#endif

public:
    template< class Iterator >
    explicit nc_slist(Iterator first, Iterator last) :
        super_t(first, last)
    { }

    template< class Range >
    explicit nc_slist(Range const& rng) :
        super_t(boost::begin(rng), boost::end(rng))
    { }

private:
    nc_slist(nc_slist const&);
    nc_slist& operator=(nc_slist const&);
};


} } } // namespace pstade::oven::test


#endif
