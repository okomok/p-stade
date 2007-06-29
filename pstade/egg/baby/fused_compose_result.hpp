#ifndef PSTADE_EGG_BABY_FUSED_COMPOSE_RESULT_HPP
#define PSTADE_EGG_BABY_FUSED_COMPOSE_RESULT_HPP
#include "../detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/utility/result_of.hpp>
#include <pstade/deferred.hpp>
#include "../fuse.hpp"


namespace pstade { namespace egg { namespace baby {


    template<class F, class G>
    struct fused_compose_result
    {
        F m_f;
        G m_g;

        template<class Myself, class ArgTuple>
        struct apply :
            boost::result_of<
                PSTADE_DEFERRED(F const)(
                    typename boost::result_of<
                        typename boost::result_of<op_fuse(G const&)>::type(ArgTuple&)
                    >::type
                )
            >
        { };

        template<class Result, class ArgTuple>
        Result call(ArgTuple& args) const
        {
            return m_f(fuse(m_g)(args));
        }
    };


} } } // namespace pstade::egg::baby


#endif
