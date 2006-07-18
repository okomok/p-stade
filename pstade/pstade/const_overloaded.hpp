#ifndef PSTADE_CONST_OVERLOADED_HPP
#define PSTADE_CONST_OVERLOADED_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Usage:
//
// template< class T >
// typename const_overloaded<T, void>::type foo(T&);
//
// template< class T >
// void foo(const T&);


// Note:
//
// GCC3.4.4 cannot order overloadings of non-const-reference and const-reference
// if it has explicit template arguments.
// So disable the non-const-reference overloading in the case of const-reference.
// http://groups.google.com/group/comp.lang.c++.moderated/browse_frm/thread/2dc6189c2eec0fd5/


#include <boost/config.hpp> // BOOST_NO_SFINAE
#include <boost/type_traits/is_const.hpp>
#include <boost/utility/enable_if.hpp> // disable_if, lazy_disable_if


namespace pstade {


#if !defined(BOOST_NO_SFINAE)


    template< class T, class Result >
    struct const_overloaded :
        boost::disable_if< boost::is_const<T>, Result >
    { };


    template< class T, class Result >
    struct const_overloaded_eval :
        boost::lazy_disable_if< boost::is_const<T>, Result >
    { };


#else // God bless you.


    template< class T, class Result >
    struct const_overloaded
    {
        typedef Result type;
    };


    template< class T, class Result >
    struct const_overloaded_eval
    {
        typedef typename Result::type type;
    };


#endif // !defined(BOOST_NO_SFINAE)


} // namespace pstade


#endif
