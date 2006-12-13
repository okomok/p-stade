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
// PSTADE_UNPARENTHESIZE(cv-qualifier(T)), where cv-qualifier is optional.


#include <pstade/affect.hpp>


namespace pstade {


    namespace unparenthesize_detail {

        // suppress warning about meaningless cv-qualifier.
        struct non_built_in;

    }


    template< class Signature >
    struct unparenthesize;


    template< class Q, class T >
    struct unparenthesize<Q(T)> :
        affect_cv<Q, T>
    { };

    template< class Q >
    struct unparenthesize<Q(void)>
    {
        typedef void type;
    };


} // namespace pstade


#define PSTADE_UNPARENTHESIZE(QT) \
    pstade::unparenthesize< pstade::unparenthesize_detail::non_built_in QT >::type \
/**/


#endif
