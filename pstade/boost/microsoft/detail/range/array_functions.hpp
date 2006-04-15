#ifndef BOOST_MICROSOFT_DETAIL_RANGE_ARRAY_FUNCTIONS_HPP
#define BOOST_MICROSOFT_DETAIL_RANGE_ARRAY_FUNCTIONS_HPP


// Boost.Microsoft
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/detail/range/coll_value_type_fwd.hpp>


namespace boost { namespace microsoft { namespace detail { namespace range {


template< class ArrayT, class SizeT >
struct array_metafunctions
{
    typedef typename coll_value<ArrayT>::type value_t;

    typedef value_t *mutable_iterator;
    typedef const value_t *const_iterator;
    typedef SizeT size_type;
};


struct array_functions
{
    template< class Result, class ArrayT >
    Result begin(ArrayT& arr)
    {
        return arr.GetData();
    }

    template< class Result, class ArrayT >
    Result end(ArrayT& arr)
    {
        return arr.GetData() + arr.GetSize();
    }

    template< class Result, class ArrayT >
    Result size(ArrayT& arr)
    {
        return arr.GetSize();
    }
};


} } } } // namespace boost::microsoft::detail::range


#endif
