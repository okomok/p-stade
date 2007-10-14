#ifndef PSTADE_OVEN_TRANSFORMER_HPP
#define PSTADE_OVEN_TRANSFORMER_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pass_by.hpp>
#include <pstade/result_of.hpp>
#include "./applier.hpp"
#include "./concepts.hpp"
#include "./detail/base_to_adaptor.hpp"


namespace pstade { namespace oven {


namespace transformer_detail {


    template< class Iterator, class UnaryFun >
    struct proc
    {
        Iterator m_it;
        UnaryFun m_fun;

        typedef Iterator base_type;

        Iterator base() const
        {
            return m_it;
        }

        typedef void result_type;

        template< class Value >
        void operator()(Value& v)
        {
            *m_it++ = m_fun(v);
        }
    };


    template< class Iterator, class UnaryFun >
    struct base
    {
        typedef
            proc<
                typename pass_by_value<Iterator>::type,
                typename pass_by_value<UnaryFun>::type
            >
        proc_t;

        typedef typename
            result_of<T_applier(proc_t&)>::type
        result_type;

        result_type operator()(Iterator& it, UnaryFun& fun) const
        {
            PSTADE_CONCEPT_ASSERT((Output<Iterator>));
            proc_t p = {it, fun};
            return applier(p);
        }
    };


} // namespace transformer_detail


PSTADE_OVEN_BASE_TO_ADAPTOR(transformer, (transformer_detail::base<_, _>))


} } // namespace pstade::oven


#endif