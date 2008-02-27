#ifndef BOOST_EGG_ADAPTED_TO_HPP
#define BOOST_EGG_ADAPTED_TO_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// References:
//
// [1] Eric Niebler, iterator_cast, Boost.RangeEx, 2004.
//     http://www.boost-consulting.com/vault/index.php?directory=Algorithms


#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/egg/ambi.hpp>
#include <boost/egg/by_perfect.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/detail/boost_workaround.hpp>
#include <boost/egg/detail/enable_if.hpp>
#include <boost/egg/detail/explicit1.hpp>
#include <boost/egg/detail/is_convertible.hpp>
#include <boost/egg/implicit.hpp>


namespace boost { namespace egg {


    template<class Base>
    struct X_adapted_to
    {
        typedef Base result_type;

        template<class Adapted>
        Base operator()(Adapted &ad,
            typename enable_if_<
#if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
                mpl::and_<
                    is_convertible_<Adapted &, Base>,
                    mpl::not_< is_const<Adapted> >
                >
#else
                is_convertible_<Adapted &, Base>
#endif
            >::type = 0) const
        {
            return ad;
        }

        template<class Adapted>
        Base operator()(Adapted const &ad,
            typename enable_if_< is_convertible_<Adapted const &, Base> >::type = 0) const
        {
            return ad;
        }

        template<class Adapted>
        Base operator()(Adapted const &ad,
            typename disable_if_<is_convertible_<Adapted const &, Base> >::type = 0) const
        {
            return (*this)(ad.base());
        }
    };


    BOOST_EGG_EXPLICIT1(adapted_to, X_adapted_to, (class))


    typedef
        result_of_ambi0<
            implicit<X_adapted_to<mpl::_1>, by_perfect>::type,
            by_perfect
        >::type
    T_to_base;

    BOOST_EGG_CONST((T_to_base), to_base)
        = BOOST_EGG_AMBI_L BOOST_EGG_IMPLICIT() BOOST_EGG_AMBI_R;


    typedef
        result_of_ambi0<
            implicit_ref<X_adapted_to<mpl::_1>, by_perfect>::type,
            by_perfect
        >::type
    T_to_base_ref;

    BOOST_EGG_CONST((T_to_base_ref), to_base_ref)
        = BOOST_EGG_AMBI_L BOOST_EGG_IMPLICIT_REF() BOOST_EGG_AMBI_R;


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
