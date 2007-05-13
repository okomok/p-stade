
namespace pstade { namespace ketchup {
    struct begin_msg_mapn_entry_set
    {

        template< class Dummy = boost::mpl::void_ >
        struct begin_msg_map0
        {
            template< class Derived >
            static bool process(Derived& , HWND, UINT, WPARAM, LPARAM, LRESULT& , DWORD)
            {
                return false;
            }
        };

        template<
            class E0
        >
        struct begin_msg_map1
        {
            template< class Derived >
            static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
            {
                if (E0::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }

                return false;
            }
        };

        template<
            class E0 , class E1
        >
        struct begin_msg_map2
        {
            template< class Derived >
            static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
            {
                if (E0::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E1::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }

                return false;
            }
        };

        template<
            class E0 , class E1 , class E2
        >
        struct begin_msg_map3
        {
            template< class Derived >
            static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
            {
                if (E0::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E1::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E2::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }

                return false;
            }
        };

        template<
            class E0 , class E1 , class E2 , class E3
        >
        struct begin_msg_map4
        {
            template< class Derived >
            static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
            {
                if (E0::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E1::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E2::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E3::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }

                return false;
            }
        };

        template<
            class E0 , class E1 , class E2 , class E3 , class E4
        >
        struct begin_msg_map5
        {
            template< class Derived >
            static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
            {
                if (E0::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E1::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E2::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E3::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E4::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }

                return false;
            }
        };

        template<
            class E0 , class E1 , class E2 , class E3 , class E4 , class E5
        >
        struct begin_msg_map6
        {
            template< class Derived >
            static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
            {
                if (E0::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E1::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E2::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E3::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E4::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E5::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }

                return false;
            }
        };

        template<
            class E0 , class E1 , class E2 , class E3 , class E4 , class E5 , class E6
        >
        struct begin_msg_map7
        {
            template< class Derived >
            static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
            {
                if (E0::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E1::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E2::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E3::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E4::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E5::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E6::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }

                return false;
            }
        };

        template<
            class E0 , class E1 , class E2 , class E3 , class E4 , class E5 , class E6 , class E7
        >
        struct begin_msg_map8
        {
            template< class Derived >
            static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
            {
                if (E0::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E1::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E2::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E3::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E4::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E5::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E6::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E7::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }

                return false;
            }
        };

        template<
            class E0 , class E1 , class E2 , class E3 , class E4 , class E5 , class E6 , class E7 , class E8
        >
        struct begin_msg_map9
        {
            template< class Derived >
            static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
            {
                if (E0::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E1::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E2::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E3::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E4::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E5::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E6::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E7::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E8::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }

                return false;
            }
        };

        template<
            class E0 , class E1 , class E2 , class E3 , class E4 , class E5 , class E6 , class E7 , class E8 , class E9
        >
        struct begin_msg_map10
        {
            template< class Derived >
            static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
            {
                if (E0::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E1::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E2::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E3::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E4::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E5::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E6::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E7::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E8::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E9::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }

                return false;
            }
        };

        template<
            class E0 , class E1 , class E2 , class E3 , class E4 , class E5 , class E6 , class E7 , class E8 , class E9 , class E10
        >
        struct begin_msg_map11
        {
            template< class Derived >
            static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
            {
                if (E0::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E1::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E2::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E3::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E4::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E5::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E6::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E7::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E8::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E9::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E10::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }

                return false;
            }
        };

        template<
            class E0 , class E1 , class E2 , class E3 , class E4 , class E5 , class E6 , class E7 , class E8 , class E9 , class E10 , class E11
        >
        struct begin_msg_map12
        {
            template< class Derived >
            static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
            {
                if (E0::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E1::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E2::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E3::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E4::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E5::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E6::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E7::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E8::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E9::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E10::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E11::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }

                return false;
            }
        };

        template<
            class E0 , class E1 , class E2 , class E3 , class E4 , class E5 , class E6 , class E7 , class E8 , class E9 , class E10 , class E11 , class E12
        >
        struct begin_msg_map13
        {
            template< class Derived >
            static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
            {
                if (E0::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E1::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E2::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E3::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E4::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E5::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E6::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E7::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E8::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E9::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E10::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E11::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E12::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }

                return false;
            }
        };

        template<
            class E0 , class E1 , class E2 , class E3 , class E4 , class E5 , class E6 , class E7 , class E8 , class E9 , class E10 , class E11 , class E12 , class E13
        >
        struct begin_msg_map14
        {
            template< class Derived >
            static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
            {
                if (E0::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E1::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E2::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E3::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E4::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E5::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E6::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E7::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E8::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E9::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E10::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E11::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E12::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E13::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }

                return false;
            }
        };

        template<
            class E0 , class E1 , class E2 , class E3 , class E4 , class E5 , class E6 , class E7 , class E8 , class E9 , class E10 , class E11 , class E12 , class E13 , class E14
        >
        struct begin_msg_map15
        {
            template< class Derived >
            static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
            {
                if (E0::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E1::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E2::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E3::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E4::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E5::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E6::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E7::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E8::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E9::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E10::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E11::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E12::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E13::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E14::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }

                return false;
            }
        };

