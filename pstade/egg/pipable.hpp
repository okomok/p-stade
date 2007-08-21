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
#include "./detail/baby_pipable_result.hpp"
#include "./function.hpp"
#include "./generator.hpp"
#include "./use_brace_level1.hpp"


namespace pstade { namespace egg {


    template<class Base>
    struct result_of_pipable
    {
        typedef
            function< detail::baby_pipable_result<Base> >
        type; // = { { Base } };
    };


    #define PSTADE_EGG_PIPABLE_L { {
    #define PSTADE_EGG_PIPABLE_R } }


    typedef
        generator<
            result_of_pipable< deduce<boost::mpl::_1, as_value> >::type,
            use_brace_level1
        >::type
    op_pipable;


    PSTADE_POD_CONSTANT((op_pipable), pipable) = PSTADE_EGG_GENERATOR;


} } // namespace pstade::egg


#endif
