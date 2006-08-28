#ifndef PSTADE_CONTRACT_HPP
#define PSTADE_CONTRACT_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n1962.html


#include <boost/assert.hpp>
#include <boost/mpl/aux_/preprocessor/is_seq.hpp>
#include <boost/mpl/aux_/preprocessor/token_equal.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/noncopyable.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/utility/enable_if.hpp>
#include <pstade/for_debug.hpp>
#include <pstade/has_xxx.hpp>
#include <pstade/nonconstructible.hpp>
#include <pstade/nullptr.hpp>
#include <pstade/overload.hpp>


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


namespace invariant_detail {


    PSTADE_HAS_TYPE(pstade_invariant_assertable)


    // member function
    //
    template< class T > inline
    typename boost::enable_if<has_pstade_invariant_assertable<T>,
    void>::type aux(T const& x)
    {
        contract_access::detail_invariant(x);
    }


    // ADL
    //
    template< class T > inline
    void pstade_invariant(T const& x)
    {
        pstade_invariant(x, overload<>());
    }

    template< class T > inline
    typename boost::disable_if<has_pstade_invariant_assertable<T>,
    void>::type aux(T const& x)
    {
        pstade_invariant(x);
    }


} // namespace invariant_detail


template< class InvariantAssertable > inline
bool invariant(InvariantAssertable const& ia)
{
    pstade::for_debug();

    try {
        invariant_detail::aux(ia);
    }
    catch (...) {
        BOOST_ASSERT("class invariant is broken." && false);
    }

    return true; // for 'assert'.
}


namespace invariant_assertion_detail {


    struct placeholder
    {
        typedef int pstade_invariant_assertable;
        virtual void pstade_invariant() const = 0;
        virtual ~placeholder() { }
    };


    template< class T >
    struct holder :
        placeholder
    {
        explicit holder(T const& x) :
            m_x(x)
        { }

        virtual void pstade_invariant() const
        {
            pstade::invariant(m_x);
        }

        T const& m_x;
    };


} // namespace invariant_assertion_detail


struct invariant_assertion :
    private boost::noncopyable
{
    template< class InvariantAssertable >
    invariant_assertion(InvariantAssertable const& ia, bool ctor, bool dtor) :
        m_pia(new invariant_assertion_detail::holder<InvariantAssertable>(ia)),
        m_dtor(dtor)
    {
        if (ctor)
            pstade::invariant(*m_pia);
    }

    ~invariant_assertion()
    {
        if (m_dtor)
            pstade::invariant(*m_pia);
    }

private:
    boost::scoped_ptr<invariant_assertion_detail::placeholder> m_pia;
    bool m_dtor;
};


namespace contract_detail {


    inline
    void suppress_unreachable_code_warning()
    { }


    template< class T > inline
    void suppress_unused_variable_warning(T const&)
    { }


} // namespace contract_detail


namespace postcondition_detail {


    // Prefer specialization to metafunction
    // that needs 'typename' for dependent-name.
    //

    // for value
    template< class T >
    struct result_ptr
    {
        void reset(T const& x)
        {
            m_ptr.reset(new T(x));
        }

        bool is_null() const
        {
            return !m_ptr;
        }

        T& operator *() const
        {
            BOOST_ASSERT(!is_null());
            return *m_ptr;
        }

    private:
        boost::scoped_ptr<T> m_ptr;
    };

    // for reference
    template< class T >
    struct result_ptr<T&>
    {
        result_ptr() :
            m_ptr(PSTADE_NULLPTR)
        { }

        void reset(T& x)
        {
            m_ptr = boost::addressof(x);
        }

        bool is_null() const
        {
            return !m_ptr;
        }

        T& operator *() const
        {
            BOOST_ASSERT(!is_null());
            return *m_ptr;
        }

