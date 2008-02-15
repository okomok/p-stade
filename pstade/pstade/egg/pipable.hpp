#ifndef PSTADE_EGG_PIPABLE_HPP
#define PSTADE_EGG_PIPABLE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/derived_from.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/use_default.hpp>
#include "./by_perfect.hpp"
#include "./by_value.hpp"
#include "./construct_braced2.hpp"
#include "./detail/little_pipable_result.hpp"
#include "./generator.hpp"


namespace pstade { namespace egg {


    template<class Base, class Strategy = by_perfect, class OperandBytag = by_perfect>
    struct result_of_pipable
    {
        typedef
            function<detail::little_pipable_result<Base, Strategy, OperandBytag>, Strategy>
        type;
    };

    #define PSTADE_EGG_PIPABLE_L { {
    #define PSTADE_EGG_PIPABLE_R , {} } }
    #define PSTADE_EGG_PIPABLE(F) PSTADE_EGG_PIPABLE_L F PSTADE_EGG_PIPABLE_R


    template<class Strategy = by_perfect, class OperandBytag = by_perfect>
    struct X_pipable : derived_from_eval<
        generator<
            typename result_of_pipable<deduce<mpl_1, as_value>, Strategy, OperandBytag>::type,
            by_value,
            X_construct_braced2<>
        > >
    { };

    typedef X_pipable<>::base_class T_pipable;
    PSTADE_POD_CONSTANT((T_pipable), pipable) = PSTADE_EGG_GENERATOR();


    // If msvc fails to find operator|, use this as super type.
    using detail::lookup_pipable_operator;


} } // namespace pstade::egg


#include "./detail/suffix.hpp"
#endif
