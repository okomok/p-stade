#ifndef BOOST_EGG_TO_REF_HPP
#define BOOST_EGG_TO_REF_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/type_traits/remove_cv.hpp>
#include <boost/egg/ambi.hpp>
#include <boost/egg/by_cref.hpp>
#include <boost/egg/by_perfect.hpp>
#include <boost/egg/const.hpp>


namespace boost { namespace egg {


    namespace to_ref_detail {


        struct little
        {
            template<class Me, class X>
            struct apply
            {
                typedef X &type;
            };

            template<class Re, class X>
            Re call(X &x) const
            {
                return x;
            }
        };


        struct clittle
        {
            template<class Me, class X>
            struct apply
            {
                typedef X &type;
            };

            template<class Re, class X>
            Re call(X &x) const
            {
                return x;
            }
        };


        struct mlittle
        {
            template<class Me, class X>
            struct apply
            {
                typedef typename remove_cv<X>::type &type;
            };

            template<class Re, class X>
            Re call(X const &x) const
            {
                return const_cast<X &>(x);
            }
        };


        template<class Little, class Strategy>
        struct ambify :
            result_of_ambi0<function<Little, Strategy>, Strategy>
        { };


    } // namespace to_ref_detail


    typedef to_ref_detail::ambify<to_ref_detail::little, by_perfect>::type T_to_ref;
    typedef to_ref_detail::ambify<to_ref_detail::clittle, by_cref>::type T_to_cref;
    typedef to_ref_detail::ambify<to_ref_detail::mlittle, by_cref>::type T_to_mref;
    BOOST_EGG_CONST((T_to_ref), to_ref) = BOOST_EGG_AMBI({{}});
    BOOST_EGG_CONST((T_to_cref), to_cref) = BOOST_EGG_AMBI({{}});
    BOOST_EGG_CONST((T_to_mref), to_mref) = BOOST_EGG_AMBI({{}});


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