        T *m_ptr;
    };


} // namespace postcondition_detail


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
    #define PSTADE_POSTCONDITION(T) \
        BOOST_PP_IIF (BOOST_MPL_PP_TOKEN_EQUAL(T, void), \
            PSTADE_POSTCONDITION_void, \
            PSTADE_POSTCONDITION_non_void \
        )(T) \
    /**/

    #define PSTADE_RETURN(Result) \
        BOOST_PP_IIF (BOOST_MPL_PP_TOKEN_EQUAL(Result, void), \
            PSTADE_POSTCONDITION_void_begin, \
            PSTADE_POSTCONDITION_non_void_begin \
        )(Result) \
    /**/

        // non void
        //
        #define PSTADE_POSTCONDITION_non_void(T) \
                pstade::postcondition_detail::result_ptr< T > pstade_postcondition_detail_result_ptr; \
            pstade_postcondition_detail_label: \
                if (!pstade_postcondition_detail_result_ptr.is_null()) { \
                    T result = *pstade_postcondition_detail_result_ptr; \
                    pstade::contract_detail::suppress_unused_variable_warning(result); \
                    PSTADE_POSTCONDITION_non_void_end \
        /**/

            #define PSTADE_POSTCONDITION_non_void_end(As) \
                    PSTADE_CONTRACT_try_catch(As, "postcondition is broken.") \
                    return result; \
                } \
            /**/

        #define PSTADE_POSTCONDITION_non_void_begin(Result) \
            { \
                pstade_postcondition_detail_result_ptr.reset(Result); \
                goto pstade_postcondition_detail_label; \
            } \
        /**/

        // void
        //
        #define PSTADE_POSTCONDITION_void(T) \
                bool pstade_postcondition_detail_begins = false; \
            pstade_postcondition_detail_label: \
                if (pstade_postcondition_detail_begins) { \
                    PSTADE_POSTCONDITION_void_end \
        /**/

            #define PSTADE_POSTCONDITION_void_end(As) \
                    PSTADE_CONTRACT_try_catch(As, "postcondition is broken.") \
                    return; \
                } \
            /**/

        #define PSTADE_POSTCONDITION_void_begin(_) \
            { \
                pstade_postcondition_detail_begins = true; \
                goto pstade_postcondition_detail_label; \
            } \
        /**/

    // class invariant
    //
    #define PSTADE_CLASS_INVARIANT(As) \
        typedef int pstade_invariant_assertable; \
        friend class pstade::contract_access; \
        void pstade_invariant() const \
        { \
            PSTADE_CONTRACT_expand(As) \
        } \
    /**/

    #define PSTADE_PUBLIC_PRECONDITION(As) \
        PSTADE_CONTRACT_try_catch(As, "public precondition is broken.") \
        pstade::invariant_assertion pstade_contract_detail_invariant_assertion_of(*this, true,  true); \
    /**/

    #define PSTADE_CONSTRUCTOR_PRECONDITION(As) \
        PSTADE_CONTRACT_try_catch(As, "constructor precondition is broken.") \
        pstade::invariant_assertion pstade_contract_detail_invariant_assertion_of(*this, false, true); \
    /**/

    #define PSTADE_DESTRUCTOR_PRECONDITION(As) \
        PSTADE_CONTRACT_try_catch(As, "destructor precondition is broken.") \
        pstade::invariant_assertion pstade_contract_detail_invariant_assertion_of(*this, true, false); \
    /**/

    // block invariant
    //
    #define PSTADE_INVARIANT(As) \
        PSTADE_CONTRACT_try_catch(As, "block invariant is broken.") \
    /**/

    // helper
    //
    #define PSTADE_CONTRACT_try_catch(As, Msg) \
        try { \
            PSTADE_CONTRACT_expand(As) \
            pstade::contract_detail::suppress_unreachable_code_warning(); \
        } \
        catch (...) { \
            BOOST_ASSERT(Msg && false); \
        } \
    /**/

    #define PSTADE_CONTRACT_expand \
        PSTADE_CONTRACT_expand_if_seq \
    /**/

        #define PSTADE_CONTRACT_expand_if_seq(As) \
            BOOST_PP_IIF (BOOST_MPL_PP_IS_SEQ(As), \
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
        BOOST_PP_IIF (BOOST_MPL_PP_TOKEN_EQUAL(Result, void), \
            return, \
            return (Result) \
        ) \
    /**/

    #define PSTADE_CLASS_INVARIANT(As)
    #define PSTADE_PUBLIC_PRECONDITION(As)
    #define PSTADE_CONSTRUCTOR_PRECONDITION(As)
    #define PSTADE_DESTRUCTOR_PRECONDITION(As)
    #define PSTADE_INVARIANT(As)

#endif // !defined(NDEBUG)


#endif
