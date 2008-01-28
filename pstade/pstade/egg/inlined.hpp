#ifndef PSTADE_EGG_INLINED_HPP
#define PSTADE_EGG_INLINED_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// References:
//
// [1] http://d.hatena.ne.jp/Cryolite/01000831
// [2] http://ubiety.uwaterloo.ca/~tveldhui/papers/techniques/techniques01.html#index00030


// Note:
//
// Function reference doesn't work with gcc-4.1.
// PSTADE_EGG_INLINE can't support dependent names.


#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <pstade/boost_workaround.hpp>
#include <pstade/dont_care.hpp>
#include <pstade/pod_constant.hpp>
#include "./detail/little_inlined.hpp"
#include "./detail/little_inlined_mem.hpp"
#include "./by_perfect.hpp"
#include "./by_value.hpp"
#include "./generator.hpp"


#if BOOST_WORKAROUND(BOOST_MSVC, < 1500)

    #define PSTADE_EGG_INLINE_WORKAROUND

    #include <boost/typeof/typeof.hpp>

    #if defined(BOOST_TYPEOF_EMULATION)
        #include "./return.hpp"
    #else
        #define PSTADE_EGG_INLINE_WORKAROUND_TYPEOF
    #endif

#endif


namespace pstade { namespace egg {


    template<class Ptr, Ptr ptr, class Strategy = by_perfect>
    struct inlined :
        boost::mpl::if_< boost::is_pointer<Ptr>,
            function<detail::little_inlined<Ptr, ptr, Strategy>, Strategy>,
            function<detail::little_inlined_mem<Ptr, ptr, Strategy>, Strategy>
        >
    { };

    #define PSTADE_EGG_INLINED() {{}}


    namespace inline_detail {


        template<class Ptr, class Strategy>
        struct result_
        {
            template<Ptr ptr>
            typename inlined<Ptr, ptr, Strategy>::type of() const
            {
                typename inlined<Ptr, ptr, Strategy>::type r = PSTADE_EGG_INLINED();
                return r;
            }

            explicit result_(dont_care = 0)
            { }
        };


        template<class F>
        F decay(F);


    } // namespace inline_detail


    template<class Strategy = by_perfect>
    struct X_inline :
        generator<
            inline_detail::result_<deduce<mpl_1, as_value>, Strategy>,
            by_value
        >::type
    { };

    typedef X_inline<>::function_type T_inline;
    typedef T_inline T_inline_;
    PSTADE_POD_CONSTANT((T_inline_), inline_) = PSTADE_EGG_GENERATOR();


#if !defined(PSTADE_EGG_INLINE_WORKAROUND)
    #define PSTADE_EGG_INLINE(F) pstade::egg::inline_(F).of< F >()
    #define PSTADE_EGG_INLINE_BY(F, Stg) pstade::egg::X_inline< Stg >()(F).of< F >()
#elif defined(PSTADE_EGG_INLINE_WORKAROUND_TYPEOF)
    #define PSTADE_EGG_INLINE(F) pstade::egg::inlined<BOOST_TYPEOF(pstade::egg::inline_detail::decay(F)), F>::type()
    #define PSTADE_EGG_INLINE_BY(F, Stg) pstade::egg::inlined<BOOST_TYPEOF(pstade::egg::inline_detail::decay(F)), F, Stg>::type()
#else
    #define PSTADE_EGG_INLINE(F) (F)
    #define PSTADE_EGG_INLINE_BY(F, Stg) pstade::egg::X_return<boost::use_default, Stg>()(F)
#endif


} } // namespace pstade::egg


#endif
