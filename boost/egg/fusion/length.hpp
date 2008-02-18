#ifndef BOOST_EGG_FUSION_LENGTH_HPP
#define BOOST_EGG_FUSION_LENGTH_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/int.hpp>
#include <boost/mpl/size.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_HAS_FUSIONS
#include <boost/egg/detail/mpl_boost_tuple.hpp>
#include <boost/egg/detail/mpl_std_pair.hpp>

#if defined(BOOST_EGG_HAS_FUSIONS)
    #include <boost/fusion/include/mpl.hpp> // lets FusionSequence be MPLSequence
#endif


namespace boost { namespace egg {


    // It is guaranteed to return `int_`.
    template<class Tuple>
    struct fusion_length :
        mpl::int_<
            mpl::size<typename remove_cv<Tuple>::type>::type::value
        >
    { };


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
