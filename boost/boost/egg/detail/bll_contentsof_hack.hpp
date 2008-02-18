#ifndef BOOST_EGG_DETAIL_BLL_CONTENTSOF_HACK_HPP
#define BOOST_EGG_DETAIL_BLL_CONTENTSOF_HACK_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Iterator const-ness shouldn't affect its contents, IMO.


#include <cstddef> // size_t
#include <boost/indirect_reference.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/egg/bll/extension_fwd.hpp>


namespace boost { namespace egg { namespace details {


    template<class A>
    struct bll_contentsof_type :
        indirect_reference<
            typename remove_cv<A>::type
        >
    { };

    template<class A, std::size_t N>
    struct bll_contentsof_type<A[N]>
    {
        typedef A &type;
    };


} } } // namespace boost::egg::details


namespace boost { namespace lambda {


    template<class A>
    struct return_type_1<other_action<contentsof_action>, A const>
    {
        typedef typename
            plain_return_type_1<
                other_action<contentsof_action>,
                typename boost::remove_cv<A const>::type
            >::type
        type1;

        typedef typename
            boost::mpl::eval_if< boost::is_same<type1, detail::unspecified>,
                boost::egg::details::bll_contentsof_type<A const>,
                boost::mpl::identity<type1>
            >::type
        type;
    };


} } // namespace boost::lambda


#endif
