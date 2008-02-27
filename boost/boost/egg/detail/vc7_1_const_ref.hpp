#ifndef BOOST_EGG_DETAIL_VC7_1_CONST_REF_HPP
#define BOOST_EGG_DETAIL_VC7_1_CONST_REF_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/detail/boost_workaround.hpp>


#if !BOOST_WORKAROUND(BOOST_MSVC, == 1310)
    #error This header is used only with msvc-7.1.
#endif


namespace boost { namespace egg { namespace detail_vc7_1 {


    template<class A>
    struct const_ref;


} } } // namespace boost::egg::detail_vc7_1


#endif
