#ifndef PSTADE_COMPOSE_HPP
#define PSTADE_COMPOSE_HPP


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
#include <pstade/constable.hpp>
#include <pstade/constant.hpp>
#include <pstade/fuse.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include <pstade/unfuse.hpp>


namespace pstade {


    namespace compose_detail {


        template<class F, class G>
        struct fused_return_op :
            callable< fused_return_op<F, G> >
        {
            template<class Myself, class Arguments>
            struct apply :
                boost::result_of<
                    PSTADE_CONSTABLE_TPL(F const)(
                        typename boost::result_of<
                            typename boost::result_of<op_fuse(G const&)>::type(Arguments&)
                        >::type
                    )
                >
            { };

            template<class Result, class Arguments>
            Result call(Arguments& args) const
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


    struct op_compose :
        callable<op_compose>
    {
        template<class Myself, class F, class G>
        struct apply
        {
            typedef
                compose_detail::fused_return_op<
                    typename pass_by_value<F>::type,
                    typename pass_by_value<G>::type
                >
            fused_return_op_t;

            typedef typename
                boost::result_of<op_unfuse(fused_return_op_t)>::type
            type;
        };

        template<class Result, class F, class G>
        Result call(F& f, G& g) const
        {
            typedef typename Result::base_type fused_return_op_t;
            return unfuse(fused_return_op_t(f, g));
        }
    };


    PSTADE_CONSTANT(compose, (op_compose))
    PSTADE_PIPABLE(composed, (op_compose))


} // namespace pstade


#endif
