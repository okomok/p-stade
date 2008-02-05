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
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <pstade/affect.hpp>
#include <pstade/pod_constant.hpp>
#include "../by_perfect.hpp"
#include "../config.hpp" // PSTADE_EGG_HAS_FUSIONS
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
#endif


namespace pstade { namespace egg {


    namespace fusion_drop_detail {


        namespace here = fusion_drop_detail;


        // drop n xs | n <= 0  = xs
        // drop _ []           = []
        // drop n (_:xs)       = drop (n-1) xs

        template<int N, class Tuple_>
        struct tuple_
        {
            typedef typename Tuple_::tail_type tail_t;

            template<class Tuple>
            struct result_ :
                tuple_<N-1, tail_t>::template result_<typename affect_const<Tuple, tail_t>::type>
            { };

            template<class Tuple>
            static typename result_<Tuple>::type call_(Tuple& t)
            {
                return tuple_<N-1, tail_t>::call_(t.get_tail());
            }
        };

        template<class Tuple_>
        struct tuple_<0, Tuple_>
        {
            template<class Tuple>
            struct result_
            {
                typedef Tuple& type;
            };

            template<class Tuple>
            static Tuple& call_(Tuple& t)
            {
                return t;
            }
        };

        // needed cuz t.get_tail() doesn't return reference when t is one element tuple.
        template< >
        struct tuple_<0, boost::tuples::null_type>
        {
            template<class Tuple>
            struct result_
            {
                typedef boost::tuples::null_type type;
            };

            static boost::tuples::null_type call_(boost::tuples::null_type t)
            {
                return t;
            }
        };

        template<class N, class Tuple>
        struct tuple_result_of :
            tuple_<N::value, typename boost::remove_const<Tuple>::type>::template result_<Tuple>
        { };

        template<class N, class Tuple> inline
        typename tuple_result_of<N, Tuple>::type
        tuple_call(Tuple& t)
        {
            return tuple_<N::value, typename boost::remove_const<Tuple>::type>::call_(t);
        }


#if defined(PSTADE_EGG_HAS_FUSIONS)

        template<class N, class Tuple>
        struct fusion_result_of
        {
            typedef
                boost::fusion::iterator_range<
                    typename boost::fusion::result_of::advance<
                        typename boost::fusion::result_of::begin<Tuple>::type, N
                    >::type,
                    typename boost::fusion::result_of::end<Tuple>::type
                >
            type;
        };

        template<class N, class Tuple> inline
        typename fusion_result_of<N, Tuple>::type
        fusion_call(Tuple& t)
        {
            return typename fusion_result_of<N, Tuple>::type(
                boost::fusion::advance<N>(boost::fusion::begin(t)),
                boost::fusion::end(t)
            );
        }

#endif


        template<class N>
        struct little
        {
#if defined(PSTADE_EGG_HAS_FUSIONS)
            template<class Me, class Tuple>
            struct apply :
                boost::mpl::eval_if< apple::is_boost_tuple<Tuple>,
                    tuple_result_of<N, Tuple>,
                    fusion_result_of<N, Tuple>
                >
            { };

            template<class Re, class Tuple>
            Re call(Tuple& t, typename enable_if< apple::is_boost_tuple<Tuple> >::type = 0) const
            {
                return here::tuple_call<N>(t);
            }

            template<class Re, class Tuple>
            Re call(Tuple& t, typename disable_if<apple::is_boost_tuple<Tuple> >::type = 0) const
            {
                return here::fusion_call<N>(t);
            }
#else
            template<class Me, class Tuple>
            struct apply :
                tuple_result_of<N, Tuple>
            { };

            template<class Re, class Tuple>
            Re call(Tuple& t) const
            {
                return here::tuple_call<N>(t);
            }
#endif
        };


    } // namespace fusion_drop_detail


    template<class N>
    struct X_fusion_drop :
        function<fusion_drop_detail::little<N>, by_perfect>
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
