#ifndef PSTADE_OVEN_DETAIL_WCHAR_FROM_MB_HPP
#define PSTADE_OVEN_DETAIL_WCHAR_FROM_MB_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// The convertibility of the original is over-optimistic.


#include <boost/archive/iterators/wchar_from_mb.hpp>


namespace pstade { namespace oven { namespace detail {


template< class Iterator >
struct wchar_from_mb;


template< class Iterator >
struct wchar_from_mb_super
{
    typedef
        boost::iterator_adaptor<
            wchar_from_mb<Iterator>,
            boost::archive::iterators::wchar_from_mb<Iterator>
        >
    type;
};


template< class Iterator >
struct wchar_from_mb :
    wchar_from_mb_super<Iterator>::type
{
private:
    typedef typename wchar_from_mb_super<Iterator>::type super_t;

public:
    explicit wchar_from_mb(Iterator it) :
        super_t(it)
    { }

    template< class I >
    wchar_from_mb(wchar_from_mb<I> const& other,
        typename boost::enable_if_convertible<I, Iterator>::type * = 0
    ) :
        super_t(other.base())
    { }

private:
friend class boost::iterator_core_access;
    // as is.
};


} } } // namespace pstade::oven::detail


#endif
