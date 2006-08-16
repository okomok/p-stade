#ifndef PSTADE_EGG_IS_PIPE_HPP
#define PSTADE_EGG_IS_PIPE_HPP


// PStade.Egg
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: 'boost_foreach_is_lightweight_proxy'
//
// at <boost/foreach.hpp>


#include <boost/mpl/empty_base.hpp>
#include <pstade/oui_non.hpp>
#include <pstade/overload.hpp>
#include <pstade/remove_cvr.hpp>


namespace pstade { namespace egg {


template< class T >
non pstade_egg_is_pipe(T *&, overload<>);


template< class T, class = void >
struct is_pipe_impl :
    PSTADE_IS_OUI(
        pstade_egg_is_pipe( pstade::make_ptr_ref<T>(), overload<>() )
    )
{ };


template< class T >
struct is_pipe :
    is_pipe_impl<
        typename remove_cvr<T>::type
    >
{ };


template< class T, class Base = boost::mpl::empty_base >
struct as_pipe
{
    friend // definition needed for suppressing GCC waring.
    oui pstade_egg_is_pipe(T *&, overload<>)
    {
        return oui();
    }
    
};


} } // namespace pstade::egg


#endif
