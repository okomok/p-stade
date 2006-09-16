#ifndef PSTADE_EGG_DETAIL_DISABLE_IF_SAME_HPP
#define PSTADE_EGG_DETAIL_DISABLE_IF_SAME_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// A unary template constructor can win the overloading race against copy-constructor.
// So disable it.
// http://groups.google.com/group/comp.lang.c++.moderated/browse_frm/thread/eca7b43d751008cd/


#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>


namespace pstade { namespace egg { namespace detail {


template< class X, class Y >
struct disable_if_same :
    boost::disable_if< boost::is_same<X, Y> >
{ };


} } } // namespace pstade::egg::detail


#endif
