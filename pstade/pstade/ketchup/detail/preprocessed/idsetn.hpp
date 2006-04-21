
namespace pstade { namespace ketchup {

    template< UINT Dummy = 0 >
    struct idset0;
    template< >
    struct idset0<0>
    {
        static bool contains(UINT)
        {
            return false;
        }
    };

    template<
        UINT ID0
    >
    struct idset1
    {
        static bool contains(UINT id)
        {
            if (ID0 == id) { return true; }

            return false;
        }
    };

    template<
        UINT ID0 , UINT ID1
    >
    struct idset2
    {
        static bool contains(UINT id)
        {
            if (ID0 == id) { return true; }
            if (ID1 == id) { return true; }

            return false;
        }
    };

    template<
        UINT ID0 , UINT ID1 , UINT ID2
    >
    struct idset3
    {
        static bool contains(UINT id)
        {
            if (ID0 == id) { return true; }
            if (ID1 == id) { return true; }
            if (ID2 == id) { return true; }

            return false;
        }
    };

    template<
        UINT ID0 , UINT ID1 , UINT ID2 , UINT ID3
    >
    struct idset4
    {
        static bool contains(UINT id)
        {
            if (ID0 == id) { return true; }
            if (ID1 == id) { return true; }
            if (ID2 == id) { return true; }
            if (ID3 == id) { return true; }

            return false;
        }
    };

    template<
        UINT ID0 , UINT ID1 , UINT ID2 , UINT ID3 , UINT ID4
    >
    struct idset5
    {
        static bool contains(UINT id)
        {
            if (ID0 == id) { return true; }
            if (ID1 == id) { return true; }
            if (ID2 == id) { return true; }
            if (ID3 == id) { return true; }
            if (ID4 == id) { return true; }

            return false;
        }
    };

    template<
        UINT ID0 , UINT ID1 , UINT ID2 , UINT ID3 , UINT ID4 , UINT ID5
    >
    struct idset6
    {
        static bool contains(UINT id)
        {
            if (ID0 == id) { return true; }
            if (ID1 == id) { return true; }
            if (ID2 == id) { return true; }
            if (ID3 == id) { return true; }
            if (ID4 == id) { return true; }
            if (ID5 == id) { return true; }

            return false;
        }
    };

    template<
        UINT ID0 , UINT ID1 , UINT ID2 , UINT ID3 , UINT ID4 , UINT ID5 , UINT ID6
    >
    struct idset7
    {
        static bool contains(UINT id)
        {
            if (ID0 == id) { return true; }
            if (ID1 == id) { return true; }
            if (ID2 == id) { return true; }
            if (ID3 == id) { return true; }
            if (ID4 == id) { return true; }
            if (ID5 == id) { return true; }
            if (ID6 == id) { return true; }

            return false;
        }
    };

    template<
        UINT ID0 , UINT ID1 , UINT ID2 , UINT ID3 , UINT ID4 , UINT ID5 , UINT ID6 , UINT ID7
    >
    struct idset8
    {
        static bool contains(UINT id)
        {
            if (ID0 == id) { return true; }
            if (ID1 == id) { return true; }
            if (ID2 == id) { return true; }
            if (ID3 == id) { return true; }
            if (ID4 == id) { return true; }
            if (ID5 == id) { return true; }
            if (ID6 == id) { return true; }
            if (ID7 == id) { return true; }

            return false;
        }
    };

    template<
        UINT ID0 , UINT ID1 , UINT ID2 , UINT ID3 , UINT ID4 , UINT ID5 , UINT ID6 , UINT ID7 , UINT ID8
    >
    struct idset9
    {
        static bool contains(UINT id)
        {
            if (ID0 == id) { return true; }
            if (ID1 == id) { return true; }
            if (ID2 == id) { return true; }
            if (ID3 == id) { return true; }
            if (ID4 == id) { return true; }
            if (ID5 == id) { return true; }
            if (ID6 == id) { return true; }
            if (ID7 == id) { return true; }
            if (ID8 == id) { return true; }

            return false;
        }
    };

