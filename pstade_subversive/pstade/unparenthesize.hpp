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


// What:
//
// Makes decayed-T with cv-qualifier from
// PSTADE_UNPARENTHESIZE((T)cv-qualifier), where cv-qualifier is optional.


#define PSTADE_UNPARENTHESIZE(TQ) \
    pstade::unparenthesize_detail::aux< void (::pstade::unparenthesize_detail::klass::*) TQ >::type \
/**/

#define PSTADE_UNPARENTHESIZE_TPL \
    typename PSTADE_UNPARENTHESIZE \
/**/


namespace pstade { namespace unparenthesize_detail {


    struct klass;


    template< class Signature >
    struct aux;


    template< class T >
    struct aux< void (klass::*)(T) >
    {
        typedef T type;
    };

    template< >
    struct aux< void (klass::*)(void) >
    {
        typedef void type;
    };

    template< class T >
    struct aux< void (klass::*)(T) const >
    {
        typedef T const type;
    };

    template< class T >
    struct aux< void (klass::*)(T) volatile >
    {
        typedef T volatile type;
    };

    template< class T >
    struct aux< void (klass::*)(T) const volatile >
    {
        typedef T const volatile type;
    };


} } // namespace pstade::unparenthesize_detail


#endif
