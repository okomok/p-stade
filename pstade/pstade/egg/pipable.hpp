#ifndef PSTADE_EGG_PIPABLE_HPP
#define PSTADE_EGG_PIPABLE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy tuple_at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/placeholders.hpp>
#include "./aggregate1.hpp"
#include "./baby/pipable_result.hpp"
#include "./deduce.hpp"
#include "./function.hpp"
#include "./generator.hpp"
#include "./object.hpp"


namespace pstade { namespace egg {


    template<class Base>
    struct pipable_result
    {
        typedef
            function< baby::pipable_result<Base> >
        type;
    };


    typedef
        generator<
            pipable_result< deduce<boost::mpl::_1, as_value> >::type,
            aggregate1
        >::type
    op_pipable;


    PSTADE_EGG_OBJECT((op_pipable), pipable) = { {} };


} } // namespace pstade::egg


#endif
