#ifndef PSTADE_OVEN_ACCUMULATE_ITERATOR_HPP
#define PSTADE_OVEN_ACCUMULATE_ITERATOR_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_adaptor.hpp>


namespace pstade { namespace oven {


template< class Iterator, class BinaryFun >
struct accumulate_iterator;


namespace accumulate_iterator_detail {


    template< class Iterator, class BinaryFun >
    struct super_
    {
        typedef boost::iterator_value<Iterator>::type value_t;

        typedef boost::iterator_adaptor<
            accumulate_iterator<Iterator, BinaryFun>,
            Iterator,
            value_t,
            boost::forwart_traversal_tag,
            value_t const
        > type;
    };


} // namespace accumulate_iterator_detail


template< class Iterator, class BinaryFun >
struct accumulate_iterator :
    accumulate_iterator_detail::super_<Iterator, BinaryFun>::type
{
private:
    typedef typename accumulate_iterator_detail::super_<Iterator, BinaryFun>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename super_t::value_type value_t;

public:
    accumulate_iterator()
    { }

    accumulate_iterator(Iterator it, BinaryFun fun, value_t const& val) :
        super_t(it), m_fun(fun), m_value(val)
    { }

    template< class Iterator_ >
    accumulate_iterator(
        accumulate_iterator<Iterator_> other,
        typename boost::enable_if_convertible<Iterator_, Iterator>::type * = 0
    ) :
        super_t(other.base()), m_fun(other.functor()), m_value(*other)
    { }

    BinaryFun functor() const
    {
        return m_fun;
    }

private:
    BinaryFun m_fun;
    value_t m_value;

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        return m_fun(m_value, *this->base_referece());
    }

    void increment()
    {
        m_value = dereference();
        ++this->base_reference();
    }
};


template< class Iterator, class BinaryFun, class Value > inline
accumulate_iterator<Iterator, BinaryFun> const
make_accumulate_iterator(Iterator it, BinaryFun fun, Value const& val)
{
    return accumulate_iterator<Iterator, BinaryFun>(it, first, last);
}


} } // namespace pstade::oven


#endif
