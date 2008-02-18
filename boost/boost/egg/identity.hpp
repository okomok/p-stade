#ifndef BOOST_EGG_IDENTITY_HPP
#define BOOST_EGG_IDENTITY_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/by_perfect.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/detail/adl_barrier.hpp>
#include <boost/egg/detail/derived_from.hpp>
#include <boost/egg/forward.hpp>


namespace boost { namespace egg {


    namespace identity_detail {


        template<class Strategy>
        struct little
        {
            template<class Me, class X>
            struct apply :
                result_of_forwarding<Strategy const, 1, 0, X>
            { };

            template<class Re, class X>
            Re call(X &x) const
            {
                return egg::forwarding<Strategy const, 1, 0>(x);
            }
        };


    } // namespace identity_detail


    template<class Strategy = by_perfect>
    struct X_identity : details::derived_from<
        function<identity_detail::little<Strategy>, Strategy> >
    { };

    typedef X_identity<>::base_class T_identity;
BOOST_EGG_ADL_BARRIER(identity) {
    BOOST_EGG_CONST((T_identity), identity) = {{}};
}


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
