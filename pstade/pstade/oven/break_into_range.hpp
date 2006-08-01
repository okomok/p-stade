#ifndef PSTADE_OVEN_BREAK_INTO_RANGE_HPP
#define PSTADE_OVEN_BREAK_INTO_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// The name 'tokenized' is reserved by Boost.Regex.


#include <string>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/token_iterator.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/utility/addressof.hpp>
#include <pstade/const_overloaded.hpp>
#include "./detail/concept_check.hpp"
#include "./lightweight_proxy.hpp"
#include "./range_iterator.hpp"
#include "./range_value.hpp"



namespace pstade { namespace oven {


namespace break_into_range_detail {


    template<
        class Range,
        class TokenizerFun,
        class Type
    >
    struct super_
    {
        typedef boost::iterator_range<
            boost::token_iterator<
                TokenizerFun,
                typename range_iterator<Range>::type,
                Type
            >
        > type;
    };


} // namespace break_into_range_detail


template<
    class Range,
    class TokenizerFun = boost::char_delimiters_separator<char>,
    class Type = std::string
>
struct break_into_range :
    break_into_range_detail::super_<Range, TokenizerFun, Type>::type,
    private lightweight_proxy< break_into_range<Range, TokenizerFun, Type> >
{
    typedef Range pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(Range, SinglePassRangeConcept);
    typedef typename break_into_range_detail::super_<Range, TokenizerFun, Type>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    break_into_range(Range& rng, TokenizerFun const& fun = TokenizerFun()) :
        super_t(
            iter_t(fun, boost::begin(rng), boost::end(rng)),
            iter_t(fun, boost::end(rng),   boost::end(rng))
        )
    { }
};


// generators
//

template< class Type, class Range, class TokenizerFun > inline
typename const_overloaded<break_into_range<Range, TokenizerFun, Type>, Range>::type const
make_break_into_range(Range& rng, TokenizerFun const& fun)
{
    return break_into_range<Range, TokenizerFun, Type>(rng, fun);
}


template< class Type, class Range, class TokenizerFun > inline
break_into_range<typename boost::add_const<Range>::type, TokenizerFun, Type> const
make_break_into_range(Range const& rng, TokenizerFun const& fun)
{
    return break_into_range<typename boost::add_const<Range>::type, TokenizerFun, Type>(rng, fun);
}


namespace break_into_range_detail {


    template< class Type, class TokenizerFun >
    struct adaptor
    {
        explicit adaptor(TokenizerFun const& fun) :
            m_pfun(boost::addressof(fun))
        { }

        TokenizerFun const *m_pfun;
    };


    template< class Range, class TokenizerFun, class Type > inline
    break_into_range<Range, TokenizerFun, Type> const
    operator|(Range& rng, adaptor<Type, TokenizerFun> const& ad)
    {
        return break_into_range<Range, TokenizerFun, Type>(rng, *ad.m_pfun);
    }


    template< class Range, class TokenizerFun, class Type > inline
    break_into_range<typename boost::add_const<Range>::type, TokenizerFun, Type> const
    operator|(Range const& rng, adaptor<Type, TokenizerFun> const& ad)
    {
        return break_into_range<typename boost::add_const<Range>::type, TokenizerFun, Type>(rng, *ad.m_pfun);
    }


} // namespace break_into_range_detail


template< class Type, class TokenizerFun > inline
break_into_range_detail::adaptor<Type, TokenizerFun> const
broken_into(TokenizerFun const& fun)
{
    return break_into_range_detail::adaptor<Type, TokenizerFun>(fun);
}


} } // namespace pstade::oven


#endif
