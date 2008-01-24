#ifndef PSTADE_EGG_TUPLE_PREPEND_HPP
#define PSTADE_EGG_TUPLE_PREPEND_HPP
#include "../detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/pod_constant.hpp>
#include "../by_perfect.hpp"
#include "../forward.hpp"
#include "./config.hpp"

#if defined(PSTADE_EGG_TUPLE_SUPPORTS_FUSION)
    #include <boost/fusion/include/begin.hpp>
    #include <boost/fusion/include/boost_tuple.hpp>
    #include <boost/fusion/include/end.hpp>
    #include <boost/fusion/include/iterator_range.hpp>
    #include <boost/fusion/include/joint_view.hpp>
    #include <boost/fusion/include/single_view.hpp>
#endif


namespace pstade { namespace egg {


    namespace prepend_detail {


        template<class Bytag>
        struct little
        {
#if defined(PSTADE_EGG_TUPLE_SUPPORTS_FUSION)
            template<class Myself, class Tuple, class A>
            struct apply
            {
                typedef
                    boost::fusion::single_view<
                        typename result_of_forward<Bytag, A>::type
                    >
                first_view_t;

                typedef
                    boost::fusion::iterator_range<
                        typename boost::fusion::result_of::begin<Tuple>::type,
                        typename boost::fusion::result_of::end<Tuple>::type
                    >
                second_view_t;

                typedef
                    boost::fusion::joint_view<first_view_t, second_view_t>
                type;
            };

            template<class Result, class Tuple, class A>
            Result call(Tuple& t, A& a) const
            {
                typedef apply<void, Tuple, A> apply_;
                return Result(
                    typename apply_::first_view_t(a),
                    typename apply_::second_view_t(boost::fusion::begin(t), boost::fusion::end(t))
                );
            }
#else
            template<class Myself, class Tuple, class A>
            struct apply
            {
                typedef
                    boost::tuples::cons<
                        typename result_of_forward<Bytag, A>::type,
                        typename boost::remove_cv<Tuple>::type
                    >
                type;
            };

            template<class Result, class Tuple, class A>
            Result call(Tuple& t, A& a) const
            {
                return Result(a, t);
            }
#endif
        };


    } // namespace prepend_detail


    template<class Bytag = by_perfect>
    struct X_tuple_prepend :
        function<prepend_detail::little<Bytag>, Bytag>
    { };

    typedef X_tuple_prepend<>::function_type T_tuple_prepend;
    PSTADE_POD_CONSTANT((T_tuple_prepend), tuple_prepend) = {{}};


} } // namespace pstade::egg


#endif
