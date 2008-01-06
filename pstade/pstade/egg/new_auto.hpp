#ifndef PSTADE_NEW_AUTO_HPP
#define PSTADE_NEW_AUTO_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <memory> // auto_ptr
#include "./new_ptr.hpp"
#include "./nullary_result_of.hpp"


namespace pstade { namespace egg {


    template<class X>
    struct X_new_auto :
        X_new_ptr< std::auto_ptr<X> >
    { };


} } // namespace pstade::egg


#define  PSTADE_EGG_NULLARY_RESULT_OF_TEMPLATE_PARAMS (pstade::egg::X_new_auto, (class))
#include PSTADE_EGG_NULLARY_RESULT_OF_TEMPLATE()


#endif
