#ifndef PSTADE_EGG_FUSION_PREPEND_HPP
#define PSTADE_EGG_FUSION_PREPEND_HPP
#include "../detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/eval_if.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/apple/is_boost_tuple.hpp>
#include <pstade/derived_from.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/pod_constant.hpp>
#include "../by_perfect.hpp"
#include "../config.hpp" // PSTADE_EGG_HAS_FUSIONS
#include "../forward.hpp"

#if defined(PSTADE_EGG_HAS_FUSIONS)
    #include <boost/fusion/include/begin.hpp>
//    #include <boost/fusion/include/boost_tuple.hpp> // broken for now.
    #include <boost/fusion/sequence/intrinsic/end.hpp>
    #include <boost/fusion/include/iterator_range.hpp>
    #include <boost/fusion/include/joint_view.hpp>
    #include <boost/fusion/include/single_view.hpp>
#endif


namespace pstade { namespace egg {


    namespace fusion_prepend_detail {


        namespace here = fusion_prepend_detail;


        template<class Bytag, class Tuple, class A>
        struct tuple_result_of
        {
            typedef
                boost::tuples::cons<
                    typename result_of_forward<Bytag, A>::type,
                    typename boost::remove_cv<Tuple>::type
                >
            type;
        };

        template<class Bytag, class Tuple, class A> inline
        typename tuple_result_of<Bytag, Tuple, A>::type
        tuple_call(Tuple& t, A& a)
        {
            return typename tuple_result_of<Bytag, Tuple, A>::type(a, t);
        }


#if defined(PSTADE_EGG_HAS_FUSIONS)

        template<class Bytag, class Tuple, class A>
        struct fusion_result_of
        {
            typedef
                boost::fusion::single_view<
                    typename result_of_forward<Bytag, A>::type
                > const // const is needed.
            first_view_t;

            typedef
                boost::fusion::iterator_range<
                    typename boost::fusion::result_of::begin<Tuple>::type,
                    typename boost::fusion::result_of::end<Tuple>::type
                > const
            second_view_t;

            typedef
                boost::fusion::joint_view<first_view_t, second_view_t>
            type;
        };

        template<class Bytag, class Tuple, class A> inline
        typename fusion_result_of<Bytag, Tuple, A>::type
        fusion_call(Tuple& t, A& a)
        {
            typedef fusion_result_of<Bytag, Tuple, A> result_;
            return typename result_::type(
                typename result_::first_view_t(a),
                typename result_::second_view_t(boost::fusion::begin(t), boost::fusion::end(t))
            );
        }

#endif


        template<class Bytag>
        struct little
        {
#if defined(PSTADE_EGG_HAS_FUSIONS)
            template<class Me, class Tuple, class A>
            struct apply :
                boost::mpl::eval_if< apple::is_boost_tuple<Tuple>,
                    tuple_result_of<Bytag, Tuple, A>,
                    fusion_result_of<Bytag, Tuple, A>
                >
            { };

            template<class Re, class Tuple, class A>
            Re call(Tuple& t, A& a, typename enable_if< apple::is_boost_tuple<Tuple> >::type = 0) const
            {
                return here::tuple_call<Bytag>(t, a);
            }

            template<class Re, class Tuple, class A>
            Re call(Tuple& t, A& a, typename disable_if<apple::is_boost_tuple<Tuple> >::type = 0) const
            {
                return here::fusion_call<Bytag>(t, a);
            }
#else
            template<class Me, class Tuple, class A>
            struct apply :
                tuple_result_of<Bytag, Tuple, A>
            { };

            template<class Re, class Tuple, class A>
            Re call(Tuple& t, A& a) const
            {
                return here::tuple_call<Bytag>(t, a);
            }
#endif
        };


    } // namespace fusion_prepend_detail


    template<class Bytag = by_perfect>
    struct X_fusion_prepend : derived_from<
        function<fusion_prepend_detail::little<Bytag>, Bytag>
    >
    { };

    typedef X_fusion_prepend<>::base_class T_fusion_prepend;
    PSTADE_POD_CONSTANT((T_fusion_prepend), fusion_prepend) = {{}};


} } // namespace pstade::egg


#endif
