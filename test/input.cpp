#include <RDebug.h>

using namespace Redopera;

class Test
{
public:
    std::string toStr() const
    {
        return std::string("Test class" + std::to_string(x) + ", " + std::to_string(y));
    }
    int x = 9, y = 8;
};

int main()
{
    prError("\nTest RDebug error output");
    prError("Test prErrot()");
    check(true, "Test check(true)");
    check(false, "Test check(false)");

    rDebug << "\nTest RDebug output";
    rDebug << -123456 << -123456789l << -1234567890ll;
    rDebug << 123456u << 123456789lu << 1234567890llu;
    rDebug << 123456.789 << 123456.789f;
    bool b = false;
    rDebug << b << !b << &b;
    Test t;
    rDebug << t;

    rDebug << "\nTest RDebug str output";
    unsigned uc = 'u';
    const char chars[] = "chars";
    rDebug << std::string("std::string ") << 'c' << uc << chars;
    const char chars2[] = u8"中文";
    rDebug << std::string("中文 ") << chars2;

    rDebug << L"\n测试 RDebug wstr 输出";
    const wchar_t *wchars = L" 字符";
    rDebug << std::wstring(L"标准库::wstring ") << L'中' << wchars;

    rDebug << "Test color input";
    rDebug << EscCtl::bold << EscCtl::yellow << "Yellow" << EscCtl::non;

    return 0;
}
