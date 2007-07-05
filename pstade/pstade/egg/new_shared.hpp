#ifndef PSTADE_NEW_SHARED_HPP
#define PSTADE_NEW_SHARED_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/shared_ptr.hpp>
#include "./new_ptr.hpp"
#include "./nullary_result_of.hpp"


namespace pstade { namespace egg {


    template<class X>
    struct tp_new_shared :
        tp_new_ptr< boost::shared_ptr<X> >
    { };


    template<class X>
    struct xp_new_shared :
        tp_new_shared<X>::type
    { };


} } // namespace pstade::egg


PSTADE_EGG_NULLARY_RESULT_OF_TEMPLATE(pstade::egg::xp_new_shared, 1)


#endif
