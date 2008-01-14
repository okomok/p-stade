#ifndef PSTADE_EGG_NOT_HPP
#define PSTADE_EGG_NOT_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include "./by_perfect.hpp"
#include "./by_value.hpp"
#include "./detail/little_not_result.hpp"
#include "./generator.hpp"
#include "./use_brace2.hpp"


namespace pstade { namespace egg {


    template<class Base, class Strategy = by_perfect>
    struct result_of_not
    {
        typedef
            function<detail::little_not_result<Base, Strategy>, Strategy>
        type;
    };


    #define PSTADE_EGG_NOT_L { {
    #define PSTADE_EGG_NOT_R } }
    #define PSTADE_EGG_NOT(F) PSTADE_EGG_NOT_L F PSTADE_EGG_NOT_R


    template<class Strategy = by_perfect>
    struct X_not :
        generator<
            typename result_of_not<deduce<boost::mpl::_1, as_value>, Strategy>::type,
            boost::use_default,
            use_brace2,
            by_value
        >::type
    { };


    typedef X_not<>::function_type T_not;
    typedef T_not T_not_;
    PSTADE_POD_CONSTANT((T_not_), not_) = PSTADE_EGG_GENERATOR();


} } // namespace pstade::egg


#endif
