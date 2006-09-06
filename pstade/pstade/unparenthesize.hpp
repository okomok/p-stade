#ifndef PSTADE_UNPARENTHESIZE_HPP
#define PSTADE_UNPARENTHESIZE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://d.hatena.ne.jp/Cryolite/20050326
// http://www.kangaroologic.com/interfaces/libs/interfaces/doc/macros/protect.html
// 'BOOST_PARAMETER_PARENTHESIZED_TYPE' with Boost v1.34


// Note:
//
// 'PSTADE_UNPARENTHESIZE((T const))' is not supported.
// Instead, use 'PSTADE_UNPARENTHESIZE((T)) const'.
// If 'T' is a dependent-name, add 'typename'.


#define PSTADE_UNPARENTHESIZE(Decayed) \
    pstade::unparenthesize_detail::aux<void(Decayed)>::type \
/**/


namespace pstade { namespace unparenthesize_detail {


    template< class Decayed >
    struct aux;

    template< class Decayed >
    struct aux<void(Decayed)>
    {
        typedef Decayed type;
    };


} } // namespace pstade::unparenthesize_detail


#endif
