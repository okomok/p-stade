#ifndef PSTADE_BISCUIT_RANGE_TOKEN_RANGE_HPP
#define PSTADE_BISCUIT_RANGE_TOKEN_RANGE_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp> // BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE, BOOST_EXPLICIT_TEMPLATE_TYPE
#include <boost/range/result_iterator.hpp>
#include <boost/type_traits/add_const.hpp>
#include <pstade/const_overloaded.hpp>
#include <pstade/nonassignable.hpp>
#include <pstade/oven/as_lightweight_proxy.hpp>
#include "../state/null_state.hpp"
#include "./token_iterator.hpp"


namespace pstade { namespace biscuit {


template< class Parser, class ForwardRange, class UserState >
struct token_range;


namespace token_range_detail {


    template< class Parser, class ForwardRange, class UserState >
    struct super_
    {
        typedef boost::iterator_range<
            token_iterator<
                Parser,
                typename boost::range_result_iterator<ForwardRange>::type,
                UserState
            >
        > type;
    };


} // namespace token_range_detail


template< class Parser, class ForwardRange, class UserState = null_state_type >
struct token_range :
    token_range_detail::super_<Parser, ForwardRange, UserState>::type,
    private oven::as_lightweight_proxy< token_range<Parser, ForwardRange, UserState> >
{
private:
    typedef typename token_range_detail::super_<Parser, ForwardRange, UserState>::type super_t;

public:
    explicit token_range(ForwardRange& r, UserState& us = null_state) :
        super_t(
            biscuit::make_token_iterator<Parser>(boost::begin(r), boost::end(r), us),
            biscuit::make_token_iterator<Parser>(boost::end(r),   boost::end(r), us)
        )
    { }
};


template< class Parser, class ForwardRange, class UserState > inline
typename const_overloaded<token_range<Parser, ForwardRange, UserState>, ForwardRange>::type const
make_token_range(ForwardRange& r, UserState& us BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
{
    return token_range<Parser, ForwardRange, UserState>(r, us);
}

    template< class Parser, class ForwardRange, class UserState > inline
    token_range<Parser, typename boost::add_const<ForwardRange>::type, UserState> const
    make_token_range(ForwardRange const& r, UserState& us BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
    {
        return token_range<Parser, typename boost::add_const<ForwardRange>::type, UserState>(r, us);
    }


// no user-state
template< class Parser, class ForwardRange > inline
typename const_overloaded<token_range<Parser, ForwardRange>, ForwardRange>::type const
make_token_range(ForwardRange& r BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
{
    return token_range<Parser, ForwardRange>(r);
}

    template< class Parser, class ForwardRange > inline
    token_range<Parser, typename boost::add_const<ForwardRange>::type> const
    make_token_range(ForwardRange const& r BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
    {
        return token_range<Parser, typename boost::add_const<ForwardRange>::type>(r);
    }


namespace token_range_detail {


    template< class Parser, class UserState >
    struct pipe :
        private nonassignable
    {
        explicit pipe(UserState& us) :
            m_us(us)
        { }

        UserState& m_us;
    };


    template< class Parser, class ForwardRange, class UserState > inline
    token_range<Parser, ForwardRange, UserState> const
    operator|(ForwardRange& rng, pipe<Parser, UserState> const& pi)
    {
        return biscuit::make_token_range<Parser>(rng, pi.m_us);
    }

        template< class Parser, class ForwardRange, class UserState > inline
        token_range<Parser, typename boost::add_const<ForwardRange>::type, UserState> const
        operator|(ForwardRange const& rng, pipe<Parser, UserState> const& pi)
        {
            return biscuit::make_token_range<Parser>(rng, pi.m_us);
        }


} // namespace token_range_detail


template< class Parser, class UserState > inline
token_range_detail::pipe<Parser, UserState> const
tokenized(UserState& us BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
{
    return token_range_detail::pipe<Parser, UserState>(us);
}

// no user-state
template< class Parser > inline
token_range_detail::pipe<Parser, null_state_type> const
tokenized(BOOST_EXPLICIT_TEMPLATE_TYPE(Parser))
{
    return token_range_detail::pipe<Parser, null_state_type>(null_state);
}


} } // namespace pstade::biscuit


#endif
