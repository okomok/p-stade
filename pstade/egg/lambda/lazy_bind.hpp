#ifndef PSTADE_EGG_LAMBDA_LAZY_BIND_HPP
#define PSTADE_EGG_LAMBDA_LAZY_BIND_HPP
#include "../detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include "../lazy.hpp"
#include "./bind.hpp"


namespace pstade { namespace egg {


    typedef result_of_lazy<op_lambda_bind>::type op_lambda_Bind;
    PSTADE_POD_CONSTANT((op_lambda_Bind), lambda_Bind) = PSTADE_EGG_LAZY_L {{}} PSTADE_EGG_LAZY_R;


} } // namespace pstade::egg


#endif
