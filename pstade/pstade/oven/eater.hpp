#ifndef PSTADE_OVEN_EATER_HPP
#define PSTADE_OVEN_EATER_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include <pstade/unused.hpp>
#include "./applier.hpp"


namespace pstade { namespace oven {


struct T_eater
{
    typedef
        result_of<T_applier(T_unused const&)>::type
    result_type;

    result_type operator()() const
    {
        return applier(unused);
    }
};


PSTADE_POD_CONSTANT((T_eater), eater) = {};


} } // namespace pstade::oven


#endif
