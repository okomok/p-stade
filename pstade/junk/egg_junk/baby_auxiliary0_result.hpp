#ifndef PSTADE_EGG_DETAIL_BABY_AUXILIARY0_RESULT_HPP
#define PSTADE_EGG_DETAIL_BABY_AUXILIARY0_RESULT_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/utility/result_of.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/deferred.hpp>
#include "../function_fwd.hpp"
#include ".config.hpp" // PSTADE_EGG_MAX_ARITY


namespace pstade { namespace egg { namespace detail {


    template<class UnaryBase>
    struct baby_auxiliary0_result
    {
        UnaryBase m_base;

        typedef UnaryBase base_type;

        UnaryBase base() const
        {
            return m_base;
        }

    // as pipe
        typedef
            function<baby_auxiliary0_result>
        nullary_result_type;

        template<class Result>
        Result call() const
        {
            Result result = { { m_base } };
            return result;
        }

    // as function call
        template<class Myself, class A0>
        struct apply :
            boost::result_of<PSTADE_DEFERRED(UnaryBase const)(A0&)>
        { };

        template<class Result, class A0>
        Result call(A0& a0) const
        {
            return m_base(a0);
        }
    };


    template<class A0, class UnaryBase> inline
    typename boost::result_of<UnaryBase(A0&)>::type
    operator|(A0& a0, function< baby_auxiliary0_result<UnaryBase> > pi)
    {
        return pi.baby().m_base(a0);
    }

    template<class A0, class UnaryBase> inline
    typename boost::result_of<UnaryBase(PSTADE_DEDUCED_CONST(A0)&)>::type
    operator|(A0 const& a0, function< baby_auxiliary0_result<UnaryBase> > pi)
    {
        return pi.baby().m_base(a0);
    }


} } } // namespace pstade::egg::detail


#endif
