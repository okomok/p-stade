#ifndef PSTADE_EGG_FUSION_DROP1_HPP
#define PSTADE_EGG_FUSION_DROP1_HPP
#include "../detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/affect.hpp>
#include <pstade/apple/is_boost_tuple.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/pod_constant.hpp>
#include "../by_perfect.hpp"
#include "../config.hpp" // PSTADE_EGG_HAS_FUSIONS

#if defined(PSTADE_EGG_HAS_FUSIONS)
    #include <boost/fusion/include/begin.hpp>
//    #include <boost/fusion/include/boost_tuple.hpp> // broken for now.
    #include <boost/fusion/sequence/intrinsic/end.hpp>
    #include <boost/fusion/include/iterator_range.hpp>
    #include <boost/fusion/include/next.hpp>
#endif


namespace pstade { namespace egg {


    namespace fusion_drop1_detail {


        namespace here = fusion_drop1_detail;


        template<class Tuple>
        struct tuple_result_of :
            boost::mpl::eval_if< boost::is_same<typename Tuple::tail_type, boost::tuples::null_type>,
                boost::mpl::identity<boost::tuples::null_type>,
                affect<Tuple&, typename Tuple::tail_type>
            >
        { };

        template<class Tuple> inline
        typename tuple_result_of<Tuple>::type
        tuple_call(Tuple& t)
        {
            return t.get_tail();
        }


#if defined(PSTADE_EGG_HAS_FUSIONS)

        template<class Tuple>
        struct fusion_result_of
        {
            typedef
                boost::fusion::iterator_range<
                    typename boost::fusion::result_of::next<
                        typename boost::fusion::result_of::begin<Tuple>::type
                    >::type,
                    typename boost::fusion::result_of::end<Tuple>::type
                >
            type;
        };

        template<class Tuple> inline
        typename fusion_result_of<Tuple>::type
        fusion_call(Tuple& t)
        {
            return typename fusion_result_of<Tuple>::type(
                boost::fusion::next(boost::fusion::begin(t)),
                boost::fusion::end(t)
            );
        }

#endif


        struct little
        {
#if defined(PSTADE_EGG_HAS_FUSIONS)
            template<class Me, class Tuple>
            struct apply :
                boost::mpl::eval_if< apple::is_boost_tuple<Tuple>,
                    tuple_result_of<Tuple>,
                    fusion_result_of<Tuple>
                >
            { };

            template<class Re, class Tuple>
            Re call(Tuple& t, typename enable_if< apple::is_boost_tuple<Tuple> >::type = 0) const
            {
                return here::tuple_call(t);
            }

            template<class Re, class Tuple>
            Re call(Tuple& t, typename disable_if<apple::is_boost_tuple<Tuple> >::type = 0) const
            {
                return here::fusion_call(t);
            }
#else
            template<class Me, class Tuple>
            struct apply :
                tuple_result_of<Tuple>
            { };

            template<class Re, class Tuple>
            Re call(Tuple& t) const
            {
                return here::tuple_call(t);
            }
#endif
        };


    } // namespace fusion_drop1_detail


    typedef function<fusion_drop1_detail::little, by_perfect> T_fusion_drop1;
    PSTADE_POD_CONSTANT((T_fusion_drop1), fusion_drop1) = {{}};


} } // namespace pstade::egg


#endif
