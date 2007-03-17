#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_OVEN_INITIALIZERS_HPP
#define PSTADE_OVEN_INITIALIZERS_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Simpler/faster version of 'boost::assign::cref_list_of'.
// A1-AN must be convertible to A1.


#include <cstddef> // size_t
#include <boost/array.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <pstade/constant.hpp>
#include <pstade/lambda_sig.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/preprocessor.hpp>
#include "./concepts.hpp"
#include "./copy_range.hpp"


#if !defined(PSTADE_OVEN_INITIALIZERS_MAX_ARITY)
    #define PSTADE_OVEN_INITIALIZERS_MAX_ARITY 20
#endif


namespace pstade { namespace oven {


namespace initializers_detail {


    template< class Value, std::size_t N >
    struct return_range
    {
        // Prefer 'boost::array' to built-in array;
        // If 'To' also is 'boost::array', the initialization can be
        // efficient because 'copy_range' can return without assignments.
        boost::array<Value, N> m_array;

        // convertible to CopyableRange
        template< class Range >
        operator Range() const
        {
            PSTADE_CONCEPT_ASSERT((Copyable<Range>));
            return oven::copy_range<Range>(m_array);
        }

    // range implementation
        typedef Value const *iterator;
        typedef iterator     const_iterator;
        typedef std::size_t  size_type;

        iterator begin() const
        {
            return m_array.data();
        }

        iterator end() const
        {
            return m_array.data() + N;
        }

        size_type size() const
        {
            return N;
        }
    };


    // 'return_range' also is CopyableRange.
    template< class Value, std::size_t N, class From > inline
    return_range<Value, N> pstade_oven_copy_range(return_range<Value, N> *&, From& from)
    {
        return_range<Value, N> r = { oven::copy_range< boost::array<Value, N> >(from) };
        return r;
    }


} // namespace initializers_detail


struct op_initializers :
    lambda_sig
{
    template< class FunCall >
    struct result;

    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_OVEN_INITIALIZERS_MAX_ARITY, <pstade/oven/initializers.hpp>))
    #include BOOST_PP_ITERATE()
};


PSTADE_CONSTANT(initializers, (op_initializers))


} } // namespace pstade::oven


#endif
#else
#define n BOOST_PP_ITERATION()


private:
    template< BOOST_PP_ENUM_PARAMS(n, class A) >
    struct BOOST_PP_CAT(result, n)
    {
        typedef
            initializers_detail::return_range<
                typename pass_by_value<A0>::type, n
            > const
        type;
    };

public:
    template< class Fun, BOOST_PP_ENUM_PARAMS(n, class A) >
    struct result<Fun(BOOST_PP_ENUM_PARAMS(n, A))> :
        BOOST_PP_CAT(result, n)<BOOST_PP_ENUM_PARAMS(n, A)>
    { };

    template< BOOST_PP_ENUM_PARAMS(n, class A) >
    typename BOOST_PP_CAT(result, n)<PSTADE_PP_ENUM_PARAMS_WITH(n, A, const&)>::type
    operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, const& a)) const
    {
        typename BOOST_PP_CAT(result, n)<PSTADE_PP_ENUM_PARAMS_WITH(n, A, const&)>::type
            r = { { { BOOST_PP_ENUM_PARAMS(n, a) } } };
        return r;
    }


#undef n
#endif
