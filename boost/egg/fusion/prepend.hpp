#ifndef BOOST_EGG_FUSION_PREPEND_HPP
#define BOOST_EGG_FUSION_PREPEND_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/detail/enable_if.hpp>
#include <boost/egg/by_perfect.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_HAS_FUSIONS
#include <boost/egg/const.hpp>
#include <boost/egg/forward.hpp>
#include <boost/egg/detail/tuple_prepend.hpp>

#if defined(BOOST_EGG_HAS_FUSIONS)
    #include <boost/fusion/include/begin.hpp>
    #include <boost/fusion/sequence/intrinsic/end.hpp> // for include guard bug
    #include <boost/fusion/include/iterator_range.hpp>
    #include <boost/fusion/include/joint_view.hpp>
    #include <boost/fusion/include/single_view.hpp>
    #include <boost/egg/detail/is_fusion_sequence.hpp>
#endif


namespace boost { namespace egg {


#if defined(BOOST_EGG_HAS_FUSIONS)


    namespace details {


        template<class Bytag, class Tuple, class A>
        struct tuple_prepend_impl<Bytag, Tuple, A,
            typename enable_if_< is_fusion_sequence<Tuple> >::type>
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
            result_type;

            result_type operator()(Tuple &t, A &a) const
            {
                return result_type(
                    first_view_t(a),
                    second_view_t(fusion::begin(t), fusion::end(t))
                );
            }
        };


    } // namespace details


#endif // defined(BOOST_EGG_HAS_FUSIONS)


    template<class Bytag = by_perfect>
    struct X_fusion_prepend :
        details::X_tuple_prepend<Bytag>
    { };

    typedef X_fusion_prepend<>::base_class T_fusion_prepend;
    BOOST_EGG_CONST((T_fusion_prepend), fusion_prepend) = {{}};


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
