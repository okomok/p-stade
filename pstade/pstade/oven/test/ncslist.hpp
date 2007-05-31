#ifndef PSTADE_OVEN_TEST_NCSLIST_HPP
#define PSTADE_OVEN_TEST_NCSLIST_HPP


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
struct ncslist :
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
    explicit ncslist()
    { }

    template< class Iterator >
    explicit ncslist(Iterator first, Iterator last) :
        super_t(first, last)
    { }

    template< class Range >
    explicit ncslist(Range const& rng) :
        super_t(boost::begin(rng), boost::end(rng))
    { }

private:
    ncslist(ncslist const&);
    ncslist& operator=(ncslist const&);
};


} } } // namespace pstade::oven::test


#endif
