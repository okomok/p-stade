#ifndef BOOST_EGG_DETAIL_IS_FUSION_SEQUENCE_HPP
#define BOOST_EGG_DETAIL_IS_FUSION_SEQUENCE_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/egg/detail/is_boost_tuple.hpp>
#include <boost/egg/detail/is_std_pair.hpp>


namespace boost { namespace egg { namespace details {


    template<class Tuple>
    struct is_fusion_sequence :
        mpl::and_<
            mpl::not_< is_boost_tuple<Tuple> >,
            mpl::not_< is_std_pair<Tuple> >
        >
    { };


} } } // namespace boost::egg::details


#endif
