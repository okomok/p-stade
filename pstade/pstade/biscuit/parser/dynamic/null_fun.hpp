#ifndef PSTADE_BISCUIT_PARSER_DYNAMIC_NULL_FUN_HPP
#define PSTADE_BISCUIT_PARSER_DYNAMIC_NULL_FUN_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade { namespace biscuit {


struct null_fun
{
    typedef void result_type;

    template< class A0 >
    void operator()(A0& a0) const
    {
        pstade::unused(a0);
    }

    template< class A0, class A1 >
    void operator()(A0& a0, A1& a1) const
    {
        pstade::unused(a0, a1);
    }

    template< class A0, class A1, class A2 >
    void operator()(A0& a0, A1& a1, A2& a2) const
    {
        pstade::unused(a0, a1, a2);
    }
};


} } // namespace pstade::biscuit


#endif
