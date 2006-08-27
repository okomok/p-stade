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
#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/mpl/aux_/preprocessor/is_seq.hpp>
// #include <boost/mpl/aux_/preprocessor/token_equal.hpp>
#include <boost/noncopyable.hpp>
// #include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/utility/enable_if.hpp>
#include <pstade/for_debug.hpp>
#include <pstade/has_xxx.hpp>
#include <pstade/implies.hpp>
#include <pstade/nonconstructible.hpp>
#include <pstade/overload.hpp>


#if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
    // VC7.1 function-try-block doesn't support function templates.
    #define PSTADE_CONTRACT_NO_FUNCTION_TEMPLATE_TRY_BLOCK
#endif


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


    PSTADE_HAS_TYPE(pstade_invariant_checkable)


    // member function
    //
    template< class T > inline
    typename boost::enable_if<has_pstade_invariant_checkable<T>,
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
    typename boost::disable_if<has_pstade_invariant_checkable<T>,
    void>::type aux(T const& x)
    {
        pstade_invariant(x);
    }


} // namespace invariant_detail


template< class T > inline
bool invariant(T const& x)
{
    pstade::for_debug();

    try {
        invariant_detail::aux(x);
    }
    catch (...) {
        BOOST_ASSERT("class invariant is broken." && false);
    }

    return true; // for 'assert'.
}


namespace invariant_checker_detail {


    struct placeholder
    {
        typedef int pstade_invariant_checkable; // don't forget!
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


    struct impl :
        private boost::noncopyable
    {
        template< class T >
        explicit impl(T const& x, bool ctor, bool dtor) :
            m_px(new holder<T>(x)), m_dtor(dtor)
        {
            if (ctor)
                pstade::invariant(*m_px);
        }

        ~impl()
        {
            if (m_dtor)
                pstade::invariant(*m_px);
        }

    private:
        boost::scoped_ptr<placeholder> m_px;
        bool m_dtor;
    };


} // namespace invariant_checker_detail


struct invariant_checker
    // must be copyable for 'catch'.
    // See Standard 15.1/5 or 15.3/16.
{
    template< class T >
    explicit invariant_checker(T const& x, bool ctor, bool dtor) :
        m_pimpl(new invariant_checker_detail::impl(x, ctor, dtor))
    { };

private:
    boost::shared_ptr<invariant_checker_detail::impl> m_pimpl;
};


namespace contract_detail {


    // Note:
    // cannot be derived from 'std::exception',
    // otherwise VC7.1/8 complains.
    struct goto_handler
    { };


    inline
    void suppress_unreachable_code_warning()
    { }


} // namespace contract_detail


} // namespace pstade


// macros
//

#if !defined(NDEBUG)


    #define PSTADE_CONTRACT_expand \
        PSTADE_CONTRACT_expand_ \
    /**/

        #define PSTADE_CONTRACT_expand_(As) \
            BOOST_PP_SEQ_FOR_EACH(PSTADE_CONTRACT_expander, ~, As) \
        /**/

        #define PSTADE_CONTRACT_expand_rejected(As) \
            BOOST_PP_IF (BOOST_MPL_PP_TOKEN_EQUAL(As, empty), \
                BOOST_PP_TUPLE_EAT(3), \
                BOOST_PP_SEQ_FOR_EACH \
            )(PSTADE_CONTRACT_expander, ~, As) \
        /**/

        #define PSTADE_CONTRACT_expander(R, _, A) \
            BOOST_ASSERT(A); \
        /**/

        #if !defined(BOOST_MPL_PP_TOKEN_EQUAL_empty)
            #define BOOST_MPL_PP_TOKEN_EQUAL_empty(X) \
                X \
            /**/
        #endif

    #define PSTADE_CLASS_INVARIANT(As) \
        typedef int pstade_invariant_checkable; \
        friend class pstade::contract_access; \
        void pstade_invariant() const \
        { \
            PSTADE_CONTRACT_expand(As) \
        } \
    /**/

    #define PSTADE_PRECONDITION(As) \
        BOOST_PP_IIF (BOOST_MPL_PP_IS_SEQ(As), \
            PSTADE_PRECONDITION_free, \
            PSTADE_PRECONDITION_public_member_ BOOST_PP_TUPLE_EAT(1) \
        )(As) \
    /**/

        #define PSTADE_PRECONDITION_free(As) \
            try { \
                PSTADE_CONTRACT_expand(As) \
                throw pstade::contract_detail::goto_handler(); \
            } \
            catch (pstade::contract_detail::goto_handler const&) \
        /**/

        #define PSTADE_PRECONDITION_public_member(As) \
            try { \
                PSTADE_CONTRACT_expand(As) \
                throw pstade::contract_detail::goto_handler(); \
            } \
            catch (pstade::contract_detail::goto_handler const&) \
        /**/

        #define PSTADE_PRECONDITION_public_member_(As) \
            PSTADE_PRECONDITION_public_member(As) \
        /**/

    #define PSTADE_PUBLIC_PRECONDITION(As) \
        try { \
            PSTADE_CONTRACT_expand(As) \
            throw pstade::invariant_checker(*this, true, true); \
        } \
        catch (pstade::invariant_checker const&) \
    /**/

    #define PSTADE_PUBLIC_CONSTRUCTOR \
        pstade::invariant_checker pstade_contract_detail_ctor_invariant_checker_of(*this, false, true) \
    /**/

    #define PSTADE_PUBLIC_DESTRUCTOR \
        pstade::invariant_checker pstade_contract_detail_dtor_invariant_checker_of(*this, true, false) \
    /**/

    #define PSTADE_INVARIANT(As) \
        try { \
            PSTADE_CONTRACT_expand(As) \
            pstade::contract_detail::suppress_unreachable_code_warning(); \
        } \
        catch (...) { \
            BOOST_ASSERT("block invariant is broken." && false); \
        } \
    /**/

    // Workaround
    #if !defined(PSTADE_CONTRACT_NO_FUNCTION_TEMPLATE_TRY_BLOCK)
        #define PSTADE_PRECONDITION_        PSTADE_PRECONDITION
        #define PSTADE_PUBLIC_PRECONDITION_ PSTADE_PUBLIC_PRECONDITION
    #else
        #define PSTADE_PRECONDITION_(As)
        #define PSTADE_PUBLIC_PRECONDITION_(As)
    #endif

#else

    #define PSTADE_CLASS_INVARIANT(As)
    #define PSTADE_PRECONDITION(As)
    #define PSTADE_PUBLIC_PRECONDITION(As)
    #define PSTADE_PUBLIC_CONSTRUCTOR
    #define PSTADE_PUBLIC_DESTRUCTOR
    #define PSTADE_INVARIANT(As)

    #define PSTADE_PRECONDITION_(As)
    #define PSTADE_PUBLIC_PRECONDITION_(As)

#endif // !defined(NDEBUG)





#endif
