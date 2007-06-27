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
#include <boost/preprocessor/cat.hpp>
#include <pstade/pod_constant.hpp>
#include "./aggregate1.hpp"
#include "./function.hpp"
#include "./generator.hpp"
#include "./pipable_result.hpp"


namespace pstade { namespace egg {


    // Todo: make this nullary-callable.

    typedef
        function<
            generator<
                function< pipable_result< deduce<boost::mpl::_1, deducers::as_value> > >,
                aggregate1
            >
        >
    op_pipable;


    PSTADE_POD_CONSTANT(pipable, (op_pipable))


    #define PSTADE_EGG_PIPABLE(O, F) \
        namespace BOOST_PP_CAT(pstade_egg_pipable_workarea_of_, O) { \
            using namespace boost::mpl::placeholders; \
            typedef pstade::egg::function< pstade::egg::pipable_result<PSTADE_UNPARENTHESIZE(F)> > pipe; \
        } \
        PSTADE_POD_CONSTANT(O, (BOOST_PP_CAT(pstade_egg_pipable_workarea_of_, O)::pipe)) \
    /**/


} } // namespace pstade::egg


#endif
