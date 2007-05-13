#ifndef PSTADE_IS_OLD_OF_HPP
#define PSTADE_IS_OLD_OF_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/object_generator.hpp>


namespace pstade {


    namespace is_old_of_detail {


        template< class Value >
        struct return_op
        {
            typedef bool result_type;

            bool operator()(Value const& now) const
            {
                return m_old == now;
            }

            explicit return_op(Value const& old) :
                m_old(old)
            { }

        private:
            Value m_old;
        };


    } // namespace is_old_of_detail


    PSTADE_OBJECT_GENERATOR(is_old_of, (is_old_of_detail::return_op< deduce<_1, to_value> >))


} // namespace pstade


#endif
