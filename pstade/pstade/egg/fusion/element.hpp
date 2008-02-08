#ifndef PSTADE_EGG_FUSION_ELEMENT_HPP
#define PSTADE_EGG_FUSION_ELEMENT_HPP
#include "../detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/mpl_boost_tuple.hpp>
#include <pstade/mpl_std_pair.hpp>
#include "../config.hpp" // PSTADE_EGG_HAS_FUSIONS

#if defined(PSTADE_EGG_HAS_FUSIONS)
    #include <boost/fusion/include/mpl.hpp> // lets FusionSequence be MPLSequence
#endif


namespace pstade { namespace egg {


    template<class N, class Tuple>
    struct fusion_element :
        boost::mpl::at<typename boost::remove_cv<Tuple>::type, N>
    { };

    template<int N, class Tuple>
    struct fusion_element_c :
        fusion_element<boost::mpl::int_<N>, Tuple>
    { };


} } // namespace pstade::egg


#include "../detail/suffix.hpp"
#endif
