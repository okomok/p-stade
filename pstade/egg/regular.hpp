#ifndef PSTADE_EGG_REGULAR_HPP
#define PSTADE_EGG_REGULAR_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "./detail/regularized.hpp"
#include "./bll/result_of.hpp" // inclusion guaranteed
#include "./by_value.hpp"
#include "./indirect.hpp"


namespace pstade { namespace egg {


    namespace regular_detail {


        struct little
        {
            template<class Myself, class Base>
            struct apply :
                result_of<T_indirect(detail::regularized<Base>)>
            { };

            template<class Result, class Base>
            Result call(Base base) const
            {
                return indirect(detail::regularized<Base>(base));
            }
        };


    } // namespace regular_detail


    typedef function<regular_detail::little, by_value> T_regular;
    PSTADE_POD_CONSTANT((T_regular), regular) = {{}};


} } // namespace pstade::egg


#endif
