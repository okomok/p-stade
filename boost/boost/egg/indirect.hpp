#ifndef BOOST_EGG_INDIRECT_HPP
#define BOOST_EGG_INDIRECT_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// You can't implement this using variadic
// so that this works with noncopyable referent.
// fuse could have worked with reference_wrapper, but 
// tr1 reference_wrapper implementation needs fuse!
// In other words, this adaptor is "primitive".


#include <boost/egg/by_perfect.hpp>
#include <boost/egg/by_value.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/construct_braced2.hpp>
#include <boost/egg/detail/derived_from.hpp>
#include <boost/egg/detail/little_indirect_result.hpp>
#include <boost/egg/generator.hpp>


namespace boost { namespace egg {


    template<class Ptr, class Strategy = by_perfect>
    struct result_of_indirect
    {
        typedef
            function<details::little_indirect_result<Ptr, Strategy>, Strategy>
        type;
    };

    #define BOOST_EGG_INDIRECT_L { {
    #define BOOST_EGG_INDIRECT_R } }
    #define BOOST_EGG_INDIRECT(P) BOOST_EGG_INDIRECT_L P BOOST_EGG_INDIRECT_R


    template<class Strategy = by_perfect>
    struct X_indirect : details::derived_from_eval<
        generator<
            typename result_of_indirect<deduce<mpl::_1, as_value>, Strategy>::type,
            by_value,
            X_construct_braced2<>
        > >
    { };

    typedef X_indirect<>::base_class T_indirect;
    BOOST_EGG_CONST((T_indirect), indirect) = BOOST_EGG_GENERATOR();


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
