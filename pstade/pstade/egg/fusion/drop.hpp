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
#include "../by_perfect.hpp"
#include "../config.hpp" // PSTADE_EGG_HAS_FUSIONS
#include "../detail/tuple_drop.hpp"
#include "../specified.hpp"

#if defined(PSTADE_EGG_HAS_FUSIONS)
    #include <boost/mpl/eval_if.hpp>
    #include <boost/fusion/include/begin.hpp>
//    #include <boost/fusion/include/boost_tuple.hpp> // broken for now.
    #include <boost/fusion/sequence/intrinsic/end.hpp>
    #include <boost/fusion/include/iterator_range.hpp>
    #include <boost/fusion/include/advance.hpp>
    #include <pstade/apple/is_boost_tuple.hpp>
    #include <pstade/enable_if.hpp>
    #include <pstade/result_of.hpp>
#endif


namespace pstade { namespace egg {


#if defined(PSTADE_EGG_HAS_FUSIONS)

    namespace fusion_drop_detail {


        namespace here = fusion_drop_detail;
        namespace fusion = boost::fusion;


        template<class N, class Tuple>
        struct apply_aux
        {
            typedef
                fusion::iterator_range<
                    typename fusion::result_of::advance<
                        typename fusion::result_of::begin<Tuple>::type, N
                    >::type,
                    typename fusion::result_of::end<Tuple>::type
                >
            type;
        };

        template<class N, class Tuple> inline
        typename fusion_result_of<N, Tuple>::type
        call_aux(Tuple& t)
        {
            return typename fusion_result_of<N, Tuple>::type(
                fusion::advance<N>(fusion::begin(t)),
                fusion::end(t)
            );
        }

        template<class N>
        struct little
        {
            template<class Me, class Tuple>
            struct apply :
                boost::mpl::eval_if< apple::is_boost_tuple<Tuple>,
                    result_of<detail::X_tuple_drop<N, by_perfect>(Tuple&)>,
                    apply_aux<N, Tuple>
                >
            { };

            template<class Re, class Tuple>
            Re call(Tuple& t, typename enable_if< apple::is_boost_tuple<Tuple> >::type = 0) const
            {
                return detail::X_tuple_drop<N, by_perfect>()(t);
            }

            template<class Re, class Tuple>
            Re call(Tuple& t, typename disable_if<apple::is_boost_tuple<Tuple> >::type = 0) const
            {
                return here::call_aux<N>(t);
            }
        };


    } // namespace fusion_drop_detail

#endif // defined(PSTADE_EGG_HAS_FUSIONS)


    template<class N>
    struct X_fusion_drop :
#if defined(PSTADE_EGG_HAS_FUSIONS)
        function<fusion_drop_detail::little<N>, by_perfect>
#else
        detail::X_tuple_drop<N, by_perfect>
#endif
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
