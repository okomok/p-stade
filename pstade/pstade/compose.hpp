#ifndef PSTADE_COMPOSE_HPP
#define PSTADE_COMPOSE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/utility/result_of.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include <pstade/tupled.hpp>
#include <pstade/untupled.hpp>


namespace pstade {


    namespace compose_detail {


        template< class F, class G >
        struct baby_base
        {
            template< class Myself, class Arguments >
            struct apply
            {
                typedef typename
                    boost::result_of<tupled_fun(G&)>::type
                tg_t;

                typedef typename
                    boost::result_of<tg_t(Arguments&)>::type
                result_of_tg;

                typedef typename
                    boost::result_of<F(result_of_tg)>::type
                type;
            };

            template< class Result, class Arguments >
            Result call(Arguments& args) const
            {
                return m_f( pstade::tupled(m_g)(args) );
            }

            explicit baby_base() // DefaultConstructible iff 'F' and 'G' is.
            { }

            explicit baby_base(F const& f, G const& g) :
                m_f(f), m_g(g)
            { }

        private:
            mutable F m_f;
            G m_g;
        };


        struct baby
        {
            template< class Myself, class F, class G >
            struct apply
            {
                typedef
                    egg::function<
                        baby_base<
                            typename pass_by_value<F>::type,
                            typename pass_by_value<G>::type
                        >
                    >
                base_t;

                typedef typename
                    boost::result_of<untupled_fun(base_t)>::type
                type;
            };

            template< class Result, class F, class G >
            Result call(F& f, G& g) const
            {
                typedef typename Result::base_type base_t;
                return pstade::untupled(base_t(f, g));
            }
        };


    } // namespace compose_detail


    PSTADE_EGG_FUNCTION(compose, compose_detail::baby)
    PSTADE_PIPABLE(composed, compose_fun)


} // namespace pstade


#endif
