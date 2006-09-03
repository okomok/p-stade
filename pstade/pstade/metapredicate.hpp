#ifndef PSTADE_METAPREDICATE_HPP
#define PSTADE_METAPREDICATE_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Idea from: 'boost_foreach_is_lightweight_proxy'
//
// at <boost/foreach.hpp>


#include <boost/mpl/empty_base.hpp>
#include <boost/preprocessor/cat.hpp>
#include <pstade/oui_non.hpp>
#include <pstade/overload.hpp>
#include <pstade/remove_cvr.hpp>


#define PSTADE_METAPREDICATE(Name, Prefix) \
    PSTADE_METAPREDICATE_adl_primary(Name, Prefix) \
    PSTADE_METAPREDICATE_meta_primary(Name, Prefix) \
    PSTADE_METAPREDICATE_meta(Name) \
    PSTADE_METAPREDICATE_as(Name, Prefix) \
/**/


    #define PSTADE_METAPREDICATE_adl_primary(Name, Prefix) \
        template< class T > \
        pstade::non PSTADE_METAPREDICATE_cat3(Prefix, _is_, Name)(T *&, pstade::overload<>); \
    /**/


    #define PSTADE_METAPREDICATE_meta_primary(Name, Prefix) \
        template< class T, class = void > \
        struct PSTADE_METAPREDICATE_cat3(is_, Name, _impl) : \
            PSTADE_IS_OUI( \
                PSTADE_METAPREDICATE_cat3(Prefix, _is_, Name)( pstade::make_ptr_ref<T>(), pstade::overload<>() ) \
            ) \
        { }; \
    /**/


    #define PSTADE_METAPREDICATE_meta(Name) \
        template< class T > \
        struct BOOST_PP_CAT(is_, Name) : \
            PSTADE_METAPREDICATE_cat3(is_, Name, _impl)< \
                typename pstade::remove_cvr<T>::type \
            > \
        { }; \
    /**/


    #define PSTADE_METAPREDICATE_as(Name, Prefix) \
    template< class T, class Base = boost::mpl::empty_base > \
    struct BOOST_PP_CAT(as_, Name) \
    { \
        friend /* needs definition to suppress GCC waring. */ \
        pstade::oui PSTADE_METAPREDICATE_cat3(Prefix, _is_, Name)(T *&, pstade::overload<>) \
        { \
            return pstade::oui(); \
        } \
    }; \
    /**/


    #define PSTADE_METAPREDICATE_cat3(A, B, C) \
        BOOST_PP_CAT(A, BOOST_PP_CAT(B, C)) \
    /**/


#endif
