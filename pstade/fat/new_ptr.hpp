#ifndef PSTADE_NEW_PTR_HPP
#define PSTADE_NEW_PTR_HPP
#include "./detail/prefix.hpp"


// PStade.Fat
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/pointee.hpp>
#include <pstade/egg/compose.hpp>
#include <pstade/egg/nullary_result_of.hpp>
#include "./construct.hpp"
#include "./new.hpp"


namespace pstade { namespace fat {


    template<class P>
    struct tp_new_ptr :
        egg::result_of_compose<
            typename tp_construct<P>::type,
            typename tp_new_<typename boost::pointee<P>::type>::type,
            P
        >
    { };


    template<class P>
    struct xp_new_ptr :
        tp_new_ptr<P>::type
    { };


} } // namespace pstade::fat


PSTADE_EGG_NULLARY_RESULT_OF_TEMPLATE(pstade::fat::xp_new_ptr, (class))


#endif
