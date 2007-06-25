#ifndef PSTADE_COMPOSE_HPP
#define PSTADE_COMPOSE_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Ironically, an implementation using preprocessor
// would be shorter and faster than this "beautiful" one.


#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/deferred.hpp>
#include <pstade/fuse.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/unfuse.hpp>


namespace pstade {


    namespace compose_detail {


        template<class F, class G>
        struct fused_return_op :
            callable< fused_return_op<F, G> >
        {
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

            fused_return_op()
            { }

            fused_return_op(F f, G g) :
                m_f(f), m_g(g)
            { }

        private:
            F m_f; G m_g;
        };


    } // namespace compose_detail


    // The nullary result type must be explicitly specified.
    // 'result_of<F(result_of<G()>::type)>::type' is always instantiated,
    // but it may be ill-formed, if 'result_of<G()>::type' is 'void', or
    // an invalid type like 'tuples::null_type' which Boost.Lambda returns instead of 'void'.
    // If such an invalid type is always 'void', then 'result_of<F()>::type' is always well-formed.
    // But, it is not a general solution. "compose2" to call 'f(g1, g2)' would be ill-formed after all.

    template<class NullaryResult = boost::use_default>
    struct op_compose :
        callable< op_compose<NullaryResult> >
    {
        template<class Myself, class F, class G>
        struct apply :
            boost::result_of<
                op_unfuse<NullaryResult>(
                    compose_detail::fused_return_op<typename pass_by_value<F>::type, typename pass_by_value<G>::type>
                )
            >
        { };

        template<class Result, class F, class G>
        Result call(F f, G g) const
        {
            return
                op_unfuse<NullaryResult>()(
                    compose_detail::fused_return_op<F, G>(f, g)
                );
        }
    };


    PSTADE_CONSTANT(compose, (op_compose<>))


} // namespace pstade


#endif
