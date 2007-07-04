#ifndef PSTADE_NEW_AUTO_HPP
#define PSTADE_NEW_AUTO_HPP
#include "./detail/prefix.hpp"


// PStade.Fat
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <memory> // auto_ptr
#include <pstade/egg/nullary_result_of.hpp>
#include "./new_ptr.hpp"


namespace pstade { namespace fat {


    template<class X>
    struct tp_new_auto :
        tp_new_ptr< std::auto_ptr<X> >
    { };


    template<class X>
    struct xp_new_auto :
        tp_new_auto<X>::type
    { };


} } // namespace pstade::fat


PSTADE_EGG_NULLARY_RESULT_OF_TEMPLATE(pstade::fat::xp_new_auto, (class))


#endif
