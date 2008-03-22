#ifndef BOOST_EGG_DETAIL_LITTLE_OVERLOAD_RESULT_HPP
#define BOOST_EGG_DETAIL_LITTLE_OVERLOAD_RESULT_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/function_types/result_type.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/mpl/placeholders.hpp> // inclusion guaranteed
#include <boost/mpl/transform_view.hpp>
#include <boost/egg/detail/mpl_boost_tuple.hpp>
#include <boost/egg/detail/overload_resolution.hpp>
#include <boost/egg/detail/pod_vector.hpp>
#include <boost/egg/fuse.hpp>
#include <boost/egg/result_of.hpp>
#include <boost/egg/variadic.hpp>


namespace boost { namespace egg {


    namespace overload_detail {


        template<class FunCalls>
        struct little
        {
            typedef typename
                details::pod_vector<
                    typename mpl::transform_view< FunCalls, function_types::result_type<mpl::_> >::type
                >
            bases_type;

            bases_type m_bases;

            template<class Me, class Args>
            struct apply :
                result_of_<
                    typename result_of_<
                        T_fuse(typename details::overload_resolution<FunCalls, Args>::type const &)
                    >::type(Args &)
                >
            { };

            template<class Re, class Args>
            Re call(Args &args) const
            {
                return fuse(
                    m_bases.at_(typename details::overload_resolution_index<FunCalls, Args>::type())
                )(args);
            }
        };


    } // namespace overload_detail


    template<class FunCalls, class Strategy = by_perfect>
    struct result_of_overload :
        variadic<
            overload_detail::little<FunCalls>,
            Strategy,
            use_default,
            typename details::nullary_result_of_overload_resolution<FunCalls>::type
        >
    { };

    #define BOOST_EGG_OVERLOAD_L BOOST_EGG_VARIADIC_L { {
    #define BOOST_EGG_OVERLOAD_R } } BOOST_EGG_VARIADIC_R


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