    template<
        UINT ID0 , UINT ID1 , UINT ID2 , UINT ID3 , UINT ID4 , UINT ID5 , UINT ID6 , UINT ID7 , UINT ID8 , UINT ID9
    >
    struct idset10
    {
        static bool contains(UINT id)
        {
            if (ID0 == id) { return true; }
            if (ID1 == id) { return true; }
            if (ID2 == id) { return true; }
            if (ID3 == id) { return true; }
            if (ID4 == id) { return true; }
            if (ID5 == id) { return true; }
            if (ID6 == id) { return true; }
            if (ID7 == id) { return true; }
            if (ID8 == id) { return true; }
            if (ID9 == id) { return true; }

            return false;
        }
    };

    template<
        UINT ID0 , UINT ID1 , UINT ID2 , UINT ID3 , UINT ID4 , UINT ID5 , UINT ID6 , UINT ID7 , UINT ID8 , UINT ID9 , UINT ID10
    >
    struct idset11
    {
        static bool contains(UINT id)
        {
            if (ID0 == id) { return true; }
            if (ID1 == id) { return true; }
            if (ID2 == id) { return true; }
            if (ID3 == id) { return true; }
            if (ID4 == id) { return true; }
            if (ID5 == id) { return true; }
            if (ID6 == id) { return true; }
            if (ID7 == id) { return true; }
            if (ID8 == id) { return true; }
            if (ID9 == id) { return true; }
            if (ID10 == id) { return true; }

            return false;
        }
    };

    template<
        UINT ID0 , UINT ID1 , UINT ID2 , UINT ID3 , UINT ID4 , UINT ID5 , UINT ID6 , UINT ID7 , UINT ID8 , UINT ID9 , UINT ID10 , UINT ID11
    >
    struct idset12
    {
        static bool contains(UINT id)
        {
            if (ID0 == id) { return true; }
            if (ID1 == id) { return true; }
            if (ID2 == id) { return true; }
            if (ID3 == id) { return true; }
            if (ID4 == id) { return true; }
            if (ID5 == id) { return true; }
            if (ID6 == id) { return true; }
            if (ID7 == id) { return true; }
            if (ID8 == id) { return true; }
            if (ID9 == id) { return true; }
            if (ID10 == id) { return true; }
            if (ID11 == id) { return true; }

            return false;
        }
    };

    template<
        UINT ID0 , UINT ID1 , UINT ID2 , UINT ID3 , UINT ID4 , UINT ID5 , UINT ID6 , UINT ID7 , UINT ID8 , UINT ID9 , UINT ID10 , UINT ID11 , UINT ID12
    >
    struct idset13
    {
        static bool contains(UINT id)
        {
            if (ID0 == id) { return true; }
            if (ID1 == id) { return true; }
            if (ID2 == id) { return true; }
            if (ID3 == id) { return true; }
            if (ID4 == id) { return true; }
            if (ID5 == id) { return true; }
            if (ID6 == id) { return true; }
            if (ID7 == id) { return true; }
            if (ID8 == id) { return true; }
            if (ID9 == id) { return true; }
            if (ID10 == id) { return true; }
            if (ID11 == id) { return true; }
            if (ID12 == id) { return true; }

            return false;
        }
    };

    template<
        UINT ID0 , UINT ID1 , UINT ID2 , UINT ID3 , UINT ID4 , UINT ID5 , UINT ID6 , UINT ID7 , UINT ID8 , UINT ID9 , UINT ID10 , UINT ID11 , UINT ID12 , UINT ID13
    >
    struct idset14
    {
        static bool contains(UINT id)
        {
            if (ID0 == id) { return true; }
            if (ID1 == id) { return true; }
            if (ID2 == id) { return true; }
            if (ID3 == id) { return true; }
            if (ID4 == id) { return true; }
            if (ID5 == id) { return true; }
            if (ID6 == id) { return true; }
            if (ID7 == id) { return true; }
            if (ID8 == id) { return true; }
            if (ID9 == id) { return true; }
            if (ID10 == id) { return true; }
            if (ID11 == id) { return true; }
            if (ID12 == id) { return true; }
            if (ID13 == id) { return true; }

            return false;
        }
    };

