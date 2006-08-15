#ifndef PSTADE_EGG_IS_PIPE_HPP
#define PSTADE_EGG_IS_PIPE_HPP


// PStade.Egg
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include "./detail/pipe_base.hpp"


namespace pstade { namespace egg {


template< class T, class = void >
struct is_pipe_impl :
    boost::is_base_of<detail::pipe_base, T>
{ };


template< class T >
struct is_pipe :
    is_pipe_impl<
        typename boost::remove_cv<T>::type
    >
{ };


} } // namespace pstade::egg


#endif
