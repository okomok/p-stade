#ifndef PSTADE_OVEN_CHECKED_HPP
#define PSTADE_OVEN_CHECKED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// References:
//
// [1] Microsoft, checked_iterator, Standard C++ Library.
//     http://msdn2.microsoft.com/en-us/library/aa985943(VS.80).aspx


#include <stdexcept> // logic_error, out_of_range
#include <string>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/throw_exception.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./do_iter_swap.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


struct singular_iterator_operation :
    std::logic_error
{
    explicit singular_iterator_operation(std::string msg) :
        std::logic_error(msg)
    { }
};

struct incompatible_iterators :
    std::logic_error
{
    explicit incompatible_iterators(std::string msg) :
        std::logic_error(msg)
    { }
};


namespace checked_detail {


    namespace here = checked_detail;


    inline
    void throw_out_of_range()
    {
        std::out_of_range err("out of 'check_iterator' range");
        boost::throw_exception(err);
    }


    template< class CheckIterator >
    void check_singularity(CheckIterator it)
    {
        if (it.is_singular()) {
            singular_iterator_operation err("operation on default-constructed 'check_iterator'");
            boost::throw_exception(err);
        }
    }


    template< class CheckIterator1, class CheckIterator2 >
    void check_compatibility(CheckIterator1 it1, CheckIterator2 it2)
    {
        if (it1.begin() != it2.begin() || it1.end() != it2.end()) {
            incompatible_iterators err("incompatible iterators of 'check_iterator'");
            boost::throw_exception(err);
        }
    }


    template< class Iterator >
    struct check_iterator;


    template< class Iterator >
    struct check_iterator_super
    {
        typedef
            boost::iterator_adaptor<
                check_iterator<Iterator>,
                Iterator
            >
        type;
    };


    template< class Iterator >
    struct check_iterator :
        check_iterator_super<Iterator>::type
    {
    private:
        typedef typename check_iterator_super<Iterator>::type super_t;
        typedef typename super_t::reference ref_t;
        typedef typename super_t::difference_type diff_t;

    public:
        check_iterator() :
            m_singular(true)
        { }

        check_iterator(Iterator it, Iterator first, Iterator last) :
            super_t(it),
            m_first(first), m_last(last),
            m_singular(false)
        { }

        template< class I >
        check_iterator(check_iterator<I> const& other,
            typename boost::enable_if_convertible<I, Iterator>::type * = 0
        ) :
            super_t(other.base()),
            m_first(other.begin()), m_last(other.end()),
            m_singular(other.is_singular())
        {
            here::check_singularity(*this);
        }

        Iterator begin() const
        {
            here::check_singularity(*this);
            return m_first;
        }

        Iterator end() const
        {
            here::check_singularity(*this);
            return m_last;
        }

        bool is_begin() const
        {
            here::check_singularity(*this);
            return this->base() == m_first;
        }

        bool is_end() const
        {
            here::check_singularity(*this);
            return this->base() == m_last;
        }

        bool is_singular() const
        {
            return m_singular;
        }

    private:
        Iterator m_first, m_last;
        bool m_singular;

    friend class boost::iterator_core_access;
        ref_t dereference() const
        {
            here::check_singularity(*this);

            if (is_end())
                here::throw_out_of_range();

            return *this->base();
        }

        template< class I >
        bool equal(check_iterator<I> const& other) const
        {
            here::check_singularity(*this);
            here::check_singularity(other);
            here::check_compatibility(*this, other);

            return this->base() == other.base();
        }

        void increment()
        {
            here::check_singularity(*this);

            if (is_end())
                here::throw_out_of_range();

            ++this->base_reference();
        }

        void decrement()
        {
            here::check_singularity(*this);

            if (is_begin())
                here::throw_out_of_range();

            --this->base_reference();
        }

        void advance(diff_t n)
        {
            here::check_singularity(*this);

            if (
                ( n >= 0 &&  n > ( m_last - this->base()  ) ) ||
                ( n <  0 && -n > ( this->base() - m_first ) )
            ) {
                here::throw_out_of_range();
            }

            this->base_reference() += n;
        }

        template< class I >
        diff_t distance_to(check_iterator<I> const& other) const
        {
            here::check_singularity(*this);
            here::check_singularity(other);
            here::check_compatibility(*this, other);

            return other.base() - this->base();
        }
    };


    template< class I >
    void iter_swap(check_iterator<I> const& left, check_iterator<I> const& right)
    {
        here::check_singularity(left);
        here::check_singularity(right);
        here::check_compatibility(left, right);
        do_iter_swap(left.base(), right.base());
    }


    template< class Range >
    struct baby
    {
        typedef
            check_iterator<
                typename range_iterator<Range>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(Range& rng) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

            return result_type(
                iter_t(boost::begin(rng), boost::begin(rng), boost::end(rng)),
                iter_t(boost::end(rng),   boost::begin(rng), boost::end(rng))
            );
        }
    };


} // namespace checked_detail


PSTADE_FUNCTION(make_checked, (checked_detail::baby<_>))
PSTADE_PIPABLE(checked, (op_make_checked))


} } // namespace pstade::oven


#endif