    template<
        UINT ID0 , UINT ID1 , UINT ID2 , UINT ID3 , UINT ID4 , UINT ID5 , UINT ID6 , UINT ID7 , UINT ID8 , UINT ID9 , UINT ID10 , UINT ID11 , UINT ID12 , UINT ID13 , UINT ID14
    >
    struct idset15
    {
        static bool contains(UINT id)
        {
            if (ID0 == id) { return true; }
            if (ID1 == id) { return true; }
            if (ID2 == id) { return true; }
            if (ID3 == id) { return true; }
            if (ID4 == id) { return true; }
            if (ID5 == id) { return true; }
            if (ID6 == id) { return true; }
            if (ID7 == id) { return true; }
            if (ID8 == id) { return true; }
            if (ID9 == id) { return true; }
            if (ID10 == id) { return true; }
            if (ID11 == id) { return true; }
            if (ID12 == id) { return true; }
            if (ID13 == id) { return true; }
            if (ID14 == id) { return true; }

            return false;
        }
    };

    template<
        UINT ID0 , UINT ID1 , UINT ID2 , UINT ID3 , UINT ID4 , UINT ID5 , UINT ID6 , UINT ID7 , UINT ID8 , UINT ID9 , UINT ID10 , UINT ID11 , UINT ID12 , UINT ID13 , UINT ID14 , UINT ID15
    >
    struct idset16
    {
        static bool contains(UINT id)
        {
            if (ID0 == id) { return true; }
            if (ID1 == id) { return true; }
            if (ID2 == id) { return true; }
            if (ID3 == id) { return true; }
            if (ID4 == id) { return true; }
            if (ID5 == id) { return true; }
            if (ID6 == id) { return true; }
            if (ID7 == id) { return true; }
            if (ID8 == id) { return true; }
            if (ID9 == id) { return true; }
            if (ID10 == id) { return true; }
            if (ID11 == id) { return true; }
            if (ID12 == id) { return true; }
            if (ID13 == id) { return true; }
            if (ID14 == id) { return true; }
            if (ID15 == id) { return true; }

            return false;
        }
    };

    template<
        UINT ID0 , UINT ID1 , UINT ID2 , UINT ID3 , UINT ID4 , UINT ID5 , UINT ID6 , UINT ID7 , UINT ID8 , UINT ID9 , UINT ID10 , UINT ID11 , UINT ID12 , UINT ID13 , UINT ID14 , UINT ID15 , UINT ID16
    >
    struct idset17
    {
        static bool contains(UINT id)
        {
            if (ID0 == id) { return true; }
            if (ID1 == id) { return true; }
            if (ID2 == id) { return true; }
            if (ID3 == id) { return true; }
            if (ID4 == id) { return true; }
            if (ID5 == id) { return true; }
            if (ID6 == id) { return true; }
            if (ID7 == id) { return true; }
            if (ID8 == id) { return true; }
            if (ID9 == id) { return true; }
            if (ID10 == id) { return true; }
            if (ID11 == id) { return true; }
            if (ID12 == id) { return true; }
            if (ID13 == id) { return true; }
            if (ID14 == id) { return true; }
            if (ID15 == id) { return true; }
            if (ID16 == id) { return true; }

            return false;
        }
    };

