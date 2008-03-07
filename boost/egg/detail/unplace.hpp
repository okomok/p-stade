#ifndef BOOST_EGG_DETAIL_UNPLACE_HPP
#define BOOST_EGG_DETAIL_UNPLACE_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/eval_if.hpp>
#include <boost/egg/by_value.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/identity.hpp>
#include <boost/egg/lazy.hpp>
#include <boost/egg/result_of.hpp>
#include <boost/egg/detail/derived_from.hpp>
#include <boost/egg/detail/enable_if.hpp>
#include <boost/egg/detail/is_placeholder.hpp>


namespace boost { namespace egg {


    template<class Bind>
    struct little_unplace
    {
        template<class Fun>
        struct apply_aux :
            result_of_<
                typename result_of_<
                    X_lazy<Bind>(X_identity<by_value>)
                >::type(Fun &)
            >
        { };

        template<class Me, class Fun>
        struct apply :
            mpl::eval_if< is_placeholder_<Fun>,
                apply_aux<Fun>,
                mpl::identity<Fun>
            >
        { };

        template<class Re, class Fun>
        Re call(Fun fun, typename enable_if_< is_placeholder_<Fun> >::type = 0) const
        {
            return X_lazy<Bind>()(X_identity<by_value>())(fun);
        }

        template<class Re, class Fun>
        Re call(Fun fun, typename disable_if_<is_placeholder_<Fun> >::type = 0) const
        {
            return fun;
        }
    };

    template<class Bind = use_default>
    struct X_unplace : details::derived_from<
        function<little_unplace<Bind>, by_value> > 
    { };

    typedef X_unplace<>::base_class T_unplace;
    BOOST_EGG_CONST((T_unplace), unplace) = {{}};


} } // namespace boost::egg


#endif
