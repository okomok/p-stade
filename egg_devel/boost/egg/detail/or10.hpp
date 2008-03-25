#ifndef BOOST_EGG_DETAIL_OR10_HPP
#define BOOST_EGG_DETAIL_OR10_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/or.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>


namespace boost { namespace egg { namespace details {


    template<BOOST_PP_ENUM_PARAMS(10, class T)>
    struct or10 :
        mpl::or_<
            mpl::or_<T0, T1, T2, T3, T4>,
            mpl::or_<T5, T6, T7, T8, T9>
        >
    { };


} } } // namespace boost::egg::details


#endif
