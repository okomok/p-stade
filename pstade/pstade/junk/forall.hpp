#ifndef BOOST_EGG_DETAIL_FORALL_HPP
#define BOOST_EGG_DETAIL_FORALL_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/end.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_same.hpp>


namespace boost { namespace egg { namespace details {


    template<class Seq, class Pred>
    struct forall :
        boost::is_same<
            typename mpl::end<Seq>::type,
            typename mpl::find_if< Seq, mpl::not_<Pred> >::type
        >
    { };


} } } // namespace boost::egg::details


#endif
