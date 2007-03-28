#ifndef PSTADE_POSSIBLE_LOSS_CAST_HPP
#define PSTADE_POSSIBLE_LOSS_CAST_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/or.hpp>
#include <boost/numeric/conversion/cast.hpp> // numeric_cast
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <pstade/cast_function.hpp>


namespace pstade {


    namespace possible_loss_cast_detail {


        // Prefer "explicit test" to 'is_convertible<T, int>';
        // the convertibility of user defined types is not stable.
        template<class T>
        struct is_numeric :
            boost::mpl::or_<
                boost::is_floating_point<T>,
                boost::is_integral<T>
            >
        { };


    } // namespace possible_loss_cast_detail 


    template<class To>
    struct op_possible_loss_cast
    {
        typedef To result_type;

        template<class From>
        To aux(From const& from, boost::mpl::true_) const
        {
        #if !defined(NDEBUG)
            return boost::numeric_cast<To>(from);
        #else
            return static_cast<To>(from); // suppress the warning!
        #endif
        }

        template<class From>
        To aux(From const& from, boost::mpl::false_) const
        {
            return from;
        }

        template<class From>
        To operator()(From const& from) const
        {
            typedef boost::mpl::and_<
                possible_loss_cast_detail::is_numeric<To>,
                possible_loss_cast_detail::is_numeric<From>
            >  is_cast;
            return aux(from, boost::mpl::bool_<is_cast::value>());
        }
    };


    PSTADE_CAST_FUNCTION1(possible_loss_cast, op_possible_loss_cast, 1)


} // namespace pstade


#endif
