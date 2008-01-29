

// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


    typedef ResultType result_type;

    base_type m_base;

    base_type const& base() const
    {
        return m_base;
    }

    template<class U>
    result_type operator()(U const& u BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(n, A, a)) const
    {
        return call_aux(u, &u BOOST_PP_ENUM_TRAILING_PARAMS(n, a));
    }

    template<class U>
    result_type operator()(U& u BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(n, A, a)) const
    {
        return call_aux(u, &u BOOST_PP_ENUM_TRAILING_PARAMS(n, a));
    }

    template<class U>
    result_type call_aux(U& u, T const * BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(n, A, a)) const
    {
        return (u.*m_base)(BOOST_PP_ENUM(n, PSTADE_forward, ~));
    }

    template<class U>
    result_type call_aux(U& u, void const * BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(n, A, a)) const
    {
        PSTADE_EGG_GET_POINTER_PREAMBLE()
        return (get_pointer(u)->*m_base)(BOOST_PP_ENUM(n, PSTADE_forward, ~));
    }

