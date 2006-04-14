#ifndef BOOST_MICROSOFT_DETAIL_RANGE_LIST_FUNCTIONS_HPP
#define BOOST_MICROSOFT_DETAIL_RANGE_LIST_FUNCTIONS_HPP


// Boost.Microsoft
//
// Copyright 2006 Shunsuke Sogame.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/detail/range/coll_value_type_fwd.hpp>
#include <boost/microsoft/detail/range/list_iterator.hpp>


namespace boost { namespace microsoft { namespace detail { namespace range {


template< class ListT, class SizeT >
struct list_metafunctions
{
    typedef typename coll_value<ListT>::type value_t;

    typedef list_iterator<ListT, value_t> mutable_iterator;
    typedef list_iterator<const ListT, const value_t> const_iterator;
    typedef SizeT size_type;
};


struct list_functions
{
    template< class Result, class ListT >
    Result begin(ListT& lst)
    {
        return Result(lst, lst.GetHeadPosition());
    }

    template< class Result, class ListT >
    Result end(ListT& lst)
    {
        return Result(lst, POSITION(NULL));
    }

    template< class Result, class ListT >
    Result size(ListT& lst)
    {
        return lst.GetCount();
    }
};


} } } } // namespace boost::microsoft::detail::range


#endif
