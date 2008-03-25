#ifndef BOOST_EGG_DETAIL_MAYBE_FIND_HPP
#define BOOST_EGG_DETAIL_MAYBE_FIND_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/deref.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/egg/detail/maybe.hpp>


namespace boost { namespace egg { namespace details {


    template<class Seq, class Pred>
    struct maybe_find
    {
        typedef typename
            mpl::find_if<Seq, Pred>::type
        iter_t;

        typedef typename
            mpl::eval_if< is_same<iter_t, typename mpl::end<Seq>::type>,
                mpl::identity<nothing>,
                just_eval< mpl::deref<iter_t> >
            >::type
        type;
    };


} } } // namespace boost::egg::details


#endif
