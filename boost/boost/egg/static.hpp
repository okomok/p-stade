#ifndef BOOST_EGG_STATIC_HPP
#define BOOST_EGG_STATIC_HPP
#include "./detail/prefix.hpp"


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/assert.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/egg/pstade/affect.hpp>
#include <boost/egg/pstade/has_xxx.hpp>
#include "./by_perfect.hpp"
#include "./indirect.hpp"


namespace pstade { namespace egg {


    namespace static_detail {


        PSTADE_HAS_TYPE(result_type)
        PSTADE_HAS_TYPE(function_type)

        template<class X>
        struct identity_storage
        {
            typedef X object_type;
            static object_type object;
        };

        template<class X>
        typename identity_storage<X>::object_type identity_storage<X>::object = {};


        template<class X>
        struct function_storage
        {
            BOOST_MPL_ASSERT((has_function_type<X>));
            typedef typename affect_cv<X, typename X::function_type>::type object_type;
            static object_type object;
        };

        template<class X>
        typename function_storage<X>::object_type function_storage<X>::object = {{}};


        PSTADE_HAS_TYPE(strategy_type)

        template<class X>
        struct get_strategy_of
        {
            typedef typename X::strategy_type type;
        };

        template<class X>
        struct strategy_of :
            boost::mpl::eval_if< has_strategy_type<X>,
                get_strategy_of<X>,
                boost::mpl::identity<by_perfect>
            >
        { };


    } // namespace static_detail


    // TODO: cooler customization point
    template<class X>
    struct static_storage :
        boost::mpl::if_< static_detail::has_result_type<X>,
            static_detail::identity_storage<X>,
            static_detail::function_storage<X>
        >::type
    { };


    template<class X>
    struct static_ :
        result_of_indirect<
            typename static_storage<X const>::object_type *, // const for now.
            typename static_detail::strategy_of<X>::type
        >
    { };

    #define BOOST_EGG_STATIC_L BOOST_EGG_INDIRECT_L &pstade::egg::static_storage<
    #define BOOST_EGG_STATIC_R >::object BOOST_EGG_INDIRECT_R 
    #define BOOST_EGG_STATIC(F) BOOST_EGG_STATIC_L F BOOST_EGG_STATIC_R


} } // namespace pstade::egg


#endif
