#ifndef PSTADE_EGG_TO_OPTIONAL_HPP
#define PSTADE_EGG_TO_OPTIONAL_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy tuple_at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/optional/optional.hpp>
#include <pstade/pod_constant.hpp>
#include "./config.hpp" // PSTADE_EGG_MAX_ARITY
#include "./generator.hpp"


namespace pstade { namespace egg {


    namespace to_optional_detail {


        struct klass
        {
            template<class T>
            struct apply
            {
                typedef
                    boost::optional< deduce<T, as_value> >
                type;
            };
        };


    } // namespace to_optional_detail


    typedef
        generator<to_optional_detail::klass>::type
    op_to_optional;


    PSTADE_POD_CONSTANT((op_to_optional), to_optional) = PSTADE_EGG_GENERATOR_INITIALIZER();


} } // namespace pstade::egg


#endif
