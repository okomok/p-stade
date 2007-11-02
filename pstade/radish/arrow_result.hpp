#ifndef PSTADE_RADISH_ARROW_RESULT_HPP
#define PSTADE_RADISH_ARROW_RESULT_HPP


// PStade.Radish
//
// Copyright Shunsuke Sogame 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// (C) Copyright David Abrahams 2002.
// (C) Copyright Jeremy Siek    2002.
// (C) Copyright Thomas Witt    2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/utility/addressof.hpp>


namespace pstade { namespace radish {


    template< class T >
    struct arrow_result
    {
        struct type
        {
            type(T const& x) :
                m_value(x)
            { }

            T* operator->() const
            {
                return boost::addressof(m_value);
            }

        private:
            mutable T m_value;
        };
    };


    template< class T >
    struct arrow_result<T&>
    {
        struct type
        {
            type(T& x) :
                m_ref(x)
            { }

            T* operator->() const
            {
                return boost::addressof(m_ref);
            }

        private:
            T& m_ref;
        };
    };


    template< >
    struct arrow_result<void>
    {
        typedef void type;
    };


} } // namespace pstade::radish


#endif
