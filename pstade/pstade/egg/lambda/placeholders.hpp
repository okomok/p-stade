#ifndef PSTADE_EGG_LAMBDA_PLACEHOLDERS_HPP
#define PSTADE_EGG_LAMBDA_PLACEHOLDERS_HPP
#include "../detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/lambda/core.hpp> // placeholders
#include <boost/type_traits/remove_const.hpp>
#include <pstade/constant.hpp>


namespace pstade { namespace egg {


    namespace lambda_placeholders {

        // These are not pod.
        typedef boost::remove_const<boost::lambda::placeholder1_type>::type op_lambda_1;
        typedef boost::remove_const<boost::lambda::placeholder2_type>::type op_lambda_2;
        typedef boost::remove_const<boost::lambda::placeholder3_type>::type op_lambda_3;

        PSTADE_CONSTANT(lambda_1, (op_lambda_1))
        PSTADE_CONSTANT(lambda_2, (op_lambda_2))
        PSTADE_CONSTANT(lambda_3, (op_lambda_3))

    }

    using namespace lambda_placeholders;


} } // namespace pstade::egg


#endif
