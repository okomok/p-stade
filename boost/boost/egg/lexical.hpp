#ifndef BOOST_EGG_LEXICALIZE_HPP
#define BOOST_EGG_LEXICALIZE_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/lexical_cast.hpp>
#include <boost/egg/ambi.hpp>
#include <boost/egg/by_cref.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/implicit.hpp>


namespace boost { namespace egg {


    template<class To>
    struct X_lexical_cast
    {
        typedef To result_type;

        template<class From>
        To operator()(From const &from) const
        {
            return boost::lexical_cast<To>(from);
        }
    };

    typedef
        result_of_ambi0<
            implicit<X_lexical_cast<mpl::_1>, by_cref>::type,
            by_cref
        >::type
    T_lexical;

    BOOST_EGG_CONST((T_lexical), lexical)
        = BOOST_EGG_AMBI_L BOOST_EGG_IMPLICIT() BOOST_EGG_AMBI_R;


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
