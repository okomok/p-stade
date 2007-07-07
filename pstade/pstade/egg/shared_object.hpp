#ifndef PSTADE_EGG_SHARED_OBJECT_HPP
#define PSTADE_EGG_SHARED_OBJECT_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/placeholders.hpp>
#include <boost/pointee.hpp>
#include <pstade/pod_constant.hpp>
#include "./automatic.hpp"
#include "./new_shared.hpp"


namespace pstade { namespace egg {


    typedef
        automatic<
            xp_new_shared< boost::pointee<boost::mpl::_1> >
        >::type
    op_shared_object;


    PSTADE_POD_CONSTANT((op_shared_object), shared_object) = PSTADE_EGG_AUTOMATIC_INITIALIZER();


} } // namespace pstade::egg


#endif
