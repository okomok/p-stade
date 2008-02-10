#ifndef PSTADE_EGG_DETAIL_IS_FUSION_SEQUENCE_HPP
#define PSTADE_EGG_DETAIL_IS_FUSION_SEQUENCE_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// #include <boost/fusion/include/is_sequence.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/apple/is_boost_tuple.hpp>
#include <pstade/apple/is_pair.hpp>


namespace pstade { namespace egg { namespace detail {


    template<class Tuple>
    struct is_fusion_sequence :
        boost::mpl::and_<
            boost::mpl::not_< apple::is_boost_tuple<Tuple> >,
            boost::mpl::not_< apple::is_pair<Tuple> >
            // , boost::fusion::traits::is_sequence<typename boost::remove_cv<Tuple>::type>
        >
    { };


} } } // namespace pstade::egg::detail


#endif