        template<
            class E0 , class E1 , class E2 , class E3 , class E4 , class E5 , class E6 , class E7 , class E8 , class E9 , class E10 , class E11 , class E12 , class E13 , class E14 , class E15
        >
        struct begin_msg_map16
        {
            template< class Derived >
            static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
            {
                if (E0::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E1::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E2::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E3::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E4::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E5::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E6::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E7::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E8::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E9::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E10::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E11::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E12::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E13::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E14::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E15::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }

                return false;
            }
        };

        template<
            class E0 , class E1 , class E2 , class E3 , class E4 , class E5 , class E6 , class E7 , class E8 , class E9 , class E10 , class E11 , class E12 , class E13 , class E14 , class E15 , class E16
        >
        struct begin_msg_map17
        {
            template< class Derived >
            static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
            {
                if (E0::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E1::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E2::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E3::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E4::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E5::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E6::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E7::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E8::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E9::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E10::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E11::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E12::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E13::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E14::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E15::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E16::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }

                return false;
            }
        };

        template<
            class E0 , class E1 , class E2 , class E3 , class E4 , class E5 , class E6 , class E7 , class E8 , class E9 , class E10 , class E11 , class E12 , class E13 , class E14 , class E15 , class E16 , class E17
        >
        struct begin_msg_map18
        {
            template< class Derived >
            static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
            {
                if (E0::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E1::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E2::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E3::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E4::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E5::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E6::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E7::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E8::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E9::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E10::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E11::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E12::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E13::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E14::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E15::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E16::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E17::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }

                return false;
            }
        };

        template<
            class E0 , class E1 , class E2 , class E3 , class E4 , class E5 , class E6 , class E7 , class E8 , class E9 , class E10 , class E11 , class E12 , class E13 , class E14 , class E15 , class E16 , class E17 , class E18
        >
        struct begin_msg_map19
        {
            template< class Derived >
            static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
            {
                if (E0::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E1::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E2::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E3::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E4::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E5::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E6::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E7::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E8::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E9::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E10::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E11::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E12::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E13::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E14::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E15::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E16::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E17::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E18::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }

                return false;
            }
        };

        template<
            class E0 , class E1 , class E2 , class E3 , class E4 , class E5 , class E6 , class E7 , class E8 , class E9 , class E10 , class E11 , class E12 , class E13 , class E14 , class E15 , class E16 , class E17 , class E18 , class E19
        >
        struct begin_msg_map20
        {
            template< class Derived >
            static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
            {
                if (E0::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E1::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E2::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E3::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E4::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E5::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E6::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E7::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E8::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E9::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E10::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E11::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E12::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E13::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E14::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E15::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E16::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E17::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E18::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E19::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }

                return false;
            }
        };

        template<
            class E0 , class E1 , class E2 , class E3 , class E4 , class E5 , class E6 , class E7 , class E8 , class E9 , class E10 , class E11 , class E12 , class E13 , class E14 , class E15 , class E16 , class E17 , class E18 , class E19 , class E20
        >
        struct begin_msg_map21
        {
            template< class Derived >
            static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
            {
                if (E0::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E1::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E2::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E3::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E4::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E5::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E6::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E7::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E8::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E9::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E10::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E11::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E12::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E13::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E14::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E15::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E16::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E17::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E18::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E19::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E20::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }

                return false;
            }
        };

        template<
            class E0 , class E1 , class E2 , class E3 , class E4 , class E5 , class E6 , class E7 , class E8 , class E9 , class E10 , class E11 , class E12 , class E13 , class E14 , class E15 , class E16 , class E17 , class E18 , class E19 , class E20 , class E21
        >
        struct begin_msg_map22
        {
            template< class Derived >
            static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
            {
                if (E0::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E1::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E2::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E3::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E4::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E5::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E6::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E7::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E8::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E9::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E10::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E11::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E12::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E13::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E14::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E15::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E16::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E17::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E18::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E19::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E20::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E21::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }

                return false;
            }
        };

        template<
            class E0 , class E1 , class E2 , class E3 , class E4 , class E5 , class E6 , class E7 , class E8 , class E9 , class E10 , class E11 , class E12 , class E13 , class E14 , class E15 , class E16 , class E17 , class E18 , class E19 , class E20 , class E21 , class E22
        >
        struct begin_msg_map23
        {
            template< class Derived >
            static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
            {
                if (E0::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E1::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E2::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E3::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E4::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E5::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E6::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E7::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E8::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E9::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E10::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E11::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E12::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E13::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E14::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E15::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E16::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E17::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E18::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E19::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E20::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E21::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E22::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }

                return false;
            }
        };

