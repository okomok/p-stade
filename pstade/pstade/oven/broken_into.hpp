#ifndef PSTADE_OVEN_BROKEN_INTO_HPP
#define PSTADE_OVEN_BROKEN_INTO_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// The name 'tokenized' is reserved by Boost.Regex.


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/token_iterator.hpp>
#include <pstade/callable.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/nonassignable.hpp>
#include <pstade/pass_by.hpp>
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


template< class Type >
struct op_make_broken_into :
    callable< op_make_broken_into<Type> >
{
    template< class Myself, class Range, class TokenizerFun >
    struct apply
    {
        typedef
            boost::token_iterator<
                typename pass_by_value<TokenizerFun>::type,
                typename range_iterator<Range>::type,
                Type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        type;
    };

    template< class Result, class Range, class TokenizerFun >
    Result call(Range& rng, TokenizerFun& fun) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

        typedef typename Result::iterator iter_t;
        return Result(
            iter_t(fun, boost::begin(rng), boost::end(rng)),
            iter_t(fun, boost::end(rng),   boost::end(rng))
        );
    }
};


namespace broken_into_detail_ {


    template< class Type, class TokenizerFun  >
    struct pipe :
        private nonassignable
    {
        explicit pipe(TokenizerFun const& fun) :
            m_fun(fun)
        { }

        TokenizerFun const& m_fun;
    };


    template< class Range, class TokenizerFun, class Type > inline
    typename boost::result_of<op_make_broken_into<Type>(Range&, TokenizerFun const&)>::type
    operator|(Range& rng, pipe<Type, TokenizerFun> const& pi)
    {
        return op_make_broken_into<Type>()(rng, pi.m_fun);
    }

    template< class Range, class TokenizerFun, class Type > inline
    typename boost::result_of<op_make_broken_into<Type>(PSTADE_DEDUCED_CONST(Range)&, TokenizerFun const&)>::type
    operator|(Range const& rng, pipe<Type, TokenizerFun> const& pi)
    {
        return op_make_broken_into<Type>()(rng, pi.m_fun);
    }


} // namespace broken_into_detail_


template< class Type, class TokenizerFun > inline
broken_into_detail_::pipe<Type, TokenizerFun> const
broken_into(TokenizerFun const& fun)
{
    return broken_into_detail_::pipe<Type, TokenizerFun>(fun);
}


} } // namespace pstade::oven


#endif
