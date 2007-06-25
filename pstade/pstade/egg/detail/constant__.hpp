#ifndef PSTADE_EGG_DETAIL_CONSTANT_HPP
#define PSTADE_EGG_DETAIL_CONSTANT_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/in_unnamed.hpp>
#include <pstade/unparenthesize.hpp>
#include "./config.hpp"


#define PSTADE_EGG_DETAIL_CONSTANT(O, T) \
    PSTADE_EGG_DETAIL_CONSTANT_aux(O, PSTADE_UNPARENTHESIZE(T)) \
/**/

    #define PSTADE_EGG_DETAIL_CONSTANT_aux(O, T) \
        namespace { \
            PSTADE_IN_UNNAMED T const& O \
                = pstade::egg::detail::constant< T >::value; \
        } \
    /**/


namespace pstade { namespace egg { namespace detail {


    template<class T>
    struct constant
    {
        static T const value;
    };


    // Brace ensures static-initialization (8.5.14).

    template<class T>
    T const constant<T>::value
#if !defined(PSTADE_EGG_RESULT_OF_CANT_WORK_WITH_TEMPLATE_POD)        
        = { };
#else
        = T();
#endif


} } } // namespace pstade::egg::detail


#endif
