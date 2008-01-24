#ifndef PSTADE_EGG_MAKE_FUNCTION_HPP
#define PSTADE_EGG_MAKE_FUNCTION_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include "./braced1_construct.hpp"
#include "./by_perfect.hpp"
#include "./by_value.hpp"
#include "./generator.hpp"


namespace pstade { namespace egg {


    template<class Strategy = by_perfect>
    struct X_make_function :
        generator<
            function<deduce<mpl_1, as_value>, Strategy>,
            by_value,
            X_braced1_construct<mpl_1, mpl_2>
        >::type
    { };

    typedef X_make_function<>::function_type T_make_function;
    PSTADE_POD_CONSTANT((T_make_function), make_function) = PSTADE_EGG_GENERATOR();


} } // namespace pstade::egg


#endif
