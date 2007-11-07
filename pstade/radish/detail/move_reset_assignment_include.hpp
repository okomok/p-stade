

// PStade.Radish
//
// Copyright Shunsuke Sogame 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


    pstade_radish_this_type&
    operator=(boost::none_t)
    {
        this->reset();
        return *this;
    }

    template<class pstade_X>
    pstade_radish_this_type&
    operator=(pstade_X x)
    {
        this->reset(x);
        return *this;
    }

