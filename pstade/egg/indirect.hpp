#ifndef PSTADE_EGG_INDIRECT_HPP
#define PSTADE_EGG_INDIRECT_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// 'boost::indirect_iterator<>' is famous.
// This is intended as "indirect_function<>".
// See also 'boost::indirect_fun'.


#include <pstade/pod_constant.hpp>
#include "./by_perfect.hpp"
#include "./by_value.hpp"
#include "./detail/little_indirect_result.hpp"
#include "./generator.hpp"
#include "./use_brace2.hpp"


namespace pstade { namespace egg {


    template<class Ptr, class Strategy = by_perfect>
    struct result_of_indirect
    {
        typedef
            function<detail::little_indirect_result<Ptr, Strategy>, Strategy>
        type;
    };


    #define PSTADE_EGG_INDIRECT_L { {
    #define PSTADE_EGG_INDIRECT_R } }
    #define PSTADE_EGG_INDIRECT(P) PSTADE_EGG_INDIRECT_L P PSTADE_EGG_INDIRECT_R


    template<class Strategy = by_perfect>
    struct X_indirect :
        generator<
            typename result_of_indirect<deduce<boost::mpl::_1, as_value>, Strategy>::type,
            boost::use_default,
            use_brace2,
            by_value
        >::type
    { };

    typedef X_indirect<>::function_type T_indirect;
    PSTADE_POD_CONSTANT((T_indirect), indirect) = PSTADE_EGG_GENERATOR();


} } // namespace pstade::egg


#endif
