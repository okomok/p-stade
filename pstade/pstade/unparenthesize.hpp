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



namespace pstade {


    namespace unparenthesize_detail {

        struct klass;

    }


    template< class Signature >
    struct unparenthesize;


    template< class T >
    struct unparenthesize<void (unparenthesize_detail::klass::*)(T)>
    {
        typedef T type;
    };

    template< class T >
    struct unparenthesize<void (unparenthesize_detail::klass::*)(T) const>
    {
        typedef T const type;
    };

    template< class T >
    struct unparenthesize<void (unparenthesize_detail::klass::*)(T) volatile>
    {
        typedef T volatile type;
    };

    template< class T >
    struct unparenthesize<void (unparenthesize_detail::klass::*)(T) const volatile>
    {
        typedef T const volatile type;
    };

    template< >
    struct unparenthesize<void (unparenthesize_detail::klass::*)(void)>
    {
        typedef void type;
    };


} // namespace pstade


#define PSTADE_UNPARENTHESIZE(TQ) \
    pstade::unparenthesize< void (pstade::unparenthesize_detail::klass::*) TQ >::type \
/**/


#endif
