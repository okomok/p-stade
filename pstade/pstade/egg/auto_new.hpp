#ifndef PSTADE_AUTO_NEW_HPP
#define PSTADE_AUTO_NEW_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <memory> // auto_ptr
#include "./nullary_result_of.hpp"
#include "./ptr_new.hpp"


namespace pstade { namespace egg {


    template<class X, class Strategy = boost::use_default>
    struct X_auto_new :
        X_ptr_new<std::auto_ptr<X>, Strategy>
    { };


} } // namespace pstade::egg


#define  PSTADE_EGG_NULLARY_RESULT_OF_TEMPLATE_PARAMS (pstade::egg::X_auto_new, (class))
#include PSTADE_EGG_NULLARY_RESULT_OF_TEMPLATE()


#endif
