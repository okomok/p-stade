#ifndef BOOST_EGG_DETAIL_BYTAG_AT_HPP
#define BOOST_EGG_DETAIL_BYTAG_AT_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/int.hpp>


namespace boost { namespace egg { namespace details {


    template<class Strategy, int Arity, int Index>
    struct bytag_at :
        Strategy::template apply<
            Strategy,
            mpl::int_<Arity>,
            mpl::int_<Index>
        >
    { };


} } } // namespace boost::egg::details


#endif
