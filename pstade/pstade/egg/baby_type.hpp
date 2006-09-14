#ifndef PSTADE_EGG_BABY_TYPE_HPP
#define PSTADE_EGG_BABY_TYPE_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade { namespace egg {


template< class Function >
struct baby
{
    typedef typename Function::pstade_egg_baby_type type;
};


} } // namespace pstade::egg


#endif
