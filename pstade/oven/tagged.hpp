#ifndef PSTADE_OVEN_TAGGED_HPP
#define PSTADE_OVEN_TAGGED_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/result_of_identities.hpp"


namespace pstade { namespace oven {


template< class Range, class Tag >
struct result_of_tagged :
    detail::result_of_identities<Range, boost::use_default, boost::use_default, Tag>
{ };


template< class Range >
struct tag_of
{
    typedef typename Range::iterator::tag_type type;
};


} } // namespace pstade::oven


#endif
