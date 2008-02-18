#ifndef BOOST_EGG_DETAIL_WRAP_HPP
#define BOOST_EGG_DETAIL_WRAP_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace boost { namespace egg { namespace details {


    // can synchronize initializers.
    template<class Base>
    struct wrap
    {
        Base base;
    };


} } } // namespace boost::egg::details


#endif
