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
#include <boost/noncopyable.hpp>
#include <boost/preprocessor/seq/for_each.hpp>  
#include <boost/scoped_ptr.hpp>
#include <pstade/debugging.hpp>
#include <pstade/nonconstructible.hpp>


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


struct scoped_assert_invariant :
    private boost::noncopyable
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

    ~scoped_assert_invariant()
    {
        pstade::assert_invariant(*m_px);
    }

private:
    boost::scoped_ptr<placeholder> m_px;
};


} // namespace pstade


// macros
//

#if !defined(NDEBUG)

    #define PSTADE_PRECONDITION(As)    As
    #define PSTADE_POSTCONDITION(As)   As
    #define PSTADE_BLOCK_INVARIANT(As) As

    // This order follows n1962.
    #define PSTADE_PUBLIC_PRECONDITION(As) \
        As \
        pstade::scoped_assert_invariant pstade_contract_detail_scoped_assert_invariant_of(*this); \
    /**/

    #define PSTADE_ASSERT_INVARIANT \
        pstade::assert_invariant(*this) \
    /**/

#else

    #define PSTADE_PRECONDITION(As)
    #define PSTADE_POSTCONDITION(As)
    #define PSTADE_BLOCK_INVARIANT(As)
    #define PSTADE_PUBLIC_PRECONDITION(As)
    #define PSTADE_ASSERT_INVARIANT

#endif


#define PSTADE_INVARIANT \
    friend class pstade::contract_access; \
    void pstade_invariant() const \
/**/


#endif
