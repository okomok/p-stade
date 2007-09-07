


template<class X, class A>
void foo(A&, X* = 0)
{ }

template<class X, class A>
void foo(A const&, X* = 0)
{ }


int main()
{
    double *p = 0;
    int const i = 0;
    foo<double>(i, p);
}

