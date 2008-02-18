#ifndef BOOST_EGG_NOT_HPP
#define BOOST_EGG_NOT_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/by_perfect.hpp>
#include <boost/egg/by_value.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/construct_unfused1.hpp>
#include <boost/egg/detail/derived_from.hpp>
#include <boost/egg/detail/tuple_fuse.hpp>
#include <boost/egg/generator.hpp>
#include <boost/egg/return.hpp>
#include <boost/egg/unfuse.hpp>


namespace boost { namespace egg {


    namespace not_detail {


        template<class Base>
        struct fused_result
        {
            Base m_base;

            Base const &base() const
            {
                return m_base;
            }

            typedef bool result_type;

            template<class Args>
            result_type operator()(Args const &args) const
            {
                return !details::tuple_fuse(egg::return_<bool>(m_base))(args);
            }
        };


    } // namespace not_detail


    template<class Base, class Strategy = by_perfect>
    struct result_of_not :
        result_of_unfuse<
            not_detail::fused_result<Base>,
            use_nullary_result,
            use_default,
            Strategy
        >
    { };

    #define BOOST_EGG_NOT_L BOOST_EGG_UNFUSE_L {
    #define BOOST_EGG_NOT_R } BOOST_EGG_UNFUSE_R
    #define BOOST_EGG_NOT(F) BOOST_EGG_NOT_L F BOOST_EGG_NOT_R


    template<class Strategy = by_perfect>
    struct X_not : details::derived_from_eval<
        generator<
            typename result_of_not<deduce<mpl::_1, as_value>, Strategy>::type,
            by_value,
            X_construct_unfused1<>
        > >
    { };

    typedef X_not<>::base_class T_not;
    typedef T_not T_not_;
    BOOST_EGG_CONST((T_not_), not_) = BOOST_EGG_GENERATOR();


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