    template<
        UINT ID0 , UINT ID1 , UINT ID2 , UINT ID3 , UINT ID4 , UINT ID5 , UINT ID6 , UINT ID7 , UINT ID8 , UINT ID9 , UINT ID10 , UINT ID11 , UINT ID12 , UINT ID13 , UINT ID14 , UINT ID15 , UINT ID16 , UINT ID17
    >
    struct idset18
    {
        static bool contains(UINT id)
        {
            if (ID0 == id) { return true; }
            if (ID1 == id) { return true; }
            if (ID2 == id) { return true; }
            if (ID3 == id) { return true; }
            if (ID4 == id) { return true; }
            if (ID5 == id) { return true; }
            if (ID6 == id) { return true; }
            if (ID7 == id) { return true; }
            if (ID8 == id) { return true; }
            if (ID9 == id) { return true; }
            if (ID10 == id) { return true; }
            if (ID11 == id) { return true; }
            if (ID12 == id) { return true; }
            if (ID13 == id) { return true; }
            if (ID14 == id) { return true; }
            if (ID15 == id) { return true; }
            if (ID16 == id) { return true; }
            if (ID17 == id) { return true; }

            return false;
        }
    };

    template<
        UINT ID0 , UINT ID1 , UINT ID2 , UINT ID3 , UINT ID4 , UINT ID5 , UINT ID6 , UINT ID7 , UINT ID8 , UINT ID9 , UINT ID10 , UINT ID11 , UINT ID12 , UINT ID13 , UINT ID14 , UINT ID15 , UINT ID16 , UINT ID17 , UINT ID18
    >
    struct idset19
    {
        static bool contains(UINT id)
        {
            if (ID0 == id) { return true; }
            if (ID1 == id) { return true; }
            if (ID2 == id) { return true; }
            if (ID3 == id) { return true; }
            if (ID4 == id) { return true; }
            if (ID5 == id) { return true; }
            if (ID6 == id) { return true; }
            if (ID7 == id) { return true; }
            if (ID8 == id) { return true; }
            if (ID9 == id) { return true; }
            if (ID10 == id) { return true; }
            if (ID11 == id) { return true; }
            if (ID12 == id) { return true; }
            if (ID13 == id) { return true; }
            if (ID14 == id) { return true; }
            if (ID15 == id) { return true; }
            if (ID16 == id) { return true; }
            if (ID17 == id) { return true; }
            if (ID18 == id) { return true; }

            return false;
        }
    };

    template<
        UINT ID0 , UINT ID1 , UINT ID2 , UINT ID3 , UINT ID4 , UINT ID5 , UINT ID6 , UINT ID7 , UINT ID8 , UINT ID9 , UINT ID10 , UINT ID11 , UINT ID12 , UINT ID13 , UINT ID14 , UINT ID15 , UINT ID16 , UINT ID17 , UINT ID18 , UINT ID19
    >
    struct idset20
    {
        static bool contains(UINT id)
        {
            if (ID0 == id) { return true; }
            if (ID1 == id) { return true; }
            if (ID2 == id) { return true; }
            if (ID3 == id) { return true; }
            if (ID4 == id) { return true; }
            if (ID5 == id) { return true; }
            if (ID6 == id) { return true; }
            if (ID7 == id) { return true; }
            if (ID8 == id) { return true; }
            if (ID9 == id) { return true; }
            if (ID10 == id) { return true; }
            if (ID11 == id) { return true; }
            if (ID12 == id) { return true; }
            if (ID13 == id) { return true; }
            if (ID14 == id) { return true; }
            if (ID15 == id) { return true; }
            if (ID16 == id) { return true; }
            if (ID17 == id) { return true; }
            if (ID18 == id) { return true; }
            if (ID19 == id) { return true; }

            return false;
        }
    };

