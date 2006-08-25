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


#include <cassert> // revival!
#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/preprocessor/seq/for_each.hpp>  
#include <boost/shared_ptr.hpp>
#include <pstade/debugging.hpp>
#include <pstade/nonconstructible.hpp>


// Workarounds
//

#if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
    // VC7.1 function-try-block doesn't support function templates.
    #define PSTADE_CONTRACT_NO_FUNCTION_TEMPLATE_TRY_BLOCK
#endif


#if BOOST_WORKAROUND(BOOST_MSVC, == 1400)
    // VC8 should have them, but it seems not to work...
    #define PSTADE_CONTRACT_DISABLE_WARNING_UNREACHABLE_CODE_BEGIN() \
        __pragma(warning(push)); \
        __pragma(warning(disable: 4702)); \
    /**/
    #define PSTADE_CONTRACT_DISABLE_WARNING_UNREACHABLE_CODE_END() \
        __pragma(warning(pop)); \
    /**/
#else
    #define PSTADE_CONTRACT_DISABLE_WARNING_UNREACHABLE_CODE_BEGIN()
    #define PSTADE_CONTRACT_DISABLE_WARNING_UNREACHABLE_CODE_END()
#endif


namespace pstade {


// class invariants
//

class contract_access :
    private nonconstructible
{
public:
    template< class T > static
    void detail_assert_invariant(T const& x)
    {
        pstade::debugging();
        x.pstade_invariant();
    }
};


template< class T > inline
void assert_invariant(T const& x)
{
    try {
        contract_access::detail_assert_invariant(x);
    }
    catch (...) {
        BOOST_ASSERT("class invariant is broken." && false);
    }
}


struct scoped_assert_invariant
    // must be copyable for 'catch'.
    // See Standard 15.1/5 or 15.3/16.
{
private:
    struct placeholder
    {
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
            pstade::assert_invariant(m_x);
        }

        T const& m_x;
    };

public:
    template< class T >
        explicit scoped_assert_invariant(T const& x) :
        m_px(new holder<T>(x))
    {
        pstade::assert_invariant(*m_px);
    }

    ~scoped_assert_invariant() throw()
    {
        pstade::assert_invariant(*m_px);
    }

private:
    boost::shared_ptr<placeholder> m_px;
};


namespace contract_detail {

    // Workaround:
    // cannot be derived from 'std::exception'
    // for avoiding weird VC7.1/8 errors.
    struct goto_function_catch_block
    { };

} // namespace contract_detail


} // namespace pstade


// macros
//

#if !defined(NDEBUG)

    #define PSTADE_PRECONDITION(As) \
        try { \
            As \
            throw pstade::contract_detail::goto_function_catch_block(); \
        } \
        catch (pstade::contract_detail::goto_function_catch_block const&) \
    /**/

    // See Standard 15.1/4.
    #define PSTADE_PUBLIC_PRECONDITION(As) \
        try { \
            As \
            throw pstade::scoped_assert_invariant(*this); \
        } \
        catch (pstade::scoped_assert_invariant const&) \
    /**/

    #define PSTADE_BLOCK_INVARIANT(As) \
        PSTADE_CONTRACT_DISABLE_WARNING_UNREACHABLE_CODE_BEGIN() \
        try { \
            As \
        } \
        catch (...) { \
            BOOST_ASSERT("block invariant is broken." && false); \
        } \
        PSTADE_CONTRACT_DISABLE_WARNING_UNREACHABLE_CODE_END() \
    /**/

    #define PSTADE_ASSERT_INVARIANT \
        pstade::assert_invariant(*this) \
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

    #define PSTADE_PRECONDITION(As)
    #define PSTADE_PUBLIC_PRECONDITION(As)
    #define PSTADE_BLOCK_INVARIANT(As)
    #define PSTADE_ASSERT_INVARIANT

    #define PSTADE_PRECONDITION_(As)
    #define PSTADE_PUBLIC_PRECONDITION_(As)

#endif // !defined(NDEBUG)


#define PSTADE_INVARIANT \
    friend class pstade::contract_access; \
    void pstade_invariant() const \
/**/


#endif
