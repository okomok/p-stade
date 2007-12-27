#ifndef PSTADE_NEW_PTR_HPP
#define PSTADE_NEW_PTR_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/pointee.hpp>
#include "./compose.hpp"
#include "./construct.hpp"
#include "./new.hpp"
#include "./nullary_result_of.hpp"


namespace pstade { namespace egg {


    template<class P>
    struct X_new_ptr :
        result_of_compose<
            typename X_construct<P>::function_type,
            typename X_new_<typename boost::pointee<P>::type>::function_type,
            P
        >::type
    { };


} } // namespace pstade::egg


PSTADE_EGG_NULLARY_RESULT_OF_TEMPLATE(pstade::egg::X_new_ptr, (class))


#endif