    template<
        UINT ID0 , UINT ID1 , UINT ID2 , UINT ID3 , UINT ID4 , UINT ID5 , UINT ID6 , UINT ID7 , UINT ID8 , UINT ID9 , UINT ID10 , UINT ID11 , UINT ID12 , UINT ID13 , UINT ID14 , UINT ID15 , UINT ID16 , UINT ID17 , UINT ID18 , UINT ID19 , UINT ID20
    >
    struct idset21
    {
        static bool contains(UINT id)
        {
            if (ID0 == id) { return true; }
            if (ID1 == id) { return true; }
            if (ID2 == id) { return true; }
            if (ID3 == id) { return true; }
            if (ID4 == id) { return true; }
            if (ID5 == id) { return true; }
            if (ID6 == id) { return true; }
            if (ID7 == id) { return true; }
            if (ID8 == id) { return true; }
            if (ID9 == id) { return true; }
            if (ID10 == id) { return true; }
            if (ID11 == id) { return true; }
            if (ID12 == id) { return true; }
            if (ID13 == id) { return true; }
            if (ID14 == id) { return true; }
            if (ID15 == id) { return true; }
            if (ID16 == id) { return true; }
            if (ID17 == id) { return true; }
            if (ID18 == id) { return true; }
            if (ID19 == id) { return true; }
            if (ID20 == id) { return true; }

            return false;
        }
    };

    template<
        UINT ID0 , UINT ID1 , UINT ID2 , UINT ID3 , UINT ID4 , UINT ID5 , UINT ID6 , UINT ID7 , UINT ID8 , UINT ID9 , UINT ID10 , UINT ID11 , UINT ID12 , UINT ID13 , UINT ID14 , UINT ID15 , UINT ID16 , UINT ID17 , UINT ID18 , UINT ID19 , UINT ID20 , UINT ID21
    >
    struct idset22
    {
        static bool contains(UINT id)
        {
            if (ID0 == id) { return true; }
            if (ID1 == id) { return true; }
            if (ID2 == id) { return true; }
            if (ID3 == id) { return true; }
            if (ID4 == id) { return true; }
            if (ID5 == id) { return true; }
            if (ID6 == id) { return true; }
            if (ID7 == id) { return true; }
            if (ID8 == id) { return true; }
            if (ID9 == id) { return true; }
            if (ID10 == id) { return true; }
            if (ID11 == id) { return true; }
            if (ID12 == id) { return true; }
            if (ID13 == id) { return true; }
            if (ID14 == id) { return true; }
            if (ID15 == id) { return true; }
            if (ID16 == id) { return true; }
            if (ID17 == id) { return true; }
            if (ID18 == id) { return true; }
            if (ID19 == id) { return true; }
            if (ID20 == id) { return true; }
            if (ID21 == id) { return true; }

            return false;
        }
    };

    template<
        UINT ID0 , UINT ID1 , UINT ID2 , UINT ID3 , UINT ID4 , UINT ID5 , UINT ID6 , UINT ID7 , UINT ID8 , UINT ID9 , UINT ID10 , UINT ID11 , UINT ID12 , UINT ID13 , UINT ID14 , UINT ID15 , UINT ID16 , UINT ID17 , UINT ID18 , UINT ID19 , UINT ID20 , UINT ID21 , UINT ID22
    >
    struct idset23
    {
        static bool contains(UINT id)
        {
            if (ID0 == id) { return true; }
            if (ID1 == id) { return true; }
            if (ID2 == id) { return true; }
            if (ID3 == id) { return true; }
            if (ID4 == id) { return true; }
            if (ID5 == id) { return true; }
            if (ID6 == id) { return true; }
            if (ID7 == id) { return true; }
            if (ID8 == id) { return true; }
            if (ID9 == id) { return true; }
            if (ID10 == id) { return true; }
            if (ID11 == id) { return true; }
            if (ID12 == id) { return true; }
            if (ID13 == id) { return true; }
            if (ID14 == id) { return true; }
            if (ID15 == id) { return true; }
            if (ID16 == id) { return true; }
            if (ID17 == id) { return true; }
            if (ID18 == id) { return true; }
            if (ID19 == id) { return true; }
            if (ID20 == id) { return true; }
            if (ID21 == id) { return true; }
            if (ID22 == id) { return true; }

            return false;
        }
    };

