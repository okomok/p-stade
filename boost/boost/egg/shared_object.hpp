#ifndef BOOST_EGG_SHARED_OBJECT_HPP
#define BOOST_EGG_SHARED_OBJECT_HPP
#include "./detail/prefix.hpp"


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/pointee.hpp>
#include <boost/egg/pstade/pod_constant.hpp>
#include "./automatic.hpp"
#include "./new_shared.hpp"


namespace pstade { namespace egg {


    typedef
        automatic<
            X_new_shared< boost::pointee<boost::mpl::_1> >
        >::type
    T_shared_object;


    PSTADE_POD_CONSTANT((T_shared_object), shared_object) = BOOST_EGG_AUTOMATIC();


} } // namespace pstade::egg


#endif
