#ifndef PSTADE_BISCUIT_PARSER_DYNAMIC_IDENTITY_FUN_HPP
#define PSTADE_BISCUIT_PARSER_DYNAMIC_IDENTITY_FUN_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade { namespace biscuit {


struct identity_fun
{
    template< class T >
    T& operator()(T& x) const
    {
        return x;
    }

    template< class T >
    T const& operator()(T const& x) const
    {
        return x;
    }
};


} } // namespace pstade::biscuit


#endif
