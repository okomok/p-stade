#ifndef BOOST_EGG_DETAIL_SUBSTITUTE_HPP
#define BOOST_EGG_DETAIL_SUBSTITUTE_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/ref.hpp>
#include <boost/egg/always.hpp>
#include <boost/egg/by_cref.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/detail/enable_if.hpp>
#include <boost/egg/is_bind_expression.hpp>


namespace boost { namespace egg { namespace details {


    struct little_substitute
    {
        template<class Me, class X>
        struct apply :
            mpl::eval_if< is_bind_expression<X>,
                mpl::identity<X &>,
                result_of_<T_always_ref(X &)>
            >
        { };

        template<class Re, class X>
        Re call(X &x, typename enable_if_< is_bind_expression<X> >::type = 0) const
        {
            return x;
        }

        template<class Re, class X>
        Re call(X &x, typename disable_if_<is_bind_expression<X> >::type = 0) const
        {
            return always_ref(x);
        }
    };

    typedef function<little_substitute, by_cref> T_substitute;
    BOOST_EGG_CONST((T_substitute), substitute) = {{}};


} } } // namespace boost::egg::details


#endif
