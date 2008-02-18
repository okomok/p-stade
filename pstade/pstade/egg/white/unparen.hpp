#ifndef BOOST_EGG_WHITE_UNPAREN_HPP
#define BOOST_EGG_WHITE_UNPAREN_HPP
#include "./detail/prefix.hpp"


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


// What:
//
// Makes decayed-T with cv-qualifier from
// BOOST_EGG_WHITE_UNPAREN((T)cv-qualifier), where cv-qualifier is optional.


#define BOOST_EGG_WHITE_UNPAREN(TQ) \
    boost::egg::white::unparen_detail::aux_<void(boost::egg::white::unparen_detail::klass::*) TQ>::type \
/**/

#define BOOST_EGG_WHITE_UNPAREN_TPL \
    typename BOOST_EGG_WHITE_UNPAREN \
/**/


namespace boost { namespace egg { namespace white {
    
    
    namespace unparen_detail {


        struct klass;


        template<class Signature>
        struct aux_;


        template<class T>
        struct aux_<void (klass::*)(T)>
        {
            typedef T type;
        };

        template< >
        struct aux_<void (klass::*)(void)>
        {
            typedef void type;
        };

        template<class T>
        struct aux_<void (klass::*)(T) const>
        {
            typedef T const type;
        };

        template<class T>
        struct aux_<void (klass::*)(T) volatile>
        {
            typedef T volatile type;
        };

        template<class T>
        struct aux_<void (klass::*)(T) const volatile>
        {
            typedef T const volatile type;
        };


    } // namespace unparen_detail


} } } // namespace boost::egg::white


#include "./detail/suffix.hpp"
#endif
