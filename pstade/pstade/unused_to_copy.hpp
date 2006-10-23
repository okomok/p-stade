#ifndef PSTADE_USED_TO_COPY_HPP
#define PSTADE_USED_TO_COPY_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>


namespace pstade {


// give way to implicitly-declared copy-constructor.
template< class T, class A >
struct unused_to_copy :
    boost::disable_if< boost::is_same<T, A>, void * >
{ };


template< class T, class A >
struct unused_to_copy_assign :
    boost::disable_if< boost::is_same<T, A>, T& >
{ };


} // namespace pstade


#endif
