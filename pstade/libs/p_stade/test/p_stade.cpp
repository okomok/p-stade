

struct to_any
{
    template< class X >
    operator X&();
};


template<class X>
struct foo
{
    foo(int x = to_any()) { }
};


int main()
{
    foo<int> f(3);
}