    template<
        UINT ID0 , UINT ID1 , UINT ID2 , UINT ID3 , UINT ID4 , UINT ID5 , UINT ID6 , UINT ID7 , UINT ID8 , UINT ID9 , UINT ID10 , UINT ID11 , UINT ID12 , UINT ID13 , UINT ID14 , UINT ID15 , UINT ID16 , UINT ID17 , UINT ID18 , UINT ID19 , UINT ID20 , UINT ID21 , UINT ID22 , UINT ID23
    >
    struct idset24
    {
        static bool contains(UINT id)
        {
            if (ID0 == id) { return true; }
            if (ID1 == id) { return true; }
            if (ID2 == id) { return true; }
            if (ID3 == id) { return true; }
            if (ID4 == id) { return true; }
            if (ID5 == id) { return true; }
            if (ID6 == id) { return true; }
            if (ID7 == id) { return true; }
            if (ID8 == id) { return true; }
            if (ID9 == id) { return true; }
            if (ID10 == id) { return true; }
            if (ID11 == id) { return true; }
            if (ID12 == id) { return true; }
            if (ID13 == id) { return true; }
            if (ID14 == id) { return true; }
            if (ID15 == id) { return true; }
            if (ID16 == id) { return true; }
            if (ID17 == id) { return true; }
            if (ID18 == id) { return true; }
            if (ID19 == id) { return true; }
            if (ID20 == id) { return true; }
            if (ID21 == id) { return true; }
            if (ID22 == id) { return true; }
            if (ID23 == id) { return true; }

            return false;
        }
    };

    template<
        UINT ID0 , UINT ID1 , UINT ID2 , UINT ID3 , UINT ID4 , UINT ID5 , UINT ID6 , UINT ID7 , UINT ID8 , UINT ID9 , UINT ID10 , UINT ID11 , UINT ID12 , UINT ID13 , UINT ID14 , UINT ID15 , UINT ID16 , UINT ID17 , UINT ID18 , UINT ID19 , UINT ID20 , UINT ID21 , UINT ID22 , UINT ID23 , UINT ID24
    >
    struct idset25
    {
        static bool contains(UINT id)
        {
            if (ID0 == id) { return true; }
            if (ID1 == id) { return true; }
            if (ID2 == id) { return true; }
            if (ID3 == id) { return true; }
            if (ID4 == id) { return true; }
            if (ID5 == id) { return true; }
            if (ID6 == id) { return true; }
            if (ID7 == id) { return true; }
            if (ID8 == id) { return true; }
            if (ID9 == id) { return true; }
            if (ID10 == id) { return true; }
            if (ID11 == id) { return true; }
            if (ID12 == id) { return true; }
            if (ID13 == id) { return true; }
            if (ID14 == id) { return true; }
            if (ID15 == id) { return true; }
            if (ID16 == id) { return true; }
            if (ID17 == id) { return true; }
            if (ID18 == id) { return true; }
            if (ID19 == id) { return true; }
            if (ID20 == id) { return true; }
            if (ID21 == id) { return true; }
            if (ID22 == id) { return true; }
            if (ID23 == id) { return true; }
            if (ID24 == id) { return true; }

            return false;
        }
    };

    template<
        UINT ID0 , UINT ID1 , UINT ID2 , UINT ID3 , UINT ID4 , UINT ID5 , UINT ID6 , UINT ID7 , UINT ID8 , UINT ID9 , UINT ID10 , UINT ID11 , UINT ID12 , UINT ID13 , UINT ID14 , UINT ID15 , UINT ID16 , UINT ID17 , UINT ID18 , UINT ID19 , UINT ID20 , UINT ID21 , UINT ID22 , UINT ID23 , UINT ID24 , UINT ID25
    >
    struct idset26
    {
        static bool contains(UINT id)
        {
            if (ID0 == id) { return true; }
            if (ID1 == id) { return true; }
            if (ID2 == id) { return true; }
            if (ID3 == id) { return true; }
            if (ID4 == id) { return true; }
            if (ID5 == id) { return true; }
            if (ID6 == id) { return true; }
            if (ID7 == id) { return true; }
            if (ID8 == id) { return true; }
            if (ID9 == id) { return true; }
            if (ID10 == id) { return true; }
            if (ID11 == id) { return true; }
            if (ID12 == id) { return true; }
            if (ID13 == id) { return true; }
            if (ID14 == id) { return true; }
            if (ID15 == id) { return true; }
            if (ID16 == id) { return true; }
            if (ID17 == id) { return true; }
            if (ID18 == id) { return true; }
            if (ID19 == id) { return true; }
            if (ID20 == id) { return true; }
            if (ID21 == id) { return true; }
            if (ID22 == id) { return true; }
            if (ID23 == id) { return true; }
            if (ID24 == id) { return true; }
            if (ID25 == id) { return true; }

            return false;
        }
    };

