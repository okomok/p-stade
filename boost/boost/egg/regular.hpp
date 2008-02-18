#ifndef BOOST_EGG_REGULAR_HPP
#define BOOST_EGG_REGULAR_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/bll/result_of.hpp> // inclusion guaranteed
#include <boost/egg/by_value.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/detail/derived_from.hpp>
#include <boost/egg/detail/regularized.hpp>
#include <boost/egg/indirect.hpp>
#include <boost/egg/result_of.hpp>


namespace boost { namespace egg {


    namespace regular_detail {


        template<class Strategy>
        struct little
        {
            template<class Me, class Base>
            struct apply :
                result_of_<X_indirect<Strategy>(details::regularized<Base>)>
            { };

            template<class Re, class Base>
            Re call(Base base) const
            {
                return X_indirect<Strategy>()(details::regularized<Base>(base));
            }
        };


    } // namespace regular_detail


    template<class Strategy = use_default>
    struct X_regular : details::derived_from<
        function<regular_detail::little<Strategy>, by_value> >
    { };

    typedef X_regular<>::base_class T_regular;
    BOOST_EGG_CONST((T_regular), regular) = {{}};


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
