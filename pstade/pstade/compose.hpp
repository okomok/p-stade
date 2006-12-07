#ifndef PSTADE_COMPOSE_HPP
#define PSTADE_COMPOSE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include <pstade/singleton.hpp>
#include <pstade/tupled.hpp>
#include <pstade/untupled.hpp>


namespace pstade {


    namespace compose_detail {


        template< class F, class G >
        struct base_op_result :
            callable< base_op_result<F, G> >
        {
            template< class Myself, class Arguments >
            struct apply
            {
                typedef typename
                    boost::result_of<op_tupled(G&)>::type
                tupled_g;

                typedef typename
                    boost::result_of<tupled_g(Arguments&)>::type
                result_of_tupled_g;

                typedef typename
                    boost::result_of<F(result_of_tupled_g)>::type
                type;
            };

            template< class Result, class Arguments >
            Result call(Arguments& args) const
            {
                return m_f( pstade::tupled(m_g)(args) );
            }

            explicit base_op_result() // DefaultConstructible iff 'F' and 'G' are.
            { }

            explicit base_op_result(F const& f, G const& g) :
                m_f(f), m_g(g)
            { }

        private:
            F m_f;
            G m_g;
        };


    } // namespace compose_detail


    struct op_compose
    {
        template< class Signature >
        struct result;

        template< class Self, class F, class G >
        struct result<Self(F, G)>
        {
            typedef
                compose_detail::base_op_result<
                    typename pass_by_value<F>::type,
                    typename pass_by_value<G>::type
                >
            base_t;

            typedef typename
                boost::result_of<op_untupled(base_t)>::type
            type;
        };

        template< class F, class G >
        typename result<int(F, G)>::type operator()(F f, G g) const
        {
            typedef typename result<int(F, G)>::base_t base_t;
            return pstade::untupled(base_t(f, g));
        }
    };


    PSTADE_SINGLETON_CONST(compose, op_compose)
    PSTADE_PIPABLE(composed, op_compose)


} // namespace pstade


#endif
