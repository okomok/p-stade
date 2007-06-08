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
#include <boost/mpl/identity.hpp>
#include <boost/pointee.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <pstade/any_movable.hpp>
#include <pstade/constant.hpp>
#include <pstade/new_delete.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/provide_sig.hpp>
#include <pstade/use_default.hpp>
#include "./detail/config.hpp"
#include "./detail/indirect_iterator.hpp"


#if !defined(PSTADE_OVEN_INITIAL_PTRS_MAX_ARITY)
    #define PSTADE_OVEN_INITIAL_PTRS_MAX_ARITY 20
#endif


namespace pstade { namespace oven {


namespace initial_ptrs_detail {


    namespace here = initial_ptrs_detail;


    template< class AutoPtr, std::size_t N >
    struct return_range
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
                r->insert(r->end(), m_ptrs[i]);

            m_any = r;
            return m_any.base< std::auto_ptr<PtrContainer> >();
        }

        typedef boost::array<AutoPtr, N> array_type;

        explicit return_range(array_type& ptrs) :
            m_ptrs(ptrs)
        { }

    private:
        array_type m_ptrs;
        any_movable m_any;

    public:
    // range implementation
        typedef detail::indirect_iterator<AutoPtr const *> iterator;
        typedef iterator    const_iterator;
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

    private:
        return_range(return_range const&);
        return_range& operator=(return_range const&);
    };


    template< class Ptr >
    struct result_of_to_auto_ptr
    {
        typedef 
            std::auto_ptr<
                typename boost::pointee<typename pass_by_value<Ptr>::type>::type
            >
        type;
    };

    // Pass by reference for lvalue of 'move_ptr'.
    // Also note 'auto_ptr' isn't copy-initializable from one which has
    // a different 'element_type'. See http://tinyurl.com/yo8a7w (defect report #84)
    template< class To, class From > inline
    To to_auto_ptr(From& from)
    {
        return To(from.release());
    }


} // namespace initial_ptrs_detail


template< class Value = boost::use_default >
struct op_initial_ptrs :
    provide_sig
{
    template< class FunCall >
    struct result;

    template< class A >
    struct auto_ptr_of :
        eval_if_use_default< Value,
            initial_ptrs_detail::result_of_to_auto_ptr<A>,
            boost::mpl::identity< std::auto_ptr<Value> >
        >
    { };

    // 1ary-
#define PSTADE_to_ap(Z, N, _) initial_ptrs_detail::to_auto_ptr<typename auto_ptr_of<A0>::type>(BOOST_PP_CAT(a, N))
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_OVEN_INITIAL_PTRS_MAX_ARITY, <pstade/oven/initial_ptrs.hpp>))
    #include BOOST_PP_ITERATE()
#undef  PSTADE_to_ap
};


PSTADE_CONSTANT(initial_ptrs, (op_initial_ptrs<>))


template< class Value, std::size_t N >
struct result_of_initial_ptrs
{
    typedef
        std::auto_ptr<
            initial_ptrs_detail::return_range<
                std::auto_ptr<Value>, N
            >
        >
    type;
};


using pstade::op_new_auto;


} } // namespace pstade::oven


#endif
#else
#define n BOOST_PP_ITERATION()


private:
    template< BOOST_PP_ENUM_PARAMS(n, class A) >
    struct BOOST_PP_CAT(result, n)
    {
        typedef
            initial_ptrs_detail::return_range<typename auto_ptr_of<A0>::type, n>
        rng_t;

        typedef
            std::auto_ptr<rng_t>
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
        typedef initial_ptrs_detail::return_range<typename auto_ptr_of<A0>::type, n> rng_t;
        typename rng_t::array_type ptrs = { { BOOST_PP_ENUM(n, PSTADE_to_ap, ~) } };
        return std::auto_ptr<rng_t>(new rng_t(ptrs));
    }


#undef n
#endif
