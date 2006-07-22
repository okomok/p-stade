#ifndef PSTADE_BISCUIT_MATCH_RESULTS_MATCH_RESULTS_HPP
#define PSTADE_BISCUIT_MATCH_RESULTS_MATCH_RESULTS_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <functional> // std::less
#include <map>
#include <utility> // std::pair

// Workaround:
//   'boost::sub_range' is broken under eVC++4 and VC++8. It is not Assignable.
#include <pstade/oven/sub_range_base.hpp>


namespace pstade { namespace biscuit {


template< class ParsingRange >
struct match_results :
    std::map< int, typename oven::sub_range_base<ParsingRange>::type, std::less<int> >
{
private:
    typedef typename oven::sub_range_base<ParsingRange>::type stored_range_t;
    typedef std::map< int, stored_range_t, std::less<int> > super_t;

public:
    typedef ParsingRange pstade_biscuit_match_results_parsing_range_type;

    template< class ParsingSubRange >
    bool pstade_biscuit_find_backref(int id, ParsingSubRange& subrng)
    {
        typedef typename boost::range_iterator<super_t>::type iter_t;

        iter_t const it = super_t::find(id);
        if (it != boost::end(*this)) {
            subrng = it->second;
            return true;
        }

        return false;
    }

    template< class ParsingSubRange >
    void pstade_biscuit_insert_backref(int id, ParsingSubRange& subrng)
    {
        typedef typename boost::range_iterator<super_t>::type iter_t;

#if !BOOST_WORKAROUND(BOOST_MSVC, < 1300)

        std::pair<iter_t, bool> ret = super_t::insert(std::make_pair(id, subrng));
        if (!ret.second) // overwrite
            ret.first->second = subrng;

#else

    // Workaround:
    //   VC6 cannot order two ctors of boost::iterator_range if the argument range is const-qualified.
    //   And ctor of std::pair also adds const to ParsingSubRange.
    //   That is to say, we cannot call ctors of std::pair, oh my!

    // If 'const' of 'int const' is missing, results.insert(val) calls ctor of std::pair,
    // because this is the exact type of std::map's value_type,
    // and so a trivial conversion using ctor is required. Take care.

    std::pair<int const, stored_range_t> val; {
        const_cast<int&>(val.first) = id; // illegal but works.
        val.second = subrng;
    }

    std::pair<iter_t, bool> ret = super_t::insert(val);
    if (!ret.second)
        ret.first->second = subrng;

#endif // !BOOST_WORKAROUND(BOOST_MSVC, < 1300)

    }
};


} } // namespace pstade::biscuit


#endif
