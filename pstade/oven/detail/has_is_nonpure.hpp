#ifndef PSTADE_OVEN_DETAIL_HAS_IS_NONPURE_HPP
#define PSTADE_OVEN_DETAIL_HAS_IS_NONPURE_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_function.hpp>
#include <pstade/has_xxx.hpp>


namespace pstade { namespace oven { namespace detail {


namespace aux {
    PSTADE_HAS_TYPE(is_nonpure)
}

template< class X >
struct has_is_nonpure :
    boost::mpl::and_<
        boost::mpl::not_< boost::is_function<X> >,
        aux::has_is_nonpure<X>
    >
{ };


} } } // namespace pstade::oven::detail


#endif
