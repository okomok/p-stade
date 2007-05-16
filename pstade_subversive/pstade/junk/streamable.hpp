#ifndef PSTADE_STREAMABLE_HPP
#define PSTADE_STREAMABLE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n1973.html


#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/automatic.hpp>
#include <pstade/auxiliary.hpp>


namespace pstade {


    template<class InputStreamable>
    struct op_streamable_to
    {
        typedef InputStreamable result_type;

        template<class OutputStreamable>
        InputStreamable operator()(OutputStreamable const& src) const
        {
            return boost::lexical_cast<InputStreamable>(src);
        }
    };


    template<class InputStreamable, class OutputStreamable> inline
    typename boost::result_of<op_streamable_to<InputStreamable>(OutputStreamable const&)>::type
    streamable_to(OutputStreamable const& src)
    {
        return op_streamable_to<InputStreamable>()(src);
    }


    PSTADE_AUXILIARY0(to_streamable, (automatic< op_streamable_to<boost::mpl::_> >))


    PSTADE_AUXILIARY0(to_string, (op_streamable_to<std::string>))
    PSTADE_AUXILIARY0(to_wstring, (op_streamable_to<std::wstring>))


} // namespace pstade


#endif
