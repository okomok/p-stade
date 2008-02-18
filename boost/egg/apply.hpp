#ifndef BOOST_EGG_APPLY_HPP
#define BOOST_EGG_APPLY_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/by_perfect.hpp>
#include <boost/egg/by_ref.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/detail/adl_barrier.hpp>
#include <boost/egg/detail/derived_from.hpp>
#include <boost/egg/detail/result_of_tuple_get.hpp>
#include <boost/egg/detail/tuple_drop.hpp>
#include <boost/egg/detail/tuple_fuse.hpp>
#include <boost/egg/result_of.hpp>
#include <boost/egg/variadic.hpp>


namespace boost { namespace egg {


    namespace apply_detail {


        struct little
        {
            template<class Me, class Args>
            struct apply :
                result_of<
                    typename result_of<
                        details::T_tuple_fuse(typename details::result_of_tuple_get<0, Args>::type)
                    >::type(typename result_of<details::X_tuple_drop_c<1, by_ref>(Args &)>::type)
                >
            { };

            template<class Re, class Args>
            Re call(Args &args) const
            {
                return details::tuple_fuse(tuples::get<0>(args))
                    (details::X_tuple_drop_c<1, by_ref>()(args));
            }
        };


    } // namespace apply_detail


    template<class Strategy = by_perfect>
    struct X_apply : details::derived_from_eval<
        variadic<apply_detail::little, Strategy> >
    { };

    typedef X_apply<>::base_class T_apply;
BOOST_EGG_ADL_BARRIER(apply) {
    BOOST_EGG_CONST((T_apply), apply) = BOOST_EGG_VARIADIC({});
}


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
