#ifndef BOOST_EGG_FUNCTION_FWD_HPP
#define BOOST_EGG_FUNCTION_FWD_HPP
#include "./detail/prefix.hpp"


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/pstade/apple/boost/use_default_fwd.hpp>
#include "./nullary_result_of.hpp"


namespace pstade { namespace egg {


    typedef boost::use_default by_perfect;
    struct by_ref;
    struct by_cref;
    struct by_value;


    template<class Little, class Strategy = by_perfect>
    struct function;

    #define BOOST_EGG_FUNCTION_L {
    #define BOOST_EGG_FUNCTION_R }
    #define BOOST_EGG_FUNCTION(l) BOOST_EGG_FUNCTION_L l BOOST_EGG_FUNCTION_R


} } // namespace pstade::egg


#define  BOOST_EGG_NULLARY_RESULT_OF_TEMPLATE_PARAMS (pstade::egg::function, (class)(class))
#include BOOST_EGG_NULLARY_RESULT_OF_TEMPLATE()


#endif
