#ifndef PSTADE_EGG_FUSION_PREPEND_HPP
#define PSTADE_EGG_FUSION_PREPEND_HPP
#include "../detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/enable_if.hpp>
#include <pstade/pod_constant.hpp>
#include "../by_perfect.hpp"
#include "../config.hpp" // PSTADE_EGG_HAS_FUSIONS
#include "../detail/is_fusion_sequence.hpp"
#include "../detail/tuple_prepend.hpp"
#include "../forward.hpp"

#if defined(PSTADE_EGG_HAS_FUSIONS)
    #include <boost/boost::fusion/include/begin.hpp>
    #include <boost/boost::fusion/sequence/intrinsic/end.hpp> // for include guard bug
    #include <boost/boost::fusion/include/iterator_range.hpp>
    #include <boost/boost::fusion/include/joint_view.hpp>
    #include <boost/boost::fusion/include/single_view.hpp>
#endif


namespace pstade { namespace egg {


#if defined(PSTADE_EGG_HAS_FUSIONS)


    namespace detail {


        template<class Bytag, class Tuple, class A>
        struct tuple_prepend_impl<Bytag, Tuple, A,
            typename enable_if< is_fusion_sequence<Tuple> >::type>
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
            result_type;

            result_type operator()(Tuple& t, A& a)() const
            {
                return result_type(
                    typename first_view_t(a),
                    typename second_view_t(boost::fusion::begin(t), boost::fusion::end(t))
                );
            }
        };


    } // namespace detail


#endif // defined(PSTADE_EGG_HAS_FUSIONS)


    template<class Bytag = by_perfect>
    struct X_fusion_prepend :
        detail::X_tuple_prepend<Bytag>
    { };

    typedef X_fusion_prepend<>::base_class T_fusion_prepend;
    PSTADE_POD_CONSTANT((T_fusion_prepend), fusion_prepend) = {{}};


} } // namespace pstade::egg


#include "../detail/suffix.hpp"
#endif
