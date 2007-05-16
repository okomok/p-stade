#ifndef PSTADE_CROSSCAST_HPP
#define PSTADE_CROSSCAST_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/cast.hpp> // polymorphic_cast
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/addressof.hpp>
#include <pstade/affect.hpp>
#include <pstade/callable.hpp>
#include <pstade/specified.hpp>


namespace pstade {


    namespace crosscast_detail {


        template<class Reference>
        struct to_pointer
        {
            typedef typename
                boost::remove_reference<Reference>::type *
            type;
        };


    } // namespace crosscast_detail


    template<class To>
    struct op_polymorphic_downcast :
        callable< op_polymorphic_downcast<To> >
    {
        template<class Myself, class From>
        struct apply :
            affect<From&, To>
        { };

        template<class Result, class From>
        Result call(From& base) const
        {
            BOOST_MPL_ASSERT_NOT((boost::is_base_of<
                typename boost::remove_cv<From>::type,
                typename boost::remove_cv<To>::type
            >));

            BOOST_MPL_ASSERT_NOT((boost::is_base_of<
                typename boost::remove_cv<From>::type,
                typename boost::remove_cv<To>::type
            >));

            return *boost::polymorphic_cast<
                typename crosscast_detail::to_pointer<Result>::type
            >(boost::addressof(base));
        }
    };


    PSTADE_SPECIFIED1(crosscast, op_crosscast, 1)


} // namespace pstade


#endif
