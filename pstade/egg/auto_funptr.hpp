#ifndef PSTADE_EGG_AUTO_FUNPTR_HPP
#define PSTADE_EGG_AUTO_FUNPTR_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include "./automatic.hpp"
#include "./funptr.hpp"


namespace pstade { namespace egg {


    namespace auto_funptr_detail {


        struct id;


        template<class FunPtr>
        struct cast;

        template<class Fun>
        struct cast<Fun *>
        {
            typedef Fun *result_type;

            template<class Base>
            result_type operator()(Base base) const
            {
                return X_funptr<Fun, id>()(base);
            }
        };


    } // namespace auto_funptr_detail


    typedef automatic< auto_funptr_detail::cast<boost::mpl::_1> >::type T_auto_funptr;
    PSTADE_POD_CONSTANT((T_auto_funptr), auto_funptr) = PSTADE_EGG_AUTOMATIC;


} } // namespace pstade::egg


#endif
