#ifndef PSTADE_DETAIL_POINTER_CAST_HPP
#define PSTADE_DETAIL_POINTER_CAST_HPP
#include "./prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/utility/addressof.hpp>
#include <pstade/boost_workaround.hpp>
#include <pstade/egg/static_downcast.hpp>

#if BOOST_WORKAROUND(__GNUC__, == 3)
    #include <boost/type_traits/is_same.hpp>
    #include <boost/type_traits/remove_cv.hpp>
    #include <pstade/enable_if.hpp>
#endif


namespace pstade { namespace detail_ {


    template<class To, class From> inline
    To *pointer_cast(From *p
#if BOOST_WORKAROUND(__GNUC__, == 3)
        , typename disable_if< boost::is_same<typename boost::remove_cv<From>::type, void> >::type = 0
#endif
    )
    {
        return boost::addressof( egg::static_downcast<To>(*p) );
    }

    template<class To> inline
    To *pointer_cast(void *p)
    {
        return static_cast<To *>(p);
    }

    template<class To> inline
    To *pointer_cast(void const *p)
    {
        return static_cast<To *>(p);
    }

    template<class To> inline
    To *pointer_cast(void volatile *p)
    {
        return static_cast<To *>(p);
    }

    template<class To> inline
    To *pointer_cast(void const volatile *p)
    {
        return static_cast<To *>(p);
    }


} } // namespace pstade::detail_


#endif
