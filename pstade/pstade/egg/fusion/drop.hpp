#ifndef PSTADE_EGG_FUSION_DROP_HPP
#define PSTADE_EGG_FUSION_DROP_HPP
#include "../detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/int.hpp>
#include <pstade/enable_if.hpp>
#include "../by_perfect.hpp"
#include "../config.hpp" // PSTADE_EGG_HAS_FUSIONS
#include "../detail/tuple_drop.hpp"
#include "../specified.hpp"

#if defined(PSTADE_EGG_HAS_FUSIONS)
    #include <boost/fusion/include/begin.hpp>
    #include <boost/fusion/sequence/intrinsic/end.hpp>
    #include <boost/fusion/include/iterator_range.hpp>
    #include <boost/fusion/include/advance.hpp>
    #include <pstade/apple/is_boost_tuple.hpp>
    #include "../detail/is_fusion_sequence.hpp"
#endif


namespace pstade { namespace egg {


#if defined(PSTADE_EGG_HAS_FUSIONS)


    namespace detail {


        template<class N, class Tuple>
        struct tuple_drop_impl<N, Tuple,
            typename enable_if< is_fusion_sequence<Tuple> >::type>
        {
            typedef
                boost::fusion::iterator_range<
                    typename boost::fusion::result_of::advance<
                        typename boost::fusion::result_of::begin<Tuple>::type, N
                    >::type,
                    typename boost::fusion::result_of::end<Tuple>::type
                >
            result_type;

            result_type operator()(Tuple& t) const
            {
                return result_type(
                    boost::fusion::advance<N>(boost::fusion::begin(t)),
                    boost::fusion::end(t)
                );
            }
        };


    } // namespace detail


#endif // defined(PSTADE_EGG_HAS_FUSIONS)


    template<class N>
    struct X_fusion_drop :
        detail::X_tuple_drop<N, by_perfect>
    { };

     #define  PSTADE_EGG_SPECIFIED_PARAMS (fusion_drop, X_fusion_drop, (class), (1))
     #include PSTADE_EGG_SPECIFIED()


    template<int N>
    struct X_fusion_drop_c :
        X_fusion_drop< boost::mpl::int_<N> >
    { };

     #define  PSTADE_EGG_SPECIFIED_PARAMS (fusion_drop_c, X_fusion_drop_c, (int), (1))
     #include PSTADE_EGG_SPECIFIED()


} } // namespace pstade::egg


#include "../detail/suffix.hpp"
#endif
