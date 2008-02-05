#ifndef PSTADE_EGG_ADAPTED_TO_HPP
#define PSTADE_EGG_ADAPTED_TO_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
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
#include <pstade/boost_workaround.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/is_convertible.hpp>
#include <pstade/pod_constant.hpp>
#include "./ambi.hpp"
#include "./by_perfect.hpp"
#include "./implicit.hpp"
#include "./specified.hpp"


namespace pstade { namespace egg {


    template<class Base>
    struct X_adapted_to
    {
        typedef Base result_type;

        template<class Adapted>
        Base operator()(Adapted& ad,
            typename enable_if<
#if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
                boost::mpl::and_<
                    is_convertible<Adapted&, Base>,
                    boost::mpl::not_< boost::is_const<Adapted> >
                >
#else
                is_convertible<Adapted&, Base>
#endif
            >::type = 0) const
        {
            return ad;
        }

        template<class Adapted>
        Base operator()(Adapted const& ad,
            typename enable_if< is_convertible<Adapted const&, Base> >::type = 0) const
        {
            return ad;
        }

        template<class Adapted>
        Base operator()(Adapted const& ad,
            typename disable_if<is_convertible<Adapted const&, Base> >::type = 0) const
        {
            return (*this)(ad.base());
        }
    };

    #define  PSTADE_EGG_SPECIFIED_PARAMS (adapted_to, X_adapted_to, (class), (1))
    #include PSTADE_EGG_SPECIFIED()


    typedef result_of_ambi0<implicit<X_adapted_to<mpl_1>, by_perfect>::type, by_perfect>::type T_to_base;
    PSTADE_POD_CONSTANT((T_to_base), to_base) = PSTADE_EGG_AMBI_L PSTADE_EGG_IMPLICIT() PSTADE_EGG_AMBI_R;

    typedef result_of_ambi0<implicit_ref<X_adapted_to<mpl_1>, by_perfect>::type, by_perfect>::type T_to_base_ref;
    PSTADE_POD_CONSTANT((T_to_base_ref), to_base_ref) = PSTADE_EGG_AMBI_L PSTADE_EGG_IMPLICIT_REF() PSTADE_EGG_AMBI_R;


} } // namespace pstade::egg


#include "./detail/suffix.hpp"
#endif
