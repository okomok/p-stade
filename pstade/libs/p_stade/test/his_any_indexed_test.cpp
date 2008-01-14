
#include <boost/ptr_container/ptr_vector.hpp>
#include "any_indexed.hpp"
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <pstade/oven/indirected.hpp>
//#include <pstade/oven/any_indexed.hpp>

class Base
{
public:
  virtual ~Base(){}
  virtual void f()const = 0;
};

class Foo : public Base
{
public:
  virtual void f()const{ std::cout << "foo "; }
};

class Bar : public Base
{
public:
  virtual void f()const{ std::cout << "bar "; }
};

void print(const raylet::any_indexed<const Base&> a)
{
  typedef raylet::any_indexed<const Base&>::const_iterator iter_t;
  for(iter_t it=a.begin();it!=a.end();++it)
    it->f();
  std::cout << '\n';
}

int main()
{
  // 普通の配列
  Foo foo3[3];
  print(foo3);
  Bar bar3[3];
  print(bar3);

  // boost::ptr_vector
  boost::ptr_vector<Base> foobarbar;
  foobarbar.push_back(new Foo);
  foobarbar.push_back(new Bar);
  foobarbar.push_back(new Bar);
  print(boost::cref(foobarbar));

  // 生ポインタの配列
  Base* foobarfoo[3] = {&foo3[0], &bar3[1], &foo3[2]};
  print(foobarfoo|pstade::oven::indirected);

  // スマートポインタのvector
  std::vector<boost::shared_ptr<Base> > foofoobar(3);
  foofoobar[0].reset(new Foo);
  foofoobar[1].reset(new Foo);
  foofoobar[2].reset(new Bar);
  print(foofoobar|pstade::oven::indirected);
}
