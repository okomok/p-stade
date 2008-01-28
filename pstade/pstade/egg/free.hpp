#ifndef PSTADE_EGG_FREE_HPP
#define PSTADE_EGG_FREE_HPP
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
#include "./construct_braced2.hpp"
#include "./detail/little_free_result.hpp"
#include "./generator.hpp"


namespace pstade { namespace egg {


    template<class MemPtr, class Strategy = by_perfect>
    struct result_of_free
    {
        typedef
            function<detail::little_free_result<MemPtr, Strategy>, Strategy>
        type;
    };

    #define PSTADE_EGG_FREE_L { {
    #define PSTADE_EGG_FREE_R } }
    #define PSTADE_EGG_FREE(P) PSTADE_EGG_FREE_L P PSTADE_EGG_FREE_R


    template<class Strategy = by_perfect>
    struct X_free :
        generator<
            typename result_of_free<deduce<mpl_1, as_value>, Strategy>::type,
            by_value,
            X_construct_braced2<>
        >::type
    { };

    typedef X_free<>::function_type T_free;
    PSTADE_POD_CONSTANT((T_free), free) = PSTADE_EGG_GENERATOR();

    typedef T_free T_free_;
    PSTADE_POD_CONSTANT((T_free_), free_) = PSTADE_EGG_GENERATOR();


} } // namespace pstade::egg


#endif
