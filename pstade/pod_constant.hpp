#ifndef PSTADE_POD_CONSTANT_HPP
#define PSTADE_POD_CONSTANT_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/in_unnamed.hpp>
#include <pstade/unparenthesize.hpp>


#define PSTADE_POD_CONSTANT(O, T) \
    PSTADE_POD_CONSTANT_aux(O, PSTADE_UNPARENTHESIZE(T)) \
/**/

    #define PSTADE_POD_CONSTANT_aux(O, T) \
        namespace { \
            PSTADE_IN_UNNAMED T const& O \
                = pstade::pod_constant_detail::static_const< T >::value; \
        } \
    /**/


namespace pstade { namespace pod_constant_detail {


    template<class T>
    struct static_const
    {
        static T const value;
    };


    // Brace ensures static-initialization (8.5.14).

    template<class T>
    T const static_const<T>::value = { };


} } // namespace pstade::pod_constant_detail


#endif
