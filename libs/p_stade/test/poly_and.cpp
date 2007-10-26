

#include <pstade/value_based.hpp>
#include <pstade/poly.hpp>
#include <pstade/clone_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <pstade/unit_test.hpp>

struct my_base
{
    virtual ~my_base() {}
    virtual int id() const = 0;
    virtual my_base *clone() const = 0;
};

// Clonable: http://tinyurl.com/2pks3r
my_base *new_clone(my_base const &b)
{
    return b.clone();
}

struct my_derived : my_base
{
    virtual int id() const { return 123; }
    virtual my_base *clone() const { return new my_derived(); }
};

void pstade_unit_test()
{
    using namespace pstade;

    {// shared
        value_based< boost::shared_ptr<my_base> > v = my_derived();
        BOOST_CHECK(v->id() == 123);
    }
    {// heap, strong assign, nothrow swap
        value_based< clone_ptr<my_base> > v = my_derived();
        BOOST_CHECK(v->id() == 123);
    }
    {// stack, basic assign
        poly<my_base> v = my_derived();
        BOOST_CHECK(v->id() == 123);
    }
}
