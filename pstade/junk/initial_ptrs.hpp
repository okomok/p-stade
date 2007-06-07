#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_OVEN_INITIAL_PTRS_HPP
#define PSTADE_OVEN_INITIAL_PTRS_HPP
#include "./prelude.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <memory> // auto_ptr
#include <cstddef> // size_t
#include <boost/array.hpp>
#include <boost/assert.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <pstade/any_movable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/provide_sig.hpp>
#include "./detail/config.hpp"
#include "./detail/indirect_iterator.hpp"


#if !defined(PSTADE_OVEN_INITIAL_PTRS_MAX_ARITY)
    #define PSTADE_OVEN_INITIAL_PTRS_MAX_ARITY 20
#endif


namespace pstade { namespace oven {


namespace initial_ptrs_detail {


    template< class Ptr, std::size_t N >
    struct return_type
    {
        template< class PtrContainer >
        operator std::auto_ptr<PtrContainer>& ()
        {
            return copy<PtrContainer>();
        }

        template< class PtrContainer >
        std::auto_ptr<PtrContainer>& copy()
        {
            BOOST_ASSERT(m_any.empty());

            std::auto_ptr<PtrContainer> r(new PtrContainer());

            for (std::size_t i = 0; i < N; ++i)
                r->push_back(m_ptrs[i]);

            m_any = r;
            return m_any.base< std::auto_ptr<PtrContainer> >();
        }

    // range implementation
        typedef detail::indirect_iterator<Ptr const *> iterator;
        typedef iterator const_iterator;
        typedef std::size_t size_type;

        iterator begin() const
        {
            return iterator(m_ptrs.data());
        }

        iterator end() const
        {
            return iterator(m_ptrs.data() + N);
        }

#if defined(PSTADE_OVEN_BOOST_RANGE_VERSION_1)
        size_type size() const
        {
            return N;
        }
#endif

        explicit return_type(boost::array<Ptr, N>& ptrs) :
            m_ptrs(ptrs)
        { }

    private:  
        boost::array<Ptr, N> m_ptrs;
        any_movable m_any;

        return_type& operator=(return_type const&);
    };


} // namespace initial_ptrs_detail


struct op_initial_ptrs :
    provide_sig
{
    template< class FunCall >
    struct result;

    // 1ary-
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_OVEN_INITIAL_PTRS_MAX_ARITY, <pstade/oven/initial_ptrs.hpp>))
    #include BOOST_PP_ITERATE()
};


PSTADE_CONSTANT(initial_ptrs, (op_initial_ptrs))


} } // namespace pstade::oven


#endif
#else
#define n BOOST_PP_ITERATION()


private:
    template< BOOST_PP_ENUM_PARAMS(n, class A) >
    struct BOOST_PP_CAT(result, n)
    {
        typedef
            initial_ptrs_detail::return_type<typename pass_by_value<A0>::type, n>
        type;
    };

public:
    template< class Fun, BOOST_PP_ENUM_PARAMS(n, class A) >
    struct result<Fun(BOOST_PP_ENUM_PARAMS(n, A))> :
        BOOST_PP_CAT(result, n)<BOOST_PP_ENUM_PARAMS(n, A)>
    { };

    template< BOOST_PP_ENUM_PARAMS(n, class A) >
    typename BOOST_PP_CAT(result, n)<BOOST_PP_ENUM_PARAMS(n, A)>::type
    operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, a)) const
    {
        boost::array<A0, n> ptrs = { { BOOST_PP_ENUM_PARAMS(n, a) } };
        initial_ptrs_detail::return_type<A0, n> r(ptrs);
        return r;
    }


#undef n
#endif
