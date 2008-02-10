#ifndef PSTADE_TUPLE_HPP
#define PSTADE_TUPLE_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/size.hpp>
#include <boost/tuple/tuple.hpp> // inclusion guaranteed
#include <boost/type_traits/remove_cv.hpp>
#include <boost/version.hpp>
#include <pstade/mpl_boost_tuple.hpp>
#include <pstade/mpl_std_pair.hpp>

#if BOOST_VERSION >= 103500
    #define PSTADE_TUPLE_HAS_FUSIONS
    #include <boost/fusion/include/mpl.hpp> // lets FusionSequence be MPLSequence
#endif


namespace pstade {


    template<class Tuple, class N>
    struct tuple_element :
        boost::mpl::at<typename boost::remove_cv<Tuple>::type, N>
    { };

    template<class Tuple, int N>
    struct tuple_element_c :
        tuple_element< Tuple, boost::mpl::int_<N> >
    { };


    // It is guaranteed to return `int_<>`.
    template<class Tuple>
    struct tuple_length :
        boost::mpl::int_<
            boost::mpl::size<typename boost::remove_cv<Tuple>::type>::type::value
        >
    { };


} // namespace pstade


#endif



#endif
