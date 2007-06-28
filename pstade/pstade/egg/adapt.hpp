#ifndef PSTADE_EGG_ADAPT_HPP
#define PSTADE_EGG_ADAPT_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy tuple_at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/placeholders.hpp>
#include "./baby/adapt.hpp"
#include "./detail/as_mpl_lambda.hpp"
#include "./function.hpp"
#include "./object.hpp"


namespace pstade { namespace egg {


    #define PSTADE_EGG_ADAPT(O, L) \
        namespace BOOST_PP_CAT(pstade_egg_adapt_workarea_of_, O) { \
            using namespace boost::mpl::placeholders; \
            typedef pstade::egg::function< pstade::egg::baby::adapt<PSTADE_EGG_DETAIL_AS_MPL_LAMBDA(L)> > op; \
        } \
        typedef BOOST_PP_CAT(pstade_egg_adapt_workarea_of_, O)::op BOOST_PP_CAT(op_, O); \
        PSTADE_EGG_OBJECT((BOOST_PP_CAT(op_, O)), O) = { {} }; \
    /**/


} } // namespace pstade::egg


#endif
