
// PStade.Diet
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/diet/access.hpp>


// hierarchy test
//   must use 'pstade::overload<>'!
//
namespace mfc {

    struct A
    {
        virtual bool AssertValid() const
        {
            return true;
        };
    };

    struct B : A
    { };

    struct C : A
    { };

}

inline bool pstade_diet_is_valid(const mfc::A& a, pstade::overload<>)
{
    return a.AssertValid();
}


// intrusive test
//
struct V
{
    typedef V pstade_diet_diagnostic;

    bool pstade_diet_is_valid() const
    {
        return true;
    }
};


// intrusive private test
//
struct W
{
private:

friend class pstade::diet::access;
    typedef W pstade_diet_diagnostic;
    bool pstade_diet_is_valid() const
    {
        return true;
    }
};


// namespace test
//
namespace my {

    struct Y
    { };

    inline bool pstade_diet_is_valid(const Y& )
    {
        return true;
    }

}


// global test
//
namespace your {

    struct Z
    { };

}

inline bool pstade_diet_is_valid(const your::Z& , pstade::overload<>)
{
    return true;
}


// type set test
//

struct S
{ };

struct T
{ };

struct U
{ };


template< class X >
struct is_STU :
    boost::mpl::or_<
        boost::is_same<X, S>,
        boost::is_same<X, T>,
        boost::is_same<X, U>
    >
{ };


template< class T > inline
typename boost::enable_if<is_STU<T>, bool>::type
pstade_diet_is_valid(const T& , pstade::overload<>)
{
    return true;
}

