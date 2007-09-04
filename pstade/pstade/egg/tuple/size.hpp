#ifndef PSTADE_EGG_TUPLE_SIZE_HPP
#define PSTADE_EGG_TUPLE_SIZE_HPP
#include "../detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy tuple_at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/size.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/apple/pair_fwd.hpp>
#include "../config.hpp"
#include "./detail/is_boost_tuple.hpp"

#if defined(PSTADE_EGG_SUPPORTS_FUSION_SEQUENCE)
    #include <boost/fusion/sequence/intrinsic/mpl.hpp> // lets FusionSequence be MPLSequence
#endif


namespace pstade { namespace egg {


    namespace tuple_size_detail {


        template<class Tuple>
        struct boost_tuple_size :
            boost::mpl::int_<boost::tuples::length<Tuple>::value>
        { };


        template<class Tuple>
        struct aux :
            boost::mpl::eval_if< tuple_detail::is_boost_tuple<Tuple>,
                boost_tuple_size<Tuple>,
                boost::mpl::size<Tuple>
            >::type
        { };

        template<class T, class U>
        struct aux< std::pair<T, U> > :
            boost::mpl::int_<2>
        { };


    } // namespace tuple_size_detail


    template<class Tuple>
    struct tuple_size :
        tuple_size_detail::aux<typename boost::remove_cv<Tuple>::type>
    { };


} } // namespace pstade::egg


#endif
