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
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/apple/is_boost_tuple.hpp>
#include <pstade/apple/pair_fwd.hpp>
#include "../config.hpp" // PSTADE_EGG_HAS_FUSIONS

#if defined(PSTADE_EGG_HAS_FUSIONS)
    #include <boost/fusion/include/mpl.hpp> // lets FusionSequence be MPLSequence
#endif


namespace pstade { namespace egg {


    namespace fusion_element_detail {


        template<class N, class Tuple>
        struct aux_ :
            boost::mpl::eval_if< apple::is_boost_tuple<Tuple>,
                boost::tuples::element<N::value, Tuple>,
                boost::mpl::at<Tuple, N>
            >
        { };

        template<class N, class T, class U>
        struct aux_< N, std::pair<T, U> > :
            boost::mpl::if_< boost::mpl::equal_to<boost::mpl::int_<0>, N>,
                T,
                U
            >
        { };


    } // namespace fusion_element_detail


    template<class N, class Tuple>
    struct fusion_element :
        fusion_element_detail::aux_<N, typename boost::remove_cv<Tuple>::type>
    { };


    template<int N, class Tuple>
    struct fusion_element_c :
        fusion_element<boost::mpl::int_<N>, Tuple>
    { };


} } // namespace pstade::egg


#include "../detail/suffix.hpp"
#endif
