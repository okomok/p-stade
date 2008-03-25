#ifndef BOOST_EGG_DETAIL_UNPAREN_HPP
#define BOOST_EGG_DETAIL_UNPAREN_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://d.hatena.ne.jp/Cryolite/20050326
// http://www.kangaroologic.com/interfaces/libs/interfaces/doc/macros/protect.html
// 'BOOST_PARAMETER_PARENTHESIZED_TYPE' with Boost v1.34


#include <boost/egg/detail/in_fun_spec.hpp>


#define BOOST_EGG_UNPAREN(T) boost::egg::details::unparen< void T >::type
#define BOOST_EGG_UNPAREN_TPL typename BOOST_EGG_UNPAREN


namespace boost { namespace egg { namespace details {


    template<class Signature>
    struct unparen;


    template<class T>
    struct unparen<void(T)>
    {
        typedef T type;
    };

    template< >
    struct unparen<void(BOOST_EGG_VOID_IN_FUN_SPEC)>
    {
        typedef void type;
    };


} } } // namespace boost::egg::details


#endif
