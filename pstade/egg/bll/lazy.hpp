#ifndef PSTADE_EGG_BLL_LAZY_HPP
#define PSTADE_EGG_BLL_LAZY_HPP
#include "../detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include "../by_cref.hpp"
#include "../by_value.hpp"
#include "../detail/little_bll_lazy_result.hpp"
#include "../generator.hpp"
#include "../use_brace2.hpp"
#include "./result_of.hpp" // inclusion guaranteed


namespace pstade { namespace egg {


    template<class Base>
    struct result_of_bll_lazy
    {
        typedef
            function<detail::little_bll_lazy_result<Base>, by_cref>
        type;
    };


    #define PSTADE_EGG_BLL_LAZY_L { {
    #define PSTADE_EGG_BLL_LAZY_R } }
    #define PSTADE_EGG_BLL_LAZY(F) PSTADE_EGG_BLL_LAZY_L F PSTADE_EGG_BLL_LAZY_R


    typedef
        generator<
            result_of_bll_lazy< deduce<boost::mpl::_1, as_value> >::type,
            boost::use_default,
            use_brace2,
            by_value
        >::type
    T_bll_lazy;

    PSTADE_POD_CONSTANT((T_bll_lazy), bll_lazy) = PSTADE_EGG_GENERATOR;


} } // namespace pstade::egg


#endif
