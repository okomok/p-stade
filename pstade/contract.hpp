#ifndef PSTADE_CONTRACT_HPP
#define PSTADE_CONTRACT_HPP
#include "./prelude.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Emulates the proposal;
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n1962.html


// Note:
//
// ADL extension which would enable 'assert(invariant(someHandle));'
// is not so useful as expected. Scattering 'assert' seems to be anti-pattern.
//
// Note that 'private' nested 'typedef' cannot be used with SFINAE.
// http://groups.google.com/group/comp.lang.c++.moderated/msg/84fe1563ccc65846


#include <boost/any.hpp>
#include <boost/assert.hpp>
#include <boost/mpl/aux_/preprocessor/is_seq.hpp>
#include <boost/mpl/aux_/preprocessor/token_equal.hpp>
#include <boost/noncopyable.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/utility/addressof.hpp>
#include <pstade/for_debug.hpp>
#include <pstade/nonconstructible.hpp>
#include <pstade/nullptr.hpp>
#include <pstade/unused.hpp>


namespace pstade {


class contract_access :
    private nonconstructible
{
public:
    template< class T > static
    void detail_invariant(T const& x)
    {
        x.pstade_invariant();
    }
};


template< class InvariantAssertable >
bool invariant(InvariantAssertable const& ia)
{
    pstade::for_debug();

    try {
        contract_access::detail_invariant(ia);
    }
    catch (...) {
        BOOST_ASSERT("class invariant is broken." && false);
    }

    return true; // for 'assert'.
}


namespace contract_detail {


    // precondition
    //

    struct invariant_assertable_placeholder
        // is also InvariantAssertable.
    {
        virtual void pstade_invariant() const = 0;
        virtual ~invariant_assertable_placeholder() { }
    };


    template< class InvariantAssertable >
    struct invariant_assertable_holder :
        invariant_assertable_placeholder
    {
        explicit invariant_assertable_holder(InvariantAssertable const& ia) :
            m_ia(ia)
        { }

        virtual void pstade_invariant() const
        {
            pstade::invariant(m_ia);
        }

        InvariantAssertable const& m_ia;
    };


    struct precondition_evaluator :
        private boost::noncopyable
    {
        template< class InvariantAssertable >
        precondition_evaluator(InvariantAssertable const& ia, bool ctor, bool dtor) :
            m_pia(new invariant_assertable_holder<InvariantAssertable>(ia)),
            m_dtor(dtor)
        {
            if (ctor)
                pstade::invariant(*m_pia);
        }

        ~precondition_evaluator()
        {
            if (m_dtor)
                pstade::invariant(*m_pia);
        }

    private:
        boost::scoped_ptr<invariant_assertable_placeholder> m_pia;
        bool m_dtor;
    };


    // postcondition
    //
    // Prefer specialization to metafunction,
    // which needs 'typename' for dependent-name.
    //

    // for value
    template< class Result >
    struct postcondition_result_ptr
    {
        void reset(Result const& x)
        {
            m_ptr.reset(new Result(x));
        }

        bool operator !() const
        {
            return !m_ptr;
        }

        Result& operator *() const
        {
            BOOST_ASSERT(m_ptr);
            return *m_ptr;
        }

    private:
        boost::scoped_ptr<Result> m_ptr;
    };

    // for reference
    template< class Result >
    struct postcondition_result_ptr<Result&>
    {
        postcondition_result_ptr() :
            m_ptr(PSTADE_NULLPTR)
        { }

        void reset(Result& x)
        {
            m_ptr = boost::addressof(x);
        }

        bool operator !() const
        {
            return !m_ptr;
        }

        Result& operator *() const
        {
            BOOST_ASSERT(m_ptr);
            return *m_ptr;
        }

        Result *m_ptr;
    };


    // oldof
    //

    struct any_old
    {
        template< class T >
        explicit any_old(T const& x) :
            m_old(x)
        { }

        template< class T >
        T const of(T const&)
        {
            return boost::any_cast<T>(m_old);
        }

    private:
        boost::any m_old;
    };


    inline
    void suppress_unreachable_code_warning()
    { }


} // namespace contract_detail


} // namespace pstade


// macros
//


#if !defined(BOOST_MPL_PP_TOKEN_EQUAL_void)
    #define BOOST_MPL_PP_TOKEN_EQUAL_void(A) \
        A \
    /**/
#endif


