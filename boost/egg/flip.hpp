#ifndef BOOST_EGG_FLIP_HPP
#define BOOST_EGG_FLIP_HPP
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
#include <boost/egg/construct_braced2.hpp>
#include <boost/egg/detail/derived_from.hpp>
#include <boost/egg/forward.hpp>
#include <boost/egg/generator.hpp>
#include <boost/egg/result_of.hpp>


namespace boost { namespace egg {


    namespace flip_detail {


        template<class Base, class Strategy>
        struct little_result
        {
            Base m_base;

            Base const &base() const
            {
                return m_base;
            }

            template<class Me, class A0, class A1>
            struct apply :
                result_of<
                    Base const(
                        typename result_of_forwarding<Strategy, 2, 1, A1>::type,
                        typename result_of_forwarding<Strategy, 2, 0, A0>::type
                    )
                >
            { };

            template<class Re, class A0, class A1>
            Re call(A0 &a0, A1 &a1) const
            {
                return m_base(
                    egg::forwarding<Strategy, 2, 1>(a1),
                    egg::forwarding<Strategy, 2, 0>(a0)
                );
            }
        };


    } // namespace flip_detail


    template<class BinaryBase, class Strategy = by_perfect>
    struct result_of_flip
    {
        typedef function<flip_detail::little_result<BinaryBase, Strategy>, Strategy> type;
    };

    #define BOOST_EGG_FLIP_L { {
    #define BOOST_EGG_FLIP_R } }
    #define BOOST_EGG_FLIP(F) BOOST_EGG_FLIP_L F BOOST_EGG_FLIP_R


    template<class Strategy = by_perfect>
    struct X_flip : details::derived_from_eval<
        generator<
            typename result_of_flip<deduce<mpl::_1, as_value>, Strategy>::type,
            by_value,
            X_construct_braced2<>
        > >
    { };

    typedef X_flip<>::base_class T_flip;
    BOOST_EGG_CONST((T_flip), flip) = BOOST_EGG_GENERATOR();


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
