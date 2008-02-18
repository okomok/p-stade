#ifndef BOOST_EGG_BLL_PLACEHOLDERS_HPP
#define BOOST_EGG_BLL_PLACEHOLDERS_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/lambda/core.hpp> // placeholders
#include <boost/type_traits/remove_const.hpp>
#include <boost/egg/bll/result_of.hpp> // inclusion guaranteed


namespace boost { namespace egg {


    namespace bll_placeholders {

        // These are not pod.
        typedef remove_const<lambda::placeholder1_type>::type T_bll_1;
        typedef remove_const<lambda::placeholder2_type>::type T_bll_2;
        typedef remove_const<lambda::placeholder3_type>::type T_bll_3;

        T_bll_1 const bll_1 = T_bll_1();
        T_bll_2 const bll_2 = T_bll_2();
        T_bll_3 const bll_3 = T_bll_3();

    }

    using namespace bll_placeholders;


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
