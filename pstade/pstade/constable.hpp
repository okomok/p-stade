#ifndef PSTADE_CONSTABLE_HPP
#define PSTADE_CONSTABLE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Works around a bug that 'boost::result_of<const function-pointer(..)>' doesn't work.
// If a function object may be a pointer, use 'PSTADE_CONSTABLE(F const)'.


#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/remove_const.hpp>


#if 1
    #define PSTADE_CONSTABLE(F) ::pstade::constable_detail::fix< F >::type
    #define PSTADE_CONSTABLE_TPL typename PSTADE_CONSTABLE
#else
    // Someday...
    #define PSTADE_CONSTABLE(F) F
    #define PSTADE_CONSTABLE_TPL(F) F
#endif


namespace pstade { namespace constable_detail {


    template<class T>
    struct is_pointer :
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400))
        boost::is_pointer<typename boost::remove_const<T>::type>
#else
        boost::is_pointer<T>
#endif
    { };


    template<class F>
    struct fix :
        boost::mpl::eval_if< is_pointer<F>,
            boost::remove_const<F>,
            boost::mpl::identity<F>
        >
    { };


} } // namespace pstade::constable_detail


#endif
