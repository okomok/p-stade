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


// Note:
//
// 'precondition' cannot check class invariants, for
// there is no way to know whether it is public or not,
// or even function or class.


#include <stdexcept> // runtime_error
#include <boost/assert.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/throw_exception.hpp>
#include <pstade/nonconstructible.hpp>


namespace pstade {


// exceptions
//

struct contract_broken :
    std::runtime_error
{
    contract_broken() :
        std::runtime_error("")
    { }
};

struct precondition_broken :
    contract_broken
{ };

struct postcondition_broken :
    contract_broken
{ };

struct class_invariant_broken :
    contract_broken
{ };

struct block_invariant_broken :
    contract_broken
{ };


// function pre- and postconditions
//

inline
void precondition(bool c)
{
    if (!c) {
        precondition_broken ex;
        boost::throw_exception(ex);
    }
}

inline
void postcondition(bool c)
{
    if (!c) {
        postcondition_broken ex;
        boost::throw_exception(ex);
    }
}


// block invariants
//

inline
void block_invariant(bool c)
{
    if (!c) {
        block_invariant_broken ex;
        boost::throw_exception(ex);
    }
}


// class invariants
//

class contract_access :
    private nonconstructible
{
public:
    template< class T > static
    bool detail_check_class_invariant(T const& x)
    {
        return x.pstade_invariant();
    }
};

struct class_invariant :
    private boost::noncopyable
{
    template< class T >
    static bool holds(T const& x)
    {
        return contract_access::detail_check_class_invariant(x);
    }

private:
    // type erasure
    //
    struct placeholder
    {
        virtual bool check() const = 0;
        virtual ~placeholder() { }
    };

    template< class T >
    struct holder :
        placeholder
    {
        explicit holder(T const& x) :
            m_x(x)
        { }

        virtual bool check() const
        {
            return contract_access::detail_check_class_invariant(m_x);
        }

        T const& m_x;
    };

public:
    // ctor/dtor
    //
    template< class T >
    explicit class_invariant(T const& x) :
        m_px(new holder<T>(x))
    {
        if (!m_px->check()) {
            BOOST_ASSERT("class invariant broken" && false);
            class_invariant_broken ex;
            boost::throw_exception(ex);
        }
    }

    ~class_invariant()
    {
        if (!m_px->check()) {
            BOOST_ASSERT("class invariant broken" && false);
            // cannot throw.
        }
    }

private:
    boost::scoped_ptr<placeholder> m_px;
};


} // namespace pstade


// macros
//

#if defined(NDEBUG) && defined(PSTADE_CONTRACT_DEBUG)
    #define PSTADE_PRECONDITION(C)    pstade::precondition(C)
    #define PSTADE_POSTCONDITION(C)   pstade::postcondition(C)
    #define PSTADE_BLOCK_INVARIANT(C) pstade::block_invariant(C)
#else // prefer 'assert' for easy debugging.
    #define PSTADE_PRECONDITION    BOOST_ASSERT
    #define PSTADE_POSTCONDITION   BOOST_ASSERT
    #define PSTADE_BLOCK_INVARIANT BOOST_ASSERT
#endif

#if !defined(NDEBUG) || defined(PSTADE_CONTRACT_DEBUG)
    #define PSTADE_CLASS_INVARIANT pstade::class_invariant pstade_contract_detail_class_invariant_of(*this)
#else
    #define PSTADE_CLASS_INVARIANT
#endif


#endif
