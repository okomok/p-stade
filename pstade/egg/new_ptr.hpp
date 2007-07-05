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
    struct tp_new_ptr :
        result_of_compose<
            typename tp_construct<P>::type,
            typename tp_new_<typename boost::pointee<P>::type>::type,
            P
        >
    { };


    template<class P>
    struct xp_new_ptr :
        tp_new_ptr<P>::type
    { };


} } // namespace pstade::egg


PSTADE_EGG_NULLARY_RESULT_OF_TEMPLATE(pstade::egg::xp_new_ptr, (class))


#endif