#if !defined(NDEBUG)

    // precondition
    //
    #define PSTADE_PRECONDITION(As) \
        PSTADE_CONTRACT_try_catch(As, "precondition is broken.") \
    /**/

    // postcondition
    //
    #define PSTADE_POSTCONDITION(ResultT) \
        BOOST_PP_IIF( BOOST_MPL_PP_TOKEN_EQUAL(ResultT, void), \
            PSTADE_POSTCONDITION_void, \
            PSTADE_POSTCONDITION_non_void \
        )(ResultT) \
    /**/

    #define PSTADE_RETURN(Result) \
        BOOST_PP_IIF( BOOST_MPL_PP_TOKEN_EQUAL(Result, void), \
            PSTADE_POSTCONDITION_evaluation_begin_void, \
            PSTADE_POSTCONDITION_evaluation_begin_non_void \
        )(Result) \
    /**/

        // non void
        //
        #define PSTADE_POSTCONDITION_non_void(ResultT) \
                ::pstade::contract_detail::postcondition_result_ptr< ResultT > pstade_contract_detail_result_ptr; \
            pstade_contract_detail_postcondition_label: \
                if (!!pstade_contract_detail_result_ptr) { \
                    ResultT result = *pstade_contract_detail_result_ptr; \
                    ::pstade::unused(result); \
                    PSTADE_POSTCONDITION_evaluation_non_void \
        /**/

            #define PSTADE_POSTCONDITION_evaluation_non_void(As) \
                    PSTADE_CONTRACT_try_catch(As, "postcondition is broken.") \
                    return result; \
                } \
            /**/

        #define PSTADE_POSTCONDITION_evaluation_begin_non_void(Result) \
            { \
                pstade_contract_detail_result_ptr.reset(Result); \
                goto pstade_contract_detail_postcondition_label; \
            } \
        /**/

        // void
        //
        #define PSTADE_POSTCONDITION_void(_) \
                bool pstade_contract_detail_postcondition_evaluation_begins = false; \
            pstade_contract_detail_postcondition_label: \
                if (pstade_contract_detail_postcondition_evaluation_begins) { \
                    PSTADE_POSTCONDITION_evaluation_void \
        /**/

            #define PSTADE_POSTCONDITION_evaluation_void(As) \
                    PSTADE_CONTRACT_try_catch(As, "postcondition is broken.") \
                    return; \
                } \
            /**/

        #define PSTADE_POSTCONDITION_evaluation_begin_void(_) \
            { \
                pstade_contract_detail_postcondition_evaluation_begins = true; \
                goto pstade_contract_detail_postcondition_label; \
            } \
        /**/

    // class invariant
    //
    #define PSTADE_CLASS_INVARIANT(As) \
        friend class ::pstade::contract_access; \
        void pstade_invariant() const \
        { \
            PSTADE_CONTRACT_expand(As) \
        } \
    /**/

    #define PSTADE_PUBLIC_PRECONDITION(As) \
        PSTADE_CONTRACT_try_catch(As, "public precondition is broken.") \
        ::pstade::contract_detail::precondition_evaluator pstade_contract_detail_precondition_evaluator_of(*this, true,  true); \
    /**/

    #define PSTADE_CONSTRUCTOR_PRECONDITION(As) \
        PSTADE_CONTRACT_try_catch(As, "constructor precondition is broken.") \
        ::pstade::contract_detail::precondition_evaluator pstade_contract_detail_precondition_evaluator_of(*this, false, true); \
    /**/

    #define PSTADE_DESTRUCTOR_PRECONDITION(As) \
        PSTADE_CONTRACT_try_catch(As, "destructor precondition is broken.") \
        ::pstade::contract_detail::precondition_evaluator pstade_contract_detail_precondition_evaluator_of(*this, true, false); \
    /**/

    // block invariant
    //
    #define PSTADE_INVARIANT(As) \
        PSTADE_CONTRACT_try_catch(As, "block invariant is broken.") \
    /**/

    // oldof
    //
    #define PSTADE_COPY_OLDOF(X, Id) \
        ::pstade::contract_detail::any_old Id(X); \
    /**/

    // helper
    //
    #define PSTADE_CONTRACT_try_catch(As, Msg) \
        try { \
            PSTADE_CONTRACT_expand(As) \
            ::pstade::contract_detail::suppress_unreachable_code_warning(); \
        } \
        catch (...) { \
            BOOST_ASSERT(Msg && false); \
        } \
    /**/

    #define PSTADE_CONTRACT_expand \
        PSTADE_CONTRACT_expand_if_seq \
    /**/

        #define PSTADE_CONTRACT_expand_if_seq(As) \
            BOOST_PP_IIF( BOOST_MPL_PP_IS_SEQ(As), \
                BOOST_PP_SEQ_FOR_EACH, \
                BOOST_PP_TUPLE_EAT(3) \
            )(PSTADE_CONTRACT_expander, ~, As) \
        /**/

        #define PSTADE_CONTRACT_expander(R, _, A) \
            BOOST_ASSERT(A); \
        /**/

#else

    #define PSTADE_PRECONDITION(As)
    #define PSTADE_POSTCONDITION(T) BOOST_PP_TUPLE_EAT(1)

    #define PSTADE_RETURN(Result) \
        BOOST_PP_IIF( BOOST_MPL_PP_TOKEN_EQUAL(Result, void), \
            return, \
            return (Result) \
        ) \
    /**/

    #define PSTADE_CLASS_INVARIANT(As)
    #define PSTADE_PUBLIC_PRECONDITION(As)
    #define PSTADE_CONSTRUCTOR_PRECONDITION(As)
    #define PSTADE_DESTRUCTOR_PRECONDITION(As)
    #define PSTADE_INVARIANT(As)
    #define PSTADE_COPY_OLDOF(X, Id)

#endif // !defined(NDEBUG)


#endif
