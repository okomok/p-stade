#ifndef PSTADE_OVEN_DETAIL_ISTREAMBUF_ITERATOR_HPP
#define PSTADE_OVEN_DETAIL_ISTREAMBUF_ITERATOR_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Works around a bug that 'istreambuf_iterator<>::reference'
// of gcc and msvc STL implementation is wrongly a reference type.


#include <iterator> // istreambuf_iterator
#include <boost/iterator/iterator_adaptor.hpp>


namespace pstade { namespace oven { namespace detail {


template< class CharT, class Traits >
struct istreambuf_iterator;


template< class CharT, class Traits >
struct istreambuf_iterator_super
{
    typedef
        boost::iterator_adaptor<
            istreambuf_iterator<CharT, Traits>,
            std::istreambuf_iterator<CharT, Traits>,
            boost::use_default,
            boost::use_default,
            CharT // fix!
        >
    type;
};


template< class CharT, class Traits >
struct istreambuf_iterator :
    istreambuf_iterator_super<CharT, Traits>::type
{
private:
    typedef typename istreambuf_iterator_super<CharT, Traits>::type super_t;
    typedef typename super_t::base_type base_t;

public:
    typedef typename base_t::char_type      char_type;
    typedef typename base_t::traits_type    traits_type;
    typedef typename base_t::int_type       int_type;
    typedef typename base_t::streambuf_type streambuf_type;
    typedef typename base_t::istream_type   istream_type;

    explicit istreambuf_iterator(streambuf_type *p = 0) :
        super_t(base_t(p))
    { }

    explicit istreambuf_iterator(istream_type& is) :
        super_t(base_t(is))
    { }

private:
friend class boost::iterator_core_access;
    // as is.
};


} } } // namespace pstade::oven::detail


#endif
