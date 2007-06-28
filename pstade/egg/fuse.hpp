#ifndef PSTADE_EGG_FUSE_HPP
#define PSTADE_EGG_FUSE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy tuple_at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/placeholders.hpp>
#include "./aggregate1.hpp"
#include "./baby/fuse_result.hpp"
#include "./baby/generator.hpp"
#include "./deduce.hpp"
#include "./function.hpp"
#include "./object.hpp"


namespace pstade { namespace egg {


    typedef
        function<
            baby::generator<
                function< baby::fuse_result< deduce<boost::mpl::_1, as_value> > >,
                aggregate1
            >
        >
    op_fuse;


    PSTADE_EGG_OBJECT((op_fuse), fuse) = { {} };


} } // namespace pstade::egg


#endif
