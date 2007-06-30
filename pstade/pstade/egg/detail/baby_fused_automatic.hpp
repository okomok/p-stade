#ifndef PSTADE_EGG_DETAIL_BABY_FUSED_AUTOMATIC_HPP
#define PSTADE_EGG_DETAIL_BABY_FUSED_AUTOMATIC_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/apply.hpp>
#include <pstade/pass_by.hpp>
#include "../fuse.hpp"


namespace pstade { namespace egg { namespace detail {


    template<class Lambda, class ArgTuple>
    struct automator
    {
        ArgTuple m_args;

        template<class To>
        operator To() const
        {
            typedef typename
                boost::mpl::apply1<Lambda, To>::type
            fun_t;

            return fuse(fun_t())(m_args);
        }
    };


    template<class Lambda>
    struct baby_fused_automatic
    {
        template<class Myself, class ArgTuple>
        struct apply
        {
            typedef
                automator<Lambda, typename pass_by_value<ArgTuple>::type> const
            type;
        };

        template<class Result, class ArgTuple>
        Result call(ArgTuple& args) const
        {
            // 'automator' must *copy* it to 'm_args';
            // 'args' is destructed as soon as this 'call' returns.
            Result result = { args };
            return result;
        }
    };


} } } // namespace pstade::egg::detail


#endif
