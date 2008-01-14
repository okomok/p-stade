#ifndef PSTADE_DISABLE_IF_COPY_HPP
#define PSTADE_DISABLE_IF_COPY_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// A unary template constructor can win the overload-resolution race
// against copy-constructor. So disable it.
// http://groups.google.com/group/comp.lang.c++.moderated/browse_frm/thread/eca7b43d751008cd/


#include <boost/type_traits/is_same.hpp>
#include <pstade/enable_if.hpp>


namespace pstade {


    template< class Self, class From >
    struct disable_if_copy :
        disable_if<
            boost::is_same<Self, From>
        >
    { };


    template< class Self, class From >
    struct disable_if_copy_assign :
        disable_if<
            boost::is_same<Self, From>,
            Self&
        >
    { };


} // namespace pstade


#endif
