

// PStade.Radish
//
// Copyright Shunsuke Sogame 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


    void reset()
    {
        pstade_radish_this_type().swap(*this);
    }


    template<class pstade_A0>
    void reset(pstade_A0 &a0)
    {
        pstade_radish_this_type(a0).swap(*this);
    }
   
    template<class pstade_A0>
    void reset(pstade_A0 const &a0)
    {
        pstade_radish_this_type(a0).swap(*this);
    }


    template<class pstade_A0, class pstade_A1>
    void reset(pstade_A0 &a0, pstade_A1 &a1)
    {
        pstade_radish_this_type(a0, a1).swap(*this);
    }
   
    template<class pstade_A0, class pstade_A1>
    void reset(pstade_A0 &a0, pstade_A1 const &a1)
    {
        pstade_radish_this_type(a0, a1).swap(*this);
    }
   
    template<class pstade_A0, class pstade_A1>
    void reset(pstade_A0 const &a0, pstade_A1 &a1)
    {
        pstade_radish_this_type(a0, a1).swap(*this);
    }
   
    template<class pstade_A0, class pstade_A1>
    void reset(pstade_A0 const &a0, pstade_A1 const &a1)
    {
        pstade_radish_this_type(a0, a1).swap(*this);
    }

