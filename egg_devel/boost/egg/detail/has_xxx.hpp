#ifndef BOOST_EGG_DETAIL_HAS_XXX_HPP
#define BOOST_EGG_DETAIL_HAS_XXX_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Workaround for:
//
// http://svn.boost.org/trac/boost/ticket/1317


#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/type_traits/detail/yes_no_type.hpp>
#include <boost/egg/detail/nullptr.hpp>


#define BOOST_EGG_HAS_XXX(Type) \
    BOOST_EGG_HAS_XXX_NAMED(BOOST_PP_CAT(has_, Type), Type) \
/**/

#define BOOST_EGG_HAS_XXX_NAMED(Name, Type) \
    BOOST_EGG_HAS_XXX_aux(Name, Type) \
/**/


    #define BOOST_EGG_HAS_XXX_aux(Name, Type) \
        namespace BOOST_EGG_HAS_XXX_aux_ns(Name) { \
            \
            template<class T> \
            boost::type_traits::yes_type test(typename T::Type (*)()); \
            \
            template<class T> \
            boost::type_traits::no_type  test(...); \
            \
        } \
        \
        template<class T> \
        struct Name : \
            boost::mpl::bool_< \
                sizeof( BOOST_EGG_HAS_XXX_aux_ns(Name)::test<T>(BOOST_EGG_NULLPTR) ) \
                    == sizeof(boost::type_traits::yes_type) \
            > \
        { }; \
    /**/

    #define BOOST_EGG_HAS_XXX_aux_ns(Name) \
        BOOST_PP_CAT(boost_egg_has_xxx_helper_, Name) \
    /**/


#endif