        template<
            class E0 , class E1 , class E2 , class E3 , class E4 , class E5 , class E6 , class E7 , class E8 , class E9 , class E10 , class E11 , class E12 , class E13 , class E14 , class E15 , class E16 , class E17 , class E18 , class E19 , class E20 , class E21 , class E22 , class E23
        >
        struct begin_msg_map24
        {
            template< class Derived >
            static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
            {
                if (E0::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E1::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E2::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E3::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E4::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E5::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E6::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E7::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E8::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E9::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E10::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E11::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E12::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E13::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E14::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E15::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E16::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E17::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E18::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E19::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E20::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E21::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E22::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E23::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }

                return false;
            }
        };

        template<
            class E0 , class E1 , class E2 , class E3 , class E4 , class E5 , class E6 , class E7 , class E8 , class E9 , class E10 , class E11 , class E12 , class E13 , class E14 , class E15 , class E16 , class E17 , class E18 , class E19 , class E20 , class E21 , class E22 , class E23 , class E24
        >
        struct begin_msg_map25
        {
            template< class Derived >
            static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
            {
                if (E0::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E1::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E2::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E3::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E4::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E5::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E6::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E7::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E8::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E9::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E10::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E11::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E12::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E13::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E14::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E15::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E16::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E17::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E18::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E19::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E20::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E21::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E22::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E23::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E24::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }

                return false;
            }
        };

        template<
            class E0 , class E1 , class E2 , class E3 , class E4 , class E5 , class E6 , class E7 , class E8 , class E9 , class E10 , class E11 , class E12 , class E13 , class E14 , class E15 , class E16 , class E17 , class E18 , class E19 , class E20 , class E21 , class E22 , class E23 , class E24 , class E25
        >
        struct begin_msg_map26
        {
            template< class Derived >
            static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
            {
                if (E0::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E1::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E2::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E3::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E4::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E5::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E6::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E7::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E8::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E9::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E10::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E11::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E12::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E13::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E14::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E15::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E16::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E17::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E18::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E19::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E20::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E21::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E22::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E23::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E24::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E25::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }

                return false;
            }
        };

        template<
            class E0 , class E1 , class E2 , class E3 , class E4 , class E5 , class E6 , class E7 , class E8 , class E9 , class E10 , class E11 , class E12 , class E13 , class E14 , class E15 , class E16 , class E17 , class E18 , class E19 , class E20 , class E21 , class E22 , class E23 , class E24 , class E25 , class E26
        >
        struct begin_msg_map27
        {
            template< class Derived >
            static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
            {
                if (E0::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E1::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E2::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E3::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E4::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E5::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E6::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E7::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E8::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E9::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E10::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E11::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E12::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E13::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E14::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E15::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E16::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E17::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E18::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E19::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E20::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E21::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E22::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E23::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E24::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E25::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E26::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }

                return false;
            }
        };

        template<
            class E0 , class E1 , class E2 , class E3 , class E4 , class E5 , class E6 , class E7 , class E8 , class E9 , class E10 , class E11 , class E12 , class E13 , class E14 , class E15 , class E16 , class E17 , class E18 , class E19 , class E20 , class E21 , class E22 , class E23 , class E24 , class E25 , class E26 , class E27
        >
        struct begin_msg_map28
        {
            template< class Derived >
            static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
            {
                if (E0::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E1::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E2::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E3::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E4::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E5::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E6::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E7::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E8::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E9::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E10::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E11::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E12::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E13::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E14::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E15::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E16::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E17::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E18::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E19::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E20::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E21::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E22::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E23::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E24::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E25::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E26::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E27::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }

                return false;
            }
        };

        template<
            class E0 , class E1 , class E2 , class E3 , class E4 , class E5 , class E6 , class E7 , class E8 , class E9 , class E10 , class E11 , class E12 , class E13 , class E14 , class E15 , class E16 , class E17 , class E18 , class E19 , class E20 , class E21 , class E22 , class E23 , class E24 , class E25 , class E26 , class E27 , class E28
        >
        struct begin_msg_map29
        {
            template< class Derived >
            static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
            {
                if (E0::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E1::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E2::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E3::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E4::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E5::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E6::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E7::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E8::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E9::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E10::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E11::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E12::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E13::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E14::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E15::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E16::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E17::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E18::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E19::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E20::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E21::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E22::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E23::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E24::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E25::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E26::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E27::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E28::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }

                return false;
            }
        };

        template<
            class E0 , class E1 , class E2 , class E3 , class E4 , class E5 , class E6 , class E7 , class E8 , class E9 , class E10 , class E11 , class E12 , class E13 , class E14 , class E15 , class E16 , class E17 , class E18 , class E19 , class E20 , class E21 , class E22 , class E23 , class E24 , class E25 , class E26 , class E27 , class E28 , class E29
        >
        struct begin_msg_map30
        {
            template< class Derived >
            static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
            {
                if (E0::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E1::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E2::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E3::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E4::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E5::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E6::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E7::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E8::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E9::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E10::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E11::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E12::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E13::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E14::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E15::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E16::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E17::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E18::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E19::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E20::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E21::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E22::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E23::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E24::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E25::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E26::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E27::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E28::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }
                if (E29::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) { return true; }

                return false;
            }
        };

    }; 
} } 