    template<
        UINT ID0 , UINT ID1 , UINT ID2 , UINT ID3 , UINT ID4 , UINT ID5 , UINT ID6 , UINT ID7 , UINT ID8 , UINT ID9 , UINT ID10 , UINT ID11 , UINT ID12 , UINT ID13 , UINT ID14 , UINT ID15 , UINT ID16 , UINT ID17 , UINT ID18 , UINT ID19 , UINT ID20 , UINT ID21 , UINT ID22 , UINT ID23 , UINT ID24 , UINT ID25 , UINT ID26
    >
    struct idset27
    {
        static bool contains(UINT id)
        {
            if (ID0 == id) { return true; }
            if (ID1 == id) { return true; }
            if (ID2 == id) { return true; }
            if (ID3 == id) { return true; }
            if (ID4 == id) { return true; }
            if (ID5 == id) { return true; }
            if (ID6 == id) { return true; }
            if (ID7 == id) { return true; }
            if (ID8 == id) { return true; }
            if (ID9 == id) { return true; }
            if (ID10 == id) { return true; }
            if (ID11 == id) { return true; }
            if (ID12 == id) { return true; }
            if (ID13 == id) { return true; }
            if (ID14 == id) { return true; }
            if (ID15 == id) { return true; }
            if (ID16 == id) { return true; }
            if (ID17 == id) { return true; }
            if (ID18 == id) { return true; }
            if (ID19 == id) { return true; }
            if (ID20 == id) { return true; }
            if (ID21 == id) { return true; }
            if (ID22 == id) { return true; }
            if (ID23 == id) { return true; }
            if (ID24 == id) { return true; }
            if (ID25 == id) { return true; }
            if (ID26 == id) { return true; }

            return false;
        }
    };

    template<
        UINT ID0 , UINT ID1 , UINT ID2 , UINT ID3 , UINT ID4 , UINT ID5 , UINT ID6 , UINT ID7 , UINT ID8 , UINT ID9 , UINT ID10 , UINT ID11 , UINT ID12 , UINT ID13 , UINT ID14 , UINT ID15 , UINT ID16 , UINT ID17 , UINT ID18 , UINT ID19 , UINT ID20 , UINT ID21 , UINT ID22 , UINT ID23 , UINT ID24 , UINT ID25 , UINT ID26 , UINT ID27
    >
    struct idset28
    {
        static bool contains(UINT id)
        {
            if (ID0 == id) { return true; }
            if (ID1 == id) { return true; }
            if (ID2 == id) { return true; }
            if (ID3 == id) { return true; }
            if (ID4 == id) { return true; }
            if (ID5 == id) { return true; }
            if (ID6 == id) { return true; }
            if (ID7 == id) { return true; }
            if (ID8 == id) { return true; }
            if (ID9 == id) { return true; }
            if (ID10 == id) { return true; }
            if (ID11 == id) { return true; }
            if (ID12 == id) { return true; }
            if (ID13 == id) { return true; }
            if (ID14 == id) { return true; }
            if (ID15 == id) { return true; }
            if (ID16 == id) { return true; }
            if (ID17 == id) { return true; }
            if (ID18 == id) { return true; }
            if (ID19 == id) { return true; }
            if (ID20 == id) { return true; }
            if (ID21 == id) { return true; }
            if (ID22 == id) { return true; }
            if (ID23 == id) { return true; }
            if (ID24 == id) { return true; }
            if (ID25 == id) { return true; }
            if (ID26 == id) { return true; }
            if (ID27 == id) { return true; }

            return false;
        }
    };

