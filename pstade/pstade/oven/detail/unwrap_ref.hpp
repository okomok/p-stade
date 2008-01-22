#ifndef PSTADE_OVEN_DETAIL_UNWRAP_REF_HPP
#define PSTADE_OVEN_DETAIL_UNWRAP_REF_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Copyright 2006 Cryolite.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See also `egg::deduce<..., egg::as_wrappred_ref>`.


#include <boost/mpl/eval_if.hpp>
#include <boost/ref.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/remove_cv.hpp>


namespace pstade { namespace oven { namespace detail {


template<class X>
struct unwrap_ref :
    boost::mpl::eval_if< boost::is_reference_wrapper<X>,
        boost::add_reference<typename boost::unwrap_reference<X>::type>,
        boost::remove_cv<X> // not reference.
      >
{ };


} } } // namespace pstade::oven::detail


#endif
