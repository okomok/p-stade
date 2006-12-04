#ifndef PSTADE_SINGLETON_HPP
#define PSTADE_SINGLETON_HPP


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


namespace pstade {


    template< class T >
    struct singleton
    {
        static T instance;
    };


    template< class T >
    T singleton<T>::instance;


} // namespace pstade


// 'stdafx.h' sometimes needs 'static'.
//

#define PSTADE_SINGLETON(T, O) \
    namespace { \
        static T& O = pstade::singleton< T >::instance; \
    } \
/**/

#define PSTADE_SINGLETON_CONST(T, O) \
    namespace { \
        static T const& O = pstade::singleton< T >::instance; \
    } \
/**/


#endif
