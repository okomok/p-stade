//#include <pstade/../libs/oven/test/concatenate_range.cpp>


#include <pstade/contract.hpp>


struct my_vector
{
    explicit my_vector(int sz) :
        m_size(sz)
    { }

    void resize(int newsize)
    {
        PSTADE_COPY_OLDOF(m_size, old)
        PSTADE_PRECONDITION
        (
            (newsize >= 0)
        )
        PSTADE_POSTCONDITION(void)
        (
            (m_size == newsize)
            (newsize > old.of(m_size) ? some_condition() : true)
        )

        m_size = newsize;

        PSTADE_RETURN(void);
    }

    bool some_condition() const
    {
        return true;
    }

private:
    int m_size;
};


int main()
{
    my_vector vec(10);
    vec.resize(16);

    return 0;
}
