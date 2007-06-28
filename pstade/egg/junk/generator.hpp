#ifndef PSTADE_EGG_GENERATOR_HPP
#define PSTADE_EGG_GENERATOR_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy tuple_at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./baby/generator.hpp"
#include "./function.hpp"


namespace pstade { namespace egg {


    template<
        class Lambda,
        class How           = boost::use_default,
        class NullaryResult = boost::use_default
    >
    struct generator
    {
        typedef
            function< baby::generator<Lambda, How, NullaryResult> >
        type;
    };


} } // namespace pstade::egg


#endif
