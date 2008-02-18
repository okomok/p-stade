#ifndef BOOST_EGG_PIPABLE_HPP
#define BOOST_EGG_PIPABLE_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/by_perfect.hpp>
#include <boost/egg/by_value.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/construct_braced2.hpp>
#include <boost/egg/detail/derived_from.hpp>
#include <boost/egg/detail/little_pipable_result.hpp>
#include <boost/egg/generator.hpp>


namespace boost { namespace egg {


    template<class Base, class Strategy = by_perfect, class OperandBytag = by_perfect>
    struct result_of_pipable
    {
        typedef
            function<details::little_pipable_result<Base, Strategy, OperandBytag>, Strategy>
        type;
    };

    #define BOOST_EGG_PIPABLE_L { {
    #define BOOST_EGG_PIPABLE_R , {} } }
    #define BOOST_EGG_PIPABLE(F) BOOST_EGG_PIPABLE_L F BOOST_EGG_PIPABLE_R


    template<class Strategy = by_perfect, class OperandBytag = by_perfect>
    struct X_pipable : details::derived_from_eval<
        generator<
            typename result_of_pipable<deduce<mpl::_1, as_value>, Strategy, OperandBytag>::type,
            by_value,
            X_construct_braced2<>
        > >
    { };

    typedef X_pipable<>::base_class T_pipable;
    BOOST_EGG_CONST((T_pipable), pipable) = BOOST_EGG_GENERATOR();


    // If msvc fails to find operator|, use this as super type.
    using details::lookup_pipable_operator;


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
