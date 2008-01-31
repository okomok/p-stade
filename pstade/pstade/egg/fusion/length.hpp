#ifndef PSTADE_EGG_FUSION_LENGTH_HPP
#define PSTADE_EGG_FUSION_LENGTH_HPP
#include "../detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// It is guaranteed that return type is `mpl::int_`.


#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/size.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/apple/is_boost_tuple.hpp>
#include <pstade/apple/pair_fwd.hpp>
#include "../config.hpp" // PSTADE_EGG_HAS_FUSIONS

#if defined(PSTADE_EGG_HAS_FUSIONS)
    #include <boost/fusion/include/mpl.hpp> // lets FusionSequence be MPLSequence
#endif


namespace pstade { namespace egg {


    namespace fusion_length_detail {


        template<class Tuple>
        struct tuple_length :
            boost::mpl::int_<boost::tuples::length<Tuple>::value>
        { };


        template<class Seq>
        struct mpl_size :
            boost::mpl::int_<boost::mpl::size<Seq>::type::value>
        { };


        template<class Tuple>
        struct aux_ :
            boost::mpl::eval_if< apple::is_boost_tuple<Tuple>,
                tuple_length<Tuple>,
                mpl_size<Tuple>
            >::type
        { };

        template<class T, class U>
        struct aux_< std::pair<T, U> > :
            boost::mpl::int_<2>
        { };


    } // namespace fusion_length_detail


    template<class Tuple>
    struct fusion_length :
        fusion_length_detail::aux_<typename boost::remove_cv<Tuple>::type>
    { };


} } // namespace pstade::egg


#endif
