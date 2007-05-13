#ifndef PSTADE_OVEN_SUB_SET_HPP
#define PSTADE_OVEN_SUB_SET_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <vector>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/utility/result_of.hpp>
#include "./indirected.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace sub_set_detail {


    // Workaround:
    // 'boost::base_from_member' can't be used; see <pstade/base_from.hpp>.
    // Note 'pstade::base_from' too should be avoided,
    // because it is (conceptually) heavey to copy 'vector'.
    template< class Range >
    struct init
    {
        typedef init type;
        typedef typename range_iterator<Range>::type iter_t;
        typedef std::vector<iter_t> storage_type;

        // Prefer non-unary template; see <pstade/implicitly_defined.hpp>.
        template< class IterOfIters >
        init(IterOfIters first, IterOfIters last) :
            m_storage(first, last)
        { }

    protected:
        storage_type m_storage;
    };


    template< class Range >
    struct super_ :
        boost::result_of<
            op_make_indirected<>(typename init<Range>::storage_type&)
        >
    { };


} // namespace sub_set_detail


template< class Range >
struct sub_set :
    private sub_set_detail::init<Range>::type,
    sub_set_detail::super_<Range>::type
{
private:
    typedef typename sub_set_detail::init<Range>::type init_t;
    typedef typename sub_set_detail::super_<Range>::type super_t;

public:
    template< class Iters >
    explicit sub_set(Iters const& its) :
        init_t(boost::begin(its), boost::end(its)),
        super_t(make_indirected(init_t::m_storage))
    { }
};


} } // namespace pstade::oven


#endif
