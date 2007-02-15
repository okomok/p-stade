#ifndef PSTADE_OVEN_MEMOIZE_ITERATOR_HPP
#define PSTADE_OVEN_MEMOIZE_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp>
#include <boost/throw_exception.hpp>
#include <deque>
#include <iterator>
#include <iostream>
#include <algorithm>    // for std::swap
#include <exception>    // for std::exception
#include <boost/limits.hpp>
#include <boost/iterator.hpp>

#include <boost/spirit/core/assert.hpp> // for BOOST_SPIRIT_ASSERT
#include <boost/detail/iterator.hpp> // for boost::detail::iterator_traits

namespace pstade { namespace oven {

namespace impl {
    template <typename T>
    inline void mp_swap(T& t1, T& t2);
}

namespace multi_pass_policies
{

///////////////////////////////////////////////////////////////////////////////
// class ref_counted
// Implementation of an OwnershipPolicy used by memoize_iterator.
//
// Implementation modified from RefCounted class from the Loki library by
// Andrei Alexandrescu
///////////////////////////////////////////////////////////////////////////////
struct ref_counted
{
    protected:
        ref_counted()
            : count(new std::size_t(1))
        {}

        ref_counted(ref_counted const& x)
            : count(x.count)
        {}

        // clone is called when a copy of the iterator is made, so increment
        // the ref-count.
        void clone()
        {
            ++*count;
        }

        // called when a copy is deleted.  Decrement the ref-count.  Return
        // value of true indicates that the last copy has been released.
        bool release()
        {
            if (!--*count)
            {
                delete count;
                count = 0;
                return true;
            }
            return false;
        }

        void swap(ref_counted& x)
        {
            impl::mp_swap(count, x.count);
        }

    public:

    private:
        std::size_t* count;
};


///////////////////////////////////////////////////////////////////////////////
// struct input_iterator
// Implementation of the InputPolicy used by memoize_iterator
// input_iterator encapsulates an input iterator of type Iterator
///////////////////////////////////////////////////////////////////////////////
struct input_iterator
{
    public:

template <typename Iterator>
struct inner
{
        typedef
            typename boost::detail::iterator_traits<Iterator>::value_type
            result_type;
        typedef
            typename boost::detail::iterator_traits<Iterator>::reference
            ref_t;

        struct Data {
            Data(Iterator const &input_, Iterator const& last_) 
            :   input(input_), last(last_), was_initialized(false)
            {}
            
            Iterator input;
            Iterator last;
            result_type curtok;
            bool was_initialized;
        };

       // Needed by compilers not implementing the resolution to DR45. For
       // reference, see
       // http://www.open-std.org/JTC1/SC22/WG21/docs/cwg_defects.html#45.

       friend struct Data;

    public:
        typedef result_type val_t;

    protected:
        inner()
            : data(0)
        {}

        inner(Iterator x, Iterator last)
            : data(new Data(x, last))
        {}

        inner(inner const& x)
            : data(x.data)
        {}

        void destroy()
        {
            delete data;
            data = 0;
        }

        bool same_input(inner const& x) const
        {
            return data == x.data;
        }

        typedef
            typename boost::detail::iterator_traits<Iterator>::value_type
            value_t;
        void swap(inner& x)
        {
            impl::mp_swap(data, x.data);
        }

        void ensure_initialized() const
        {
            if (data && !data->was_initialized) {
                data->curtok = *data->input;      // get the first token
                data->was_initialized = true;
            }
        }

    public:
        result_type const& get_input() const
        {
            BOOST_SPIRIT_ASSERT(NULL != data);
            ensure_initialized();
            return data->curtok;
        }

        void advance_input()
        {
            BOOST_SPIRIT_ASSERT(NULL != data);
            data->was_initialized = false;        // should get the next token
            ++data->input;
        }

        bool input_at_eof() const
        {
            return !data || data->input == data->last;
        }


        Data *data;
};

};


}


template<
    class Iterator,
    class InputPolicy = multi_pass_policies::input_iterator,
    class OwnershipPolicy = multi_pass_policies::ref_counted
>
struct memoize_iterator;


namespace memoize_iterator_detail {


