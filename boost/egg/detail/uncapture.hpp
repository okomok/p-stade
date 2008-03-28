#ifndef BOOST_EGG_DETAIL_UNCAPTURE_HPP
#define BOOST_EGG_DETAIL_UNCAPTURE_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/detail/boost_ref_fwd.hpp>


namespace boost { namespace egg { namespace details {

    
    template<class A>
    struct uncapture
    {
        typedef A const &result_type;

        result_type operator()(A const &a) const
        {
            return a;
        }
    };

    template<class T>
    struct uncapture< reference_wrapper<T> >
    {
        typedef T &result_type;

        result_type operator()(reference_wrapper<T> const &w) const
        {
            return w;
        }
    };


    template<bool Cond, class A>
    struct uncapture_if_aux :
        uncapture<A>
    { };

    template<class A>
    struct uncapture_if_aux<false, A>
    {
        typedef A const &result_type;

        result_type operator()(A const &a) const
        {
            return a;
        }    
    };

    template<class Cond, class A>
    struct uncapture_if :
        uncapture_if_aux<Cond::value, A>
    { };


} } } // namespace boost::egg::details


#endif
