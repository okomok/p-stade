#ifndef PSTADE_EGG_FUNCTION_FWD_HPP
#define PSTADE_EGG_FUNCTION_FWD_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/boost/use_default_fwd.hpp>
#include "./nullary_result_of.hpp"


namespace pstade { namespace egg {


    typedef boost::use_default by_perfect;
    struct by_ref;
    struct by_cref;
    struct by_value;


    template<class Baby, class Strategy = by_perfect>
    struct function;


} } // namespace pstade::egg


PSTADE_EGG_NULLARY_RESULT_OF_TEMPLATE(pstade::egg::function, (class)(class))


#endif
