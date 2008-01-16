#ifndef PSTADE_PTR_NEW_HPP
#define PSTADE_PTR_NEW_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/pointee.hpp>
#include "./compose.hpp"
#include "./construct.hpp"
#include "./new.hpp"
#include "./nullary_result_of.hpp"


namespace pstade { namespace egg {


    template<class P, class Strategy = boost::use_default>
    struct X_ptr_new :
        result_of_compose<
            typename X_construct<P>::function_type,
            typename X_new_<typename boost::pointee<P>::type, Strategy>::function_type,
            P
        >::type
    { };


} } // namespace pstade::egg


#define  PSTADE_EGG_NULLARY_RESULT_OF_TEMPLATE_PARAMS (pstade::egg::X_ptr_new, (class))
#include PSTADE_EGG_NULLARY_RESULT_OF_TEMPLATE()


#endif
