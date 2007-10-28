#ifndef RAYLET_ANY_INDEXED_HPP
#define RAYLET_ANY_INDEXED_HPP

#include <boost/ref.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/range/size.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/apply.hpp>

namespace raylet
{

template<typename Indexed>
struct indexed_type
{
  typedef typename Indexed::reference type;
};

template<typename Indexed>
struct indexed_size_type
{
  typedef typename Indexed::size_type type;
};

namespace detail
{
  namespace mpl = boost::mpl;
  template<typename T>
  struct const_reference
  {
    typedef typename mpl::eval_if<
      boost::is_reference<T>,
        mpl::apply<
          boost::add_reference<
            boost::add_const<
              boost::remove_reference<mpl::_1> > >, T>,
      mpl::identity<T>
      >::type type;
  };

  template<typename T>
  struct const_indexed_type
  {
    typedef typename const_reference<typename indexed_type<T>::type>::type type;
  };
}

template<typename Indexed>
inline typename indexed_size_type<Indexed>::type size(const Indexed& ixd)
{
  return boost::size(ixd);
}

template<typename Indexed>
inline typename indexed_type<Indexed>::type at(
  Indexed& ixd, typename indexed_size_type<Indexed>::type i
  )
{
  return ixd[i];
}

template<typename Indexed>
inline typename detail::const_indexed_type<Indexed>::type
at(Indexed const& ixd, typename indexed_size_type<Indexed>::type i)
{
  return ixd[i];
}

template<typename Indexed, typename DiffType = std::ptrdiff_t>
class indexed_iterator
     : public boost::iterator_facade<
        indexed_iterator<Indexed, DiffType>,
        typename boost::remove_reference<typename indexed_type<Indexed>::type>::type,
        boost::random_access_traversal_tag,
        typename indexed_type<Indexed>::type,
        DiffType
        >
{
  typedef indexed_iterator<Indexed, DiffType> this_t;
  typedef typename indexed_size_type<Indexed>::type size_type;
  Indexed* pidx_;
  size_type i_;
public:
  indexed_iterator()
       :pidx_(0), i_(0)
  {}
  indexed_iterator(Indexed& idx, size_type i)
       :pidx_(&idx), i_(i)
  {}

  void increment(){++i_;}
  void decrement(){--i_;}
  bool equal(this_t const& other)const
  {
    return other.i_ == i_ && other.pidx_ == pidx_;
  }
  DiffType distance_to(this_t const& other)const
  {
    return static_cast<DiffType>(other.i_) - static_cast<DiffType>(i_);
  }
  reference dereference()const{return at(*pidx_, i_);}
};

template<typename Indexed, typename DiffType = std::ptrdiff_t>
class const_indexed_iterator
     : public boost::iterator_facade<
        const_indexed_iterator<Indexed, DiffType>,
        typename boost::remove_reference<typename detail::const_indexed_type<Indexed>::type>::type,
        boost::random_access_traversal_tag,
        typename detail::const_indexed_type<Indexed>::type,
        DiffType
        >
{
  typedef const_indexed_iterator<Indexed, DiffType> this_t;
  typedef typename indexed_size_type<Indexed>::type size_type;
  const Indexed* pidx_;
  size_type i_;
public:
  const_indexed_iterator()
       :pidx_(0), i_(0)
  {}
  const_indexed_iterator(const Indexed& idx, size_type i)
       :pidx_(&idx), i_(i)
  {}

  void increment(){++i_;}
  void decrement(){--i_;}
  bool equal(this_t const& other)const
  {
    return other.i_ == i_ && other.pidx_ == pidx_;
  }
  DiffType distance_to(this_t const& other)const
  {
    return static_cast<DiffType>(other.i_) - static_cast<DiffType>(i_);
  }
  reference dereference()const{return at(*pidx_, i_);}
};

template<typename Indexed>
inline indexed_iterator<Indexed, std::ptrdiff_t> make_indexed_iterator(Indexed&  idx, typename indexed_size_type<Indexed>::type i)
{
  return indexed_iterator<Indexed, std::ptrdiff_t>(idx, i);
}

template<typename Indexed>
inline const_indexed_iterator<Indexed, std::ptrdiff_t> make_indexed_iterator(Indexed const& idx, typename indexed_size_type<Indexed>::type i)
{
  return const_indexed_iterator<Indexed, std::ptrdiff_t>(idx, i);
}

namespace detail
{
  template<typename T, typename SizeType>
  class indexed_holder_base
  {
  protected:
    typedef typename detail::const_reference<T>::type const_t;
  public:
    virtual SizeType size()const = 0;
    virtual T at(SizeType i) = 0;
    virtual const_t at(SizeType i)const = 0;
    virtual indexed_holder_base<T, SizeType>* clone()const = 0;
  };
  