    template<
        UINT ID0 , UINT ID1 , UINT ID2 , UINT ID3 , UINT ID4 , UINT ID5 , UINT ID6 , UINT ID7 , UINT ID8 , UINT ID9 , UINT ID10 , UINT ID11 , UINT ID12 , UINT ID13 , UINT ID14 , UINT ID15 , UINT ID16 , UINT ID17 , UINT ID18 , UINT ID19 , UINT ID20 , UINT ID21 , UINT ID22 , UINT ID23 , UINT ID24 , UINT ID25 , UINT ID26 , UINT ID27 , UINT ID28
    >
    struct idset29
    {
        static bool contains(UINT id)
        {
            if (ID0 == id) { return true; }
            if (ID1 == id) { return true; }
            if (ID2 == id) { return true; }
            if (ID3 == id) { return true; }
            if (ID4 == id) { return true; }
            if (ID5 == id) { return true; }
            if (ID6 == id) { return true; }
            if (ID7 == id) { return true; }
            if (ID8 == id) { return true; }
            if (ID9 == id) { return true; }
            if (ID10 == id) { return true; }
            if (ID11 == id) { return true; }
            if (ID12 == id) { return true; }
            if (ID13 == id) { return true; }
            if (ID14 == id) { return true; }
            if (ID15 == id) { return true; }
            if (ID16 == id) { return true; }
            if (ID17 == id) { return true; }
            if (ID18 == id) { return true; }
            if (ID19 == id) { return true; }
            if (ID20 == id) { return true; }
            if (ID21 == id) { return true; }
            if (ID22 == id) { return true; }
            if (ID23 == id) { return true; }
            if (ID24 == id) { return true; }
            if (ID25 == id) { return true; }
            if (ID26 == id) { return true; }
            if (ID27 == id) { return true; }
            if (ID28 == id) { return true; }

            return false;
        }
    };

    template<
        UINT ID0 , UINT ID1 , UINT ID2 , UINT ID3 , UINT ID4 , UINT ID5 , UINT ID6 , UINT ID7 , UINT ID8 , UINT ID9 , UINT ID10 , UINT ID11 , UINT ID12 , UINT ID13 , UINT ID14 , UINT ID15 , UINT ID16 , UINT ID17 , UINT ID18 , UINT ID19 , UINT ID20 , UINT ID21 , UINT ID22 , UINT ID23 , UINT ID24 , UINT ID25 , UINT ID26 , UINT ID27 , UINT ID28 , UINT ID29
    >
    struct idset30
    {
        static bool contains(UINT id)
        {
            if (ID0 == id) { return true; }
            if (ID1 == id) { return true; }
            if (ID2 == id) { return true; }
            if (ID3 == id) { return true; }
            if (ID4 == id) { return true; }
            if (ID5 == id) { return true; }
            if (ID6 == id) { return true; }
            if (ID7 == id) { return true; }
            if (ID8 == id) { return true; }
            if (ID9 == id) { return true; }
            if (ID10 == id) { return true; }
            if (ID11 == id) { return true; }
            if (ID12 == id) { return true; }
            if (ID13 == id) { return true; }
            if (ID14 == id) { return true; }
            if (ID15 == id) { return true; }
            if (ID16 == id) { return true; }
            if (ID17 == id) { return true; }
            if (ID18 == id) { return true; }
            if (ID19 == id) { return true; }
            if (ID20 == id) { return true; }
            if (ID21 == id) { return true; }
            if (ID22 == id) { return true; }
            if (ID23 == id) { return true; }
            if (ID24 == id) { return true; }
            if (ID25 == id) { return true; }
            if (ID26 == id) { return true; }
            if (ID27 == id) { return true; }
            if (ID28 == id) { return true; }
            if (ID29 == id) { return true; }

            return false;
        }
    };

} } 
