#ifndef BOOST_EGG_PIPABLE_HPP
#define BOOST_EGG_PIPABLE_HPP
#include "./detail/prefix.hpp"


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/pstade/pod_constant.hpp>
#include <boost/egg/pstade/use_default.hpp>
#include "./by_perfect.hpp"
#include "./by_value.hpp"
#include "./detail/little_pipable_result.hpp"
#include "./generator.hpp"
#include "./use_brace2.hpp"


namespace pstade { namespace egg {


    template<class Base, class Strategy = by_perfect, class OperandBytag = by_perfect>
    struct result_of_pipable
    {
        typedef
            function<detail::little_pipable_result<Base, Strategy, OperandBytag>, Strategy>
        type;
    };


    #define BOOST_EGG_PIPABLE_L { {
    #define BOOST_EGG_PIPABLE_R , {} } }
    #define BOOST_EGG_PIPABLE(F) BOOST_EGG_PIPABLE_L F BOOST_EGG_PIPABLE_R


    template<class Strategy = by_perfect, class OperandBytag = by_perfect>
    struct X_pipable :
        generator<
            typename result_of_pipable<deduce<boost::mpl::_1, as_value>, Strategy, OperandBytag>::type,
            boost::use_default,
            use_brace2,
            by_value
        >::type
    { };

    typedef X_pipable<>::function_type T_pipable;
    PSTADE_POD_CONSTANT((T_pipable), pipable) = BOOST_EGG_GENERATOR();


    // If msvc fails to find operator|, use this as super type.
    using detail::lookup_pipable_operator;


} } // namespace pstade::egg


#endif
