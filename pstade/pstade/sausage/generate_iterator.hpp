#ifndef PSTADE_SAUSAGE_GENERATE_ITERATOR_HPP
#define PSTADE_SAUSAGE_GENERATE_ITERATOR_HPP


// PStade.Sausage
//
// Copyright MB 2005-2006.
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


namespace pstade { namespace sausage {


template< class Generator >
struct generate_iterator;


namespace generate_iterator_detail {


    template< class Generator >
    struct super_
    {
        // Note:
        // If 'result_t' is not reference, it should not be modified.
        typedef typename Generator::result_type result_t;
        typedef typename remove_cvr<result_t>::type val_t;
        typedef typename param<result_t>::type ref_t;

        typedef boost::iterator_facade<
            generate_iterator<Generator>,
            val_t,
            boost::single_pass_traversal_tag,
            ref_t
        > type;
    };


} // namespace generate_iterator_detail


template< class Generator >
struct generate_iterator :
    generate_iterator_detail::super_<Generator>::type
{
private:
    typedef typename generate_iterator_detail::super_<Generator>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef detail::generate_iterator_impl<Generator> impl_t;

public:
    explicit generate_iterator() // end iter
    { }

    explicit generate_iterator(Generator gen) :
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


template< class Generator > inline
generate_iterator<Generator> const
make_generate_begin_iterator(Generator gen)
{
    return generate_iterator<Generator>(gen);
}


template< class Generator > inline
generate_iterator<Generator> const
make_generate_end_iterator(Generator gen)
{
    pstade::unused(gen);
    return generate_iterator<Generator>();
}


} } // namespace pstade::sausage


#endif