  template<typename T, typename SizeType, typename Indexed>
  class indexed_holder : public indexed_holder_base<T, SizeType>
  {
    Indexed ixd_;
  public:
    explicit indexed_holder(const Indexed& ixd)
         :ixd_(ixd)
    {}

    virtual SizeType size()const{return raylet::size(ixd_);}
    virtual T at(SizeType i){return raylet::at(ixd_, i);}
    virtual const_t at(SizeType i)const{return raylet::at(ixd_, i);}
    virtual indexed_holder_base<T, SizeType>* clone()const
    {
      return new indexed_holder<T, SizeType, Indexed>(*this);
    }
  };

  template<typename T, typename SizeType, typename Indexed>
  class indexed_holder<T, SizeType, boost::reference_wrapper<Indexed> >
       : public indexed_holder_base<T, SizeType>
  {
    Indexed* pixd_;
  public:
    explicit indexed_holder(const boost::reference_wrapper<Indexed> ixd)
         :pixd_(ixd.get_pointer())
    {}

    virtual SizeType size()const{return raylet::size(*pixd_);}
    virtual T at(SizeType i){return raylet::at(*pixd_, i);}
    virtual const_t at(SizeType i)const{return raylet::at(*pixd_, i);}
    virtual indexed_holder_base<T, SizeType>* clone()const
    {
      return new indexed_holder<T, SizeType, boost::reference_wrapper<Indexed> >(*this);
    }
  };

  template<typename T, typename SizeType, typename Value, std::size_t N>
  struct array_holder
       : public indexed_holder_base<T, SizeType>
  {
    Value* ptr_;
  public:
    explicit array_holder(Value* p)
         :ptr_(p)
    {}

    virtual SizeType size()const{return N;}
    virtual T at(SizeType i){return ptr_[i];}
    virtual const_t at(SizeType i)const{return ptr_[i];}
    virtual indexed_holder_base<T, SizeType>* clone()const
    {
      return new array_holder<T, SizeType, Value, N>(*this);
    }
  };
}

template<typename T, typename SizeType = std::size_t, typename DiffType = std::ptrdiff_t>
class any_indexed
{
  typedef any_indexed<T, SizeType, DiffType> this_t;
  detail::indexed_holder_base<T, SizeType>* pholder_;
public:
  typedef typename boost::remove_reference<T>::type value_type;
  typedef T reference;
  typedef typename detail::const_reference<reference>::type const_reference;
  typedef SizeType size_type;
  typedef DiffType difference_type;
  typedef indexed_iterator<this_t, difference_type> iterator;
  typedef const_indexed_iterator<this_t, difference_type> const_iterator;
  
  any_indexed()
       :pholder_(0)
  {}

  any_indexed(const this_t& other)
       :pholder_(other.clone())
  {}

  template<typename Indexed>
  any_indexed(const Indexed& idx)
       :pholder_(new detail::indexed_holder<T, SizeType, Indexed>(idx))
  {}

  template<typename Value, std::size_t N>
  any_indexed(Value (&a)[N])
       :pholder_(new detail::array_holder<T, SizeType, Value, N>(a))
  {}

  template<typename Value, std::size_t N>
  any_indexed(const Value (&a)[N])
       :pholder_(new detail::array_holder<T, SizeType, const Value, N>(a))
  {}

  void swap(this_t& other)
  {
    std::swap(pholder_, other.pholder_);
  }

  this_t& operator=(const this_t& other)
  {
    this_t tmp(other);
    tmp.swap(*this);
    return *this;
  }

  size_type size()const{return pholder_->size();}
  reference operator[](size_type i){return pholder_->at(i);}
  const_reference operator[](size_type i)const{return pholder_->at(i);}

  reference front(){return pholder_->at(0);}
  const_reference front()const{return pholder_->at(0);}
  reference back(){return pholder_->at(size()-1);}
  const_reference back()const{return pholder_->at(size()-1);}

  iterator begin(){return iterator(*this, 0);}
  const_iterator begin()const{return const_iterator(*this, 0);}
  iterator end(){return iterator(*this, size());}
  const_iterator end()const{return const_iterator(*this, size());}
};

}

#endif
