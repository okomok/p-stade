

struct X
{
    typedef int type;
};

template< class T >
typename X::type
foo(typename X::type a)
{
    typename X::type b = 0;
    return b;
}

template< class T >
X::type
bar(X::type a)
{
    X::type b = 0;
    return b;
}

int main()
{
    ::foo<double>(1);
    ::bar<double>(1);
}

