#ifndef BOOST_EGG_FUSION_DROP_HPP
#define BOOST_EGG_FUSION_DROP_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/int.hpp>
#include <boost/egg/by_perfect.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_HAS_FUSIONS
#include <boost/egg/detail/const_overloaded.hpp>
#include <boost/egg/detail/enable_if.hpp>
#include <boost/egg/detail/tuple_drop.hpp>

#if defined(BOOST_EGG_HAS_FUSIONS)
    #include <boost/fusion/include/begin.hpp>
    #include <boost/fusion/sequence/intrinsic/end.hpp>
    #include <boost/fusion/include/iterator_range.hpp>
    #include <boost/fusion/include/advance.hpp>
    #include <boost/egg/detail/is_fusion_sequence.hpp>
#endif


namespace boost { namespace egg {


#if defined(BOOST_EGG_HAS_FUSIONS)


    namespace details {


        template<class N, class Tuple>
        struct tuple_drop_impl<N, Tuple,
            typename enable_if_< is_fusion_sequence<Tuple> >::type>
        {
            typedef
                fusion::iterator_range<
                    typename fusion::result_of::advance<
                        typename fusion::result_of::begin<Tuple>::type, N
                    >::type,
                    typename fusion::result_of::end<Tuple>::type
                >
            result_type;

            result_type operator()(Tuple &t) const
            {
                return result_type(
                    fusion::advance<N>(fusion::begin(t)),
                    fusion::end(t)
                );
            }
        };


    } // namespace details


#endif // defined(BOOST_EGG_HAS_FUSIONS)


    template<class N>
    struct X_fusion_drop :
        details::X_tuple_drop<N, by_perfect>
    { };

    template<class N, class Tuple> inline
    typename details::tuple_drop_impl<N, Tuple>::result_type
    fusion_drop(Tuple &t BOOST_EGG_CONST_OVERLOADED(Tuple))
    {
        return X_fusion_drop<N>()(t);
    }

    template<class N, class Tuple> inline
    typename details::tuple_drop_impl<N, Tuple const>::result_type
    fusion_drop(Tuple const &t)
    {
        return X_fusion_drop<N>()(t);
    }


    template<int N>
    struct X_fusion_drop_c :
        X_fusion_drop< mpl::int_<N> >
    { };

    template<int N, class Tuple> inline
    typename details::tuple_drop_impl<mpl::int_<N>, Tuple>::result_type
    fusion_drop_c(Tuple &t BOOST_EGG_CONST_OVERLOADED(Tuple))
    {
        return X_fusion_drop_c<N>()(t);
    }

    template<int N, class Tuple> inline
    typename details::tuple_drop_impl<mpl::int_<N>, Tuple const>::result_type
    fusion_drop_c(Tuple const &t)
    {
        return X_fusion_drop_c<N>()(t);
    }


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
