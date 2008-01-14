
//#define POD

#if defined(POD)
struct A
{
    int m_i,  m_j;
};
#else
struct A
{
    A(int i, int j) : m_i(i), m_j(j)
    { }

private:
    int m_i, m_j;
};

#endif


A foo(int i, int j)
{
#if defined(POD)
   A a = {i, j};
   return a;
#else
    return A(i, j);
#endif
}

typedef A (*pfoo)(int, int);

int main()
{
    pfoo pf = &foo;
    pf(13,12);
}