    template<
        class Iterator,
        class InputPolicy,
        class OwnershipPolicy
    >
    struct super_
    {
        typedef typename
            boost::iterator_value<Iterator>::type
        val_t;

        typedef
            boost::iterator_facade<
                memoize_iterator<Iterator, InputPolicy, OwnershipPolicy>,
                val_t,
                boost::forward_traversal_tag,
                val_t const&,
                typename boost::iterator_difference<Iterator>::type
            >
        type;
    };


} // namespace memoize_iterator_detail



template<
    class Iterator,
    class InputPolicy,
    class OwnershipPolicy
>
struct memoize_iterator
    : public OwnershipPolicy
    , public InputPolicy::template inner<Iterator>
    , public memoize_iterator_detail::super_<Iterator, InputPolicy, OwnershipPolicy>::type
{
    typedef typename memoize_iterator_detail::super_<Iterator, InputPolicy, OwnershipPolicy>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename super_t::value_type val_t;

    typedef OwnershipPolicy OP;
    typedef typename InputPolicy::template inner<Iterator> IP;

    typedef std::deque<val_t> table_t;

    memoize_iterator()
        : OP()
        , IP()
    {
    }

    explicit memoize_iterator(Iterator input, Iterator last)
        : OP()
        , m_ptable(new table_t()), m_index(0)
        , IP(input, last)
    {
    }

    ~memoize_iterator()
    {
        if (OP::release())
        {
            IP::destroy();
        }
    }

    memoize_iterator(memoize_iterator const& x)
        : OP(x)
        , m_ptable(x.m_ptable), m_index(x.m_index)
        , IP(x)
    {
        OP::clone();
    }

    memoize_iterator& operator=(memoize_iterator const& x)
    {
        memoize_iterator temp(x);
        temp.swap(*this);
        return *this;
    }

    void swap(memoize_iterator& x)
    {
        OP::swap(x);
        boost::swap(m_ptable, x.m_ptable);
        std::swap(m_index, x.m_index);
        boost::swap(m_cached_value, x.m_cached_value);
        IP::swap(x);
    }

    Iterator const& base() const
    {
        return this->data->input;
    }

private:
    boost::shared_ptr<table_t> m_ptable;
    typename table_t::size_type m_index;
    mutable boost::optional<val_t> m_cached_value;

    Iterator& base_reference()
    {
        return *this->data->input;
    }

    bool is_in_table() const
    {
        return m_index != m_ptable->size();
    }

    val_t const& cached_value() const
    {
        if (!m_cached_value)
            m_cached_value = *base();

        return *m_cached_value;        
    }

    // called to determine whether the iterator is an eof iterator
    bool is_eof() const
    {
        return this->m_index == this->m_ptable->size() &&
            this->input_at_eof();
    }

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        if (is_in_table())
            return (*m_ptable)[m_index];
        else
            return this->get_input();
    }

    void increment()
    {
        if (is_in_table()) {
            ++this->m_index;
        }
        else {
            m_ptable->push_back(cached_value());
            ++m_index;
            this->advance_input();
            m_cached_value.reset();
        }
    }

    bool equal(const memoize_iterator& y) const
    {
        bool is_eof_ = is_eof();
        bool y_is_eof_ = y.is_eof();

        if (is_eof_ && y_is_eof_)
        {
            return true;  // both are EOF
        }
        else if (is_eof_ ^ y_is_eof_)
        {
            return false; // one is EOF, one isn't
        }
        else if (!IP::same_input(y))
        {
            return false;
        }
        else
        {
            return this->m_index == y.m_index;
        }
    }
};


template<
    typename Iterator,
    typename InputPolicy,
    typename OwnershipPolicy
>
void swap(memoize_iterator<Iterator, InputPolicy, OwnershipPolicy> &x,
          memoize_iterator<Iterator, InputPolicy, OwnershipPolicy> &y)
{
    x.swap(y);
}

namespace impl {

    template <typename T>
    inline void mp_swap(T& t1, T& t2)
    {
        using std::swap;
        //using boost::spirit::swap;
        swap(t1, t2);
    }
}


}} // namespace boost::spirit

#endif // BOOST_SPIRIT_ITERATOR_MULTI_PASS_HPP


