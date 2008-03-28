#ifndef BOOST_EGG_DETAIL_REF_HPP
#define BOOST_EGG_DETAIL_REF_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// boost::ref is unusable because of "early unwrapping" by Boost.Lambda.


#include <boost/utility/addressof.hpp>
#include <boost/egg/by_perfect.hpp>
#include <boost/egg/by_value.hpp>
#include <boost/egg/const.hpp>


namespace boost { namespace egg { namespace details {


    template<class T>
    struct reference_wrapper_
    {
        typedef T wrapped_type;
        wrapped_type *m_wrapped;
    };


    struct little_wrap_ref
    {
        template<class Me, class T>
        struct apply
        {
            typedef reference_wrapper_<T> type;
        };

        template<class Re, class T>
        Re call(T &t) const
        {
            Re r = {boost::addressof(t)};
            return r;
        };
    };

    typedef function<little_wrap_ref, by_perfect> T_wrap_ref;
    BOOST_EGG_CONST((T_wrap_ref), wrap_ref) = BOOST_EGG_GENERATOR();


    struct little_unwrap_ref
    {
        template<class Me, class W>
        struct apply
        {
            typedef typename W::wrapped_type &type;
        };

        template<class Re, class W>
        Re call(W w) const
        {
            return *w.m_wrapped;
        }
    };

    typedef function<little_unwrap_ref, by_value> T_unwrap_ref;
    BOOST_EGG_CONST((T_unwrap_ref), unwrap_ref) = {{}};


} } } // namespace boost::egg::details


#endif
