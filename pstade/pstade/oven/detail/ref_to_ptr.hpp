#ifndef PSTADE_OVEN_DETAIL_REF_TO_PTR_HPP
#define PSTADE_OVEN_DETAIL_REF_TO_PTR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade { namespace oven { namespace detail {


template< class T >
struct ref_to_ptr;

template< class T >
struct ref_to_ptr< T& >
{
    typedef T *type;
};


} } } // namespace pstade::oven::detail


#endif
