#ifndef PSTADE_EGG_PIPABLE_HPP
#define PSTADE_EGG_PIPABLE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy tuple_at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include "./by_perfect.hpp"
#include "./by_value.hpp"
#include "./detail/baby_pipable_result.hpp"
#include "./generator.hpp"
#include "./use_brace_level1.hpp"


namespace pstade { namespace egg {


    template<class Base, class Strategy = by_perfect>
    struct result_of_pipable
    {
        typedef
            function<detail::baby_pipable_result<Base, Strategy>, Strategy>
        type;
    };


    #define PSTADE_EGG_PIPABLE_L { {
    #define PSTADE_EGG_PIPABLE_R , {} } }


    typedef
        generator<
            result_of_pipable< deduce<boost::mpl::_1, as_value> >::type,
            boost::use_default,
            use_brace_level1,
            by_value
        >::type
    T_pipable;


    PSTADE_POD_CONSTANT((T_pipable), pipable) = PSTADE_EGG_GENERATOR;


    // If msvc fails to find operator|, use this as super type.
    using detail::lookup_pipable_operator;


} } // namespace pstade::egg


#endif
