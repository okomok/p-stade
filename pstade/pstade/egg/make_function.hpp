#ifndef PSTADE_EGG_MAKE_FUNCTION_HPP
#define PSTADE_EGG_MAKE_FUNCTION_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/derived_from.hpp>
#include <pstade/pod_constant.hpp>
#include "./by_perfect.hpp"
#include "./by_value.hpp"
#include "./construct_braced1.hpp"
#include "./generator.hpp"


namespace pstade { namespace egg {


    template<class Strategy = by_perfect>
    struct X_make_function : derived_from_eval<
        generator<
            function<deduce<mpl_1, as_value>, Strategy>,
            by_value,
            X_construct_braced1<>
        >
    >
    { };

    typedef X_make_function<>::base_class T_make_function;
    PSTADE_POD_CONSTANT((T_make_function), make_function) = PSTADE_EGG_GENERATOR();


} } // namespace pstade::egg


#endif
