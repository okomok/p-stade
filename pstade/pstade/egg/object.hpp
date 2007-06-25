#ifndef PSTADE_EGG_OBJECT_HPP
#define PSTADE_EGG_OBJECT_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/placeholders.hpp>
#include <boost/preprocessor/cat.hpp>
#include <pstade/in_unnamed.hpp>
#include <pstade/unparenthesize.hpp>
#include "./detail/config.hpp"

#if !defined(PSTADE_EGG_POD_FUNCTION_IN_VAIN)
    #include "./detail/pod_function.hpp"
#endif


#define PSTADE_EGG_OBJECT(O, F) \
    namespace BOOST_PP_CAT(pstade_egg_object_workarea_of_, O) { \
        using namespace boost::mpl::placeholders; \
        typedef pstade::egg::object_detail::to_pod<PSTADE_UNPARENTHESIZE(F)>::type op; \
    } \
    PSTADE_EGG_OBJECT_def(O, BOOST_PP_CAT(pstade_egg_object_workarea_of_, O)::op) \
/**/

    #define PSTADE_EGG_OBJECT_def(O, F) \
        namespace { \
            PSTADE_IN_UNNAMED F const& O = pstade::egg::object_detail::static_const< F >::value; \
        } \
    /**/


namespace pstade { namespace egg { namespace object_detail {


    template<class T>
    struct static_const
    {
        static T const value;
    };

    // Brace ensures static-initialization (8.5.14).
    template<class T>
    T const static_const<T>::value
#if !defined(PSTADE_EGG_POD_FUNCTION_IN_VAIN)        
        = { };
#else
        = T();
#endif


#if !defined(PSTADE_EGG_POD_FUNCTION_IN_VAIN)
    template<class F>
    struct to_pod
    {
        typedef detail::pod_function<F> type;
    };
#else
    template<class F>
    struct to_pod
    {
        typedef F type;
    };
#endif


} } } // namespace pstade::egg::object_detail


#endif
