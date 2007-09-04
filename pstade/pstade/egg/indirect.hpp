#ifndef PSTADE_EGG_INDIRECT_HPP
#define PSTADE_EGG_INDIRECT_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// 'boost::indirect_iterator<>' is famous.
// This is intended as "indirect_function<>".
// See also 'boost::indirect_fun'.


#include <pstade/pod_constant.hpp>
#include "./detail/baby_indirect_result.hpp"
#include "./function.hpp"
#include "./generator.hpp"
#include "./use_brace_level1.hpp"


namespace pstade { namespace egg {


    template<class Dereferenceable, class Pass = boost::use_default>
    struct result_of_indirect
    {
        typedef function<detail::baby_indirect_result<Dereferenceable>, Pass> type;
    };


    #define PSTADE_EGG_INDIRECT_L { {
    #define PSTADE_EGG_INDIRECT_R } }


    typedef
        generator<
            result_of_indirect< deduce<boost::mpl::_1, as_value> >::type,
            boost::use_default,
            use_brace_level1
        >::type
    op_indirect;


    PSTADE_POD_CONSTANT((op_indirect), indirect) = PSTADE_EGG_GENERATOR;


} } // namespace pstade::egg


#endif
