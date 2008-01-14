#ifndef PSTADE_METAPREDICATE_HPP
#define PSTADE_METAPREDICATE_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Defines 'Trait', 'is_Trait' and 'as_Trait'.


#include <boost/mpl/bool.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/type.hpp>
#include <boost/type_traits/detail/yes_no_type.hpp>
#include <boost/egg/pstade/radish/null_injector.hpp>


#define PSTADE_METAPREDICATE(Trait, Prefix) \
    struct Trait \
    { }; \
    \
    boost::type_traits::no_type BOOST_PP_CAT(Prefix, _is_)(Trait, ...); \
    \
    template< class T > \
    struct BOOST_PP_CAT(detail_is_, Trait) /* 'boost::type' needs this. */ \
    { \
        static bool const value = \
            sizeof(boost::type_traits::yes_type) \
            == sizeof( BOOST_PP_CAT(Prefix, _is_)(Trait(), boost::type<T>()) ); \
    }; \
    \
    template< class T > \
    struct BOOST_PP_CAT(is_, Trait) : \
        boost::mpl::bool_< BOOST_PP_CAT(detail_is_, Trait)<T>::value > \
    { }; \
    \
    template< class T, class Injector = ::pstade::radish::null_injector<T> > \
    struct BOOST_PP_CAT(as_, Trait) : Injector \
    { \
        friend /* needs definition to suppress GCC waring. */ \
        boost::type_traits::yes_type \
        BOOST_PP_CAT(Prefix, _is_)(Trait, boost::type<T>) \
        { \
            return boost::type_traits::yes_type(); \
        } \
    }; \
/**/


#endif
