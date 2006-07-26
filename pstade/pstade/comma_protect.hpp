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
// 'PSTADE_COMMA_PROTECT((Decayed const))' is not supported.
// Instead, use 'PSTADE_COMMA_PROTECT((Decayed)) const'.


#define PSTADE_COMMA_PROTECT(Decayed) \
    pstade::comma_protect_detail::unwrap<void(Decayed)>::type \
/**/


#define PSTADE_COMMA_PROTECT_D(Decayed) \
    typename pstade::comma_protect_detail::unwrap<void(Decayed)>::type \
/**/


#define PSTADE_COMMA_PROTECT_EVAL(Decayed) \
    pstade::comma_protect_detail::unwrap_eval<void(Decayed)>::type \
/**/


#define PSTADE_COMMA_PROTECT_EVAL_D(Decayed) \
    typename pstade::comma_protect_detail::unwrap_eval<void(Decayed)>::type \
/**/


namespace pstade { namespace comma_protect_detail {


    template< class Decayed >
    struct unwrap;

    template< class Decayed >
    struct unwrap<void(Decayed)>
    {
        typedef Decayed type;
    };


    template< class Decayed >
    struct unwrap_eval;

    template< class Decayed >
    struct unwrap_eval<void(Decayed)>
    {
        typedef typename Decayed::type type;
    };


} } // namespace pstade::comma_protect_detail


#endif
