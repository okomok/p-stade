#ifndef PSTADE_SAUSAGE_GENERATE_ITERATOR_HPP
#define PSTADE_SAUSAGE_GENERATE_ITERATOR_HPP


// PStade.Sausage
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://d.hatena.ne.jp/y-hamigaki/20060409#1144593955


#include <boost/iterator/iterator_facade.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/shared_ptr.hpp>
#include <pstade/param.hpp>
#include <pstade/remove_cvr.hpp>
#include <pstade/unused.hpp>
#include "./detail/generate_iterator_impl.hpp"
#include "./detail/routine_result.hpp"


namespace pstade { namespace sausage {


template< class Routine >
struct generate_iterator;


namespace generate_iterator_detail {


    template< class Routine >
    struct super_
    {
        typedef typename detail::routine_result<Routine>::type result_t;
        typedef typename remove_cvr<result_t>::type val_t;
        typedef typename param<result_t>::type ref_t; // 'param' is useful :-)

        typedef boost::iterator_facade<
            generate_iterator<Routine>,
            val_t,
            boost::single_pass_traversal_tag,
            ref_t
        > type;
    };


} // namespace generate_iterator_detail


template< class Routine >
struct generate_iterator :
    generate_iterator_detail::super_<Routine>::type
{
private:
    typedef typename generate_iterator_detail::super_<Routine>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef detail::generate_iterator_impl<Routine> impl_t;

public:
    explicit generate_iterator() // end iter
    { }

    explicit generate_iterator(Routine gen) :
        m_pimpl(new impl_t(gen))
    {
        if (m_pimpl->done())
            m_pimpl.reset();
    }

private:
    boost::shared_ptr<impl_t> m_pimpl;

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        return m_pimpl->deref();
    }

    void increment()
    {
        m_pimpl->next();
        if (m_pimpl->done())
            m_pimpl.reset();
    }

    template< class Other >
    bool equal(Other const& other) const
    {
        return m_pimpl == other.m_pimpl;
    }
};


template< class Routine > inline
generate_iterator<Routine> const
make_generate_begin_iterator(Routine gen)
{
    return generate_iterator<Routine>(gen);
}


template< class Routine > inline
generate_iterator<Routine> const
make_generate_end_iterator(Routine gen)
{
    pstade::unused(gen);
    return generate_iterator<Routine>();
}


} } // namespace pstade::sausage


#endif
