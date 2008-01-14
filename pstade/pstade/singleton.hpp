#ifndef PSTADE_SINGLETON_HPP
#define PSTADE_SINGLETON_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Port of: pod_singleton
//
// Copyright David Abrahams 2006. Distributed under the Boost 
// Software License, Version 1.0. (See accompanying 
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt) 


// Precondition:
//
// A program 'T x; int main() { }' is well-defined.


#include <pstade/in_unnamed.hpp>
#include <pstade/unparenthesize.hpp>


namespace pstade {


    template< class T >
    struct singleton
    {
        static T instance;
    };


    template< class T >
    T singleton<T>::instance;


} // namespace pstade


#define PSTADE_SINGLETON(O, T) \
    PSTADE_SINGLETON_aux(O, PSTADE_UNPARENTHESIZE(T)) \
/**/

    #define PSTADE_SINGLETON_aux(O, T) \
        namespace { \
            PSTADE_IN_UNNAMED T& O = ::pstade::singleton< T >::instance; \
        } \
    /**/


#define PSTADE_SINGLETON_FWD(O, T) \
    PSTADE_SINGLETON_FWD_aux(O, PSTADE_UNPARENTHESIZE(T)) \
/**/

    #define PSTADE_SINGLETON_FWD_aux(O, T) \
        namespace { \
            extern T& O; \
        } \
    /**/

#endif
