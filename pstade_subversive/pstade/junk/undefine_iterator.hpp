#ifndef PSTADE_OVEN_UNDEFINE_ITERATOR_HPP
#define PSTADE_OVEN_UNDEFINE_ITERATOR_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <stdexcept> // range_error
#include <string>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/throw_exception.hpp>


namespace pstade { namespace oven {


template< class Iterator >
struct undefine_iterator;


struct undefine_error :
    std::range_error
{
    explicit undefine_error(std::string const& msg) :
        std::range_error(msg)
    { }
};


namespace undefine_iterator_detail {


    template< class Iterator >
    struct super_
    {
        typedef boost::iterator_adaptor<
            undefine_iterator<Iterator>,
            Iterator
        > type;
    };


    inline
    void throw_error()
    {
        undefine_error err("operation on 'undefine_iterator'");
        boost::throw_exception(err);
    }


} // namespace undefine_iterator_detail


template< class Iterator >
struct undefine_iterator :
    undefine_iterator_detail::super_<Iterator>::type
{
private:
    typedef typename undefine_iterator_detail::super_<Iterator>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename super_t::difference_type diff_t;

public:
    undefine_iterator()
    { }

    explicit undefine_iterator(Iterator const& it) :
        super_t(it)
    { }

    template< class Iterator_ >
    undefine_iterator(
        undefine_iterator<Iterator_> const& other,
        typename boost::enable_if_convertible<Iterator_, Iterator>::type * = 0
    ) :
        super_t(other.base())
    { }

private:
friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        undefine_iterator_detail::throw_error();
        return *this->base();
    }

    template< class Other >
    bool equal(Other const& other) const
    {
        undefine_iterator_detail::throw_error();
        return this->base() == other.base();
    }

    void increment()
    {
        undefine_iterator_detail::throw_error();
        ++this->base_reference();
    }

    void decrement()
    {
        undefine_iterator_detail::throw_error();
        --this->base_reference();
    }

    void advance(diff_t d)
    {
        undefine_iterator_detail::throw_error();
        this->base_reference() += d;
    }

    template< class Other >
    diff_t distance_to(Other const& other) const
    {
        undefine_iterator_detail::throw_error();
        return other.base() - this->base();
    }
};


template< class Iterator > inline
undefine_iterator<Iterator> const
make_undefine_iterator(Iterator const& it)
{
    return undefine_iterator<Iterator>(it);
}


} } // namespace pstade::oven


#endif
