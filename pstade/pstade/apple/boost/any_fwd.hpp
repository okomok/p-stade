#ifndef PSTADE_APPLE_BOOST_ANY_FWD_HPP
#define PSTADE_APPLE_BOOST_ANY_FWD_HPP


// PStade.Apple
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace boost {


class any;


class bad_any_cast;


template<typename ValueType>
ValueType * any_cast(any * operand);

template<typename ValueType>
const ValueType * any_cast(const any * operand);


template<typename ValueType>
ValueType any_cast(any & operand);

template<typename ValueType>
ValueType any_cast(const any & operand);


} // namespace boost


#endif
