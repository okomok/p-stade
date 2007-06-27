#ifndef PSTADE_EGG_UNFUSE_HPP
#define PSTADE_EGG_UNFUSE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy tuple_at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include "./aggregate1.hpp"
#include "./function.hpp"
#include "./generator.hpp"
#include "./unfuse_result.hpp"


namespace pstade { namespace egg {


    // Todo: make this nullary-callable.

    typedef
        function<
            generator<
                function< unfuse_result< deduce<boost::mpl::_1, deducers::as_value> > >,
                aggregate1
            >
        >
    op_unfuse;


    PSTADE_POD_CONSTANT(unfuse, (op_unfuse))


} } // namespace pstade::egg


#endif
