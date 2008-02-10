#ifndef PSTADE_EGG_FUSION_PREPEND_HPP
#define PSTADE_EGG_FUSION_PREPEND_HPP
#include "../detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/derived_from.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/pod_constant.hpp>
#include "../by_perfect.hpp"
#include "../config.hpp" // PSTADE_EGG_HAS_FUSIONS
#include "../detail/tuple_prepend.hpp"
#include "../forward.hpp"

#if defined(PSTADE_EGG_HAS_FUSIONS)
    #include <boost/mpl/eval_if.hpp>
    #include <boost/fusion/include/begin.hpp>
//    #include <boost/fusion/include/boost_tuple.hpp> // broken for now.
    #include <boost/fusion/sequence/intrinsic/end.hpp>
    #include <boost/fusion/include/iterator_range.hpp>
    #include <boost/fusion/include/joint_view.hpp>
    #include <boost/fusion/include/single_view.hpp>
    #include <pstade/apple/is_boost_tuple.hpp>
    #include <pstade/result_of.hpp>
#endif


namespace pstade { namespace egg {


#if defined(PSTADE_EGG_HAS_FUSIONS)

    namespace fusion_prepend_detail {


        namespace here = fusion_prepend_detail;
        namespace fusion = boost::fusion;


        template<class Bytag, class Tuple, class A>
        struct apply_aux
        {
            typedef
                fusion::single_view<
                    typename result_of_forward<Bytag, A>::type
                > const // const is needed.
            first_view_t;

            typedef
                fusion::iterator_range<
                    typename fusion::result_of::begin<Tuple>::type,
                    typename fusion::result_of::end<Tuple>::type
                > const
            second_view_t;

            typedef
                fusion::joint_view<first_view_t, second_view_t>
            type;
        };

        template<class Bytag, class Tuple, class A> inline
        typename apply_aux<Bytag, Tuple, A>::type
        call_aux(Tuple& t, A& a)
        {
            typedef apply_aux<Bytag, Tuple, A> result_;
            return typename result_::type(
                typename result_::first_view_t(a),
                typename result_::second_view_t(fusion::begin(t), fusion::end(t))
            );
        }


        template<class Bytag>
        struct little
        {
            template<class Me, class Tuple, class A>
            struct apply :
                boost::mpl::eval_if< apple::is_boost_tuple<Tuple>,
                    result_of<X_tuple_prepend<Bytag>(Tuple&, A&)>,
                    apply_aux<Bytag, Tuple, A>
                >
            { };

            template<class Re, class Tuple, class A>
            Re call(Tuple& t, A& a, typename enable_if< apple::is_boost_tuple<Tuple> >::type = 0) const
            {
                return X_tuple_prepend<Bytag>()(t, a);
            }

            template<class Re, class Tuple, class A>
            Re call(Tuple& t, A& a, typename disable_if<apple::is_boost_tuple<Tuple> >::type = 0) const
            {
                return here::call_aux<Bytag>(t, a);
            }
        };


    } // namespace fusion_prepend_detail

#endif // defined(PSTADE_EGG_HAS_FUSIONS)


    template<class Bytag = by_perfect>
    struct X_fusion_prepend :
#if defined(PSTADE_EGG_HAS_FUSIONS)
        derived_from< function<fusion_prepend_detail::little<Bytag>, Bytag> >
#else
        detail::X_tuple_prepend<Bytag>
#endif
    { };

    typedef X_fusion_prepend<>::base_class T_fusion_prepend;
    PSTADE_POD_CONSTANT((T_fusion_prepend), fusion_prepend) = {{}};


} } // namespace pstade::egg


#include "../detail/suffix.hpp"
#endif
