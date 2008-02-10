#ifndef PSTADE_EGG_FUSION_LENGTH_HPP
#define PSTADE_EGG_FUSION_LENGTH_HPP
#include "../detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/int.hpp>
#include <boost/mpl/size.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/mpl_boost_tuple.hpp>
#include <pstade/mpl_std_pair.hpp>
#include "../config.hpp" // PSTADE_EGG_HAS_FUSIONS

#if defined(PSTADE_EGG_HAS_FUSIONS)
    #include <boost/fusion/include/mpl.hpp> // lets FusionSequence be MPLSequence
#endif


namespace pstade { namespace egg {


    // It is guaranteed to return `int_`.
    template<class Tuple>
    struct fusion_length :
        boost::mpl::int_<
            boost::mpl::size<typename boost::remove_cv<Tuple>::type>::type::value
        >
    { };


} } // namespace pstade::egg


#include "../detail/suffix.hpp"
#endif
