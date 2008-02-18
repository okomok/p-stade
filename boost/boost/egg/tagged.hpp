#ifndef BOOST_EGG_TAGGED_HPP
#define BOOST_EGG_TAGGED_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/egg/detail/unspecified.hpp>
#include <boost/egg/result_of.hpp>
#include <boost/egg/return.hpp>


namespace boost { namespace egg {


    template<class Base, class Tag, class Strategy = use_default>
    struct result_of_tagged :
        result_of_return<Base, use_default, Strategy, Tag>
    { };

    #define BOOST_EGG_TAGGED_L BOOST_EGG_RETURN_L
    #define BOOST_EGG_TAGGED_R BOOST_EGG_RETURN_R
    #define BOOST_EGG_TAGGED(F) BOOST_EGG_TAGGED_L F BOOST_EGG_TAGGED_R


    template<class Tag, class Strategy = use_default>
    struct X_tagged :
        X_return<use_default, Strategy, Tag>
    { };

    template<class Tag, class Base> inline
    typename result_of_<X_tagged<Tag>(Base &)>::type tagged(Base base)
    {
        return X_tagged<Tag>()(base);
    }


    namespace tag_of_detail {


        template<class F>
        struct aux_
        {
            typedef unspecified type;
        };

        template<class Base, class Return, class Strategy, class Tag>
        struct aux_< function<details::little_return_result<Base, Return, Strategy, Tag>, Strategy> >
        {
            typedef Tag type;
        };


    } // namespace tag_of_detail


    template<class F>
    struct tag_of :
        tag_of_detail::aux_<typename remove_cv<F>::type>
    { };


    template<class F, class Tag>
    struct is_tagged_with :
        is_same<typename tag_of<F>::type, Tag>
    { };


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
