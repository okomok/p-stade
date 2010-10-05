#ifndef PSTADE_IS_NULLARY_CALLABLE_HPP
#define PSTADE_IS_NULLARY_CALLABLE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2010.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: http://cpplover.blogspot.com/2010/03/decltypesfinae.html


#include <boost/mpl/bool.hpp>
#include <boost/config.hpp>


#if (BOOST_VERSION < 103900 && defined(BOOST_HAS_DECLTYPE)) || (BOOST_VERSION >= 103900 && !defined(BOOST_NO_DECLTYPE))
    #include <utility>
    #include <boost/mpl/identity.hpp>
    #define PSTADE_HAS_IS_NULLARY_CALLABLE
#endif


#if defined(PSTADE_HAS_IS_NULLARY_CALLABLE)
namespace is_nullary_callable_detail {

    template < typename K >
    K && value();

    template < typename T >
    struct impl
    {
    private :
        template < typename U >
        static auto check(U&& x) -> decltype( x(), std::true_type() ) ;
        static std::false_type check(...) ;

    public :
        static bool const value = boost::mpl::identity<decltype( check( value<T>() ) )>::type::value ;
    };

}
#endif

template<class T>
struct is_nullary_callable :
#if defined(PSTADE_HAS_IS_NULLARY_CALLABLE)
    boost::mpl::bool_<is_nullary_callable_detail::impl<T>::value>
#else
    boost::mpl::bool_<true>
#endif
{};


#endif
