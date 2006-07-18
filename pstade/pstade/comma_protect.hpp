#ifndef PSTADE_COMMA_PROTECT_HPP
#define PSTADE_COMMA_PROTECT_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://d.hatena.ne.jp/Cryolite/20050326
// http://www.kangaroologic.com/interfaces/libs/interfaces/doc/macros/protect.html


// See: <boost/sequence/detail/comma_protect.hpp>
//
// Copyright David Abrahams 2005. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// 'PSTADE_COMMA_PROTECT((T const))' is not supported.
// Instead, use 'PSTADE_COMMA_PROTECT((T)) const'.


#define PSTADE_COMMA_PROTECT(T) \
    pstade::comma_protect_detail::unwrap<void(T)>::type \
/**/


#define PSTADE_COMMA_PROTECT_D(T) \
    typename pstade::comma_protect_detail::unwrap<void(T)>::type \
/**/


#define PSTADE_COMMA_PROTECT_EVAL(T) \
    pstade::comma_protect_detail::unwrap_eval<void(T)>::type \
/**/


#define PSTADE_COMMA_PROTECT_EVAL_D(T) \
    typename pstade::comma_protect_detail::unwrap_eval<void(T)>::type \
/**/


namespace pstade { namespace comma_protect_detail {


    template< class T >
    struct unwrap;

    template< class T >
    struct unwrap<void(T)>
    {
        typedef T type;
    };


    template< class T >
    struct unwrap_eval;

    template< class T >
    struct unwrap_eval<void(T)>
    {
        typedef typename T::type type;
    };


} } // namespace pstade::comma_protect_detail


#endif
