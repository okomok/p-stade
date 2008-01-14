#ifndef BOOST_EGG_LAZY_HPP
#define BOOST_EGG_LAZY_HPP
#include "./detail/prefix.hpp"


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/pstade/pod_constant.hpp>
#include "./by_cref.hpp"
#include "./by_value.hpp"
#include "./detail/little_lazy_result.hpp"
#include "./generator.hpp"
#include "./use_brace2.hpp"


namespace pstade { namespace egg {


    template<class Base, class Bind = boost::use_default>
    struct result_of_lazy
    {
        typedef
            function<detail::little_lazy_result<Base, Bind>, by_cref>
        type;
    };


    #define BOOST_EGG_LAZY_L { {
    #define BOOST_EGG_LAZY_M ,
    #define BOOST_EGG_LAZY_DEFAULT_BIND BOOST_EGG_BLL_BIND_INIT
    #define BOOST_EGG_LAZY_R } }
    #define BOOST_EGG_LAZY(F) BOOST_EGG_LAZY_L F BOOST_EGG_LAZY_M BOOST_EGG_LAZY_DEFAULT_BIND BOOST_EGG_LAZY_R


    typedef
        generator<
            result_of_lazy<
                deduce<boost::mpl::_1, as_value>,
                deduce<boost::mpl::_2, as_value, boost::use_default>
            >::type,
            boost::use_default,
            use_brace2,
            by_value
        >::type
    T_lazy;

    PSTADE_POD_CONSTANT((T_lazy), lazy) = BOOST_EGG_GENERATOR();


} } // namespace pstade::egg


#endif
