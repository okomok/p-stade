#ifndef PSTADE_EGG_REGULAR_HPP
#define PSTADE_EGG_REGULAR_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/derived_from.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "./bll/result_of.hpp" // inclusion guaranteed
#include "./by_value.hpp"
#include "./detail/regularized.hpp"
#include "./indirect.hpp"


namespace pstade { namespace egg {


    namespace regular_detail {


        template<class Strategy>
        struct little
        {
            template<class Me, class Base>
            struct apply :
                result_of<X_indirect<Strategy>(detail::regularized<Base>)>
            { };

            template<class Re, class Base>
            Re call(Base base) const
            {
                return X_indirect<Strategy>()(detail::regularized<Base>(base));
            }
        };


    } // namespace regular_detail


    template<class Strategy = boost::use_default>
    struct X_regular : derived_from<
        function<regular_detail::little<Strategy>, by_value>
    >
    { };

    typedef X_regular<>::base_class T_regular;
    PSTADE_POD_CONSTANT((T_regular), regular) = {{}};


} } // namespace pstade::egg


#endif
