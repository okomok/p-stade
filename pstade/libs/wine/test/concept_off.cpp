#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


 // #define PSTADE_CONCEPT_CHECK


#include <pstade/concept.hpp>
#include <boost/test/minimal.hpp>
#include <boost/concept_check.hpp> // ConvertibleConcept

#if 0

template< class U, class T >
PSTADE_CONCEPT_WHERE(
    ((boost::ConvertibleConcept<T, U>))
    ((boost::ConvertibleConcept<T, U>)),
(U)) return_dependent(T const& x)
{
    return static_cast<U>(x);
}

template< class U, class T >
PSTADE_CONCEPT_WHERE(
    ((boost::ConvertibleConcept<T, U>))
    ((boost::ConvertibleConcept<T, U>)),
(U)) const return_const(T const& x)
{
    return static_cast<U>(x);
}

template< class U, class T >
PSTADE_CONCEPT_WHERE(
    ((boost::ConvertibleConcept<T, U>))
    ((boost::ConvertibleConcept<T, U>)),
(int)) return_non_dependent(T const& x)
{
    return static_cast<int>(x);
}

template< class U, class T >
PSTADE_CONCEPT_WHERE(
    ((boost::ConvertibleConcept<T, U>))
    ((boost::ConvertibleConcept<T, U>)),
(void)) return_void(T const&)
{
}

#endif


template< class U, class T >
U return_dependent(T const& x)
{
    PSTADE_CONCEPT_ASSERT((boost::ConvertibleConcept<T, U>));
    PSTADE_CONCEPT_ASSERT((boost::ConvertibleConcept<T, U>));
    return static_cast<U>(x);
}


void test()
{
#if 0
    ::return_dependent<float>(17);
    ::return_non_dependent<float>(17);
    ::return_const<float>(17);
    return ::return_void<float>(17);
#endif

    ::return_dependent<float>(17);
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
