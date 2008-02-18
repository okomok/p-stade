#ifndef BOOST_EGG_INTEGRAL_HPP
#define BOOST_EGG_INTEGRAL_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/assert.hpp>
#include <boost/numeric/conversion/cast.hpp> // numeric_cast
#include <boost/type_traits/is_integral.hpp>
#include <boost/egg/ambi.hpp>
#include <boost/egg/by_value.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/implicit.hpp>


namespace boost { namespace egg {


    template<class To>
    struct X_integral_cast
    {
        typedef To result_type;

        template<class From>
        To operator()(From from) const
        {
            BOOST_MPL_ASSERT((is_integral<To>));
            BOOST_MPL_ASSERT((is_integral<From>));
            return boost::numeric_cast<To>(from);
        }
    };

    template<class To, class From> inline
    To integral_cast(From from)
    {
        return X_integral_cast<To>()(from);
    }


    typedef result_of_ambi0<implicit<X_integral_cast<mpl::_1>, by_value>::type, by_value>::type T_integral;
    BOOST_EGG_CONST((T_integral), integral) = BOOST_EGG_AMBI_L BOOST_EGG_IMPLICIT() BOOST_EGG_AMBI_R;


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
