#ifndef PSTADE_EGG_BY_PERFECT_BY_PERFECT1_HPP
#define PSTADE_EGG_BY_PERFECT_BY_PERFECT1_HPP
#include "../detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/deduced_const.hpp>
#include "../detail/call_baby.hpp"
#include "../detail/meta_arg.hpp"
#include "../function_fwd.hpp"
#include "../sig_template.hpp"


namespace pstade { namespace egg {


    struct by_perfect1;


    template<class Baby>
    struct function<Baby, by_perfect1>
    {
        typedef function function_type;
        typedef Baby baby_type;

        Baby m_baby;

        Baby baby() const
        {
            return m_baby;
        }

        template<class FunCall>
        struct result;

        // This indirection is needed for msvc ETI.
        template<class A0>
        struct result1 :
            Baby::template apply<Baby, typename detail::meta_arg<A0>::type>
        { };

        template<class Fun,  class A0>
        struct result<Fun(A0)> :
            result1<A0>
        { };

        template<class A0>
        typename result1<A0&>::type
        operator()(A0& a0) const
        {
            return detail::call_baby<Baby, typename result1<A0&>::type>::call(m_baby, a0);
        }

        template<class A0>
        typename result1<PSTADE_DEDUCED_CONST(A0)&>::type
        operator()(A0 const& a0) const
        {
            return detail::call_baby<Baby, typename result1<PSTADE_DEDUCED_CONST(A0)&>::type>::call(m_baby, a0);
        }

        #include PSTADE_EGG_SIG_TEMPLATE()
    };


} } // namespace pstade::egg


#endif
