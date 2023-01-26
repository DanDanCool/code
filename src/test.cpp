#include <stdio.h>
#include <stdatomic.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define EXPAND(...) EXPAND1(EXPAND1(EXPAND1(EXPAND1(__VA_ARGS__))))
#define EXPAND1(...) EXPAND2(EXPAND2(EXPAND2(EXPAND2(__VA_ARGS__))))
#define EXPAND2(...) EXPAND3(EXPAND3(EXPAND3(EXPAND3(__VA_ARGS__))))
#define EXPAND3(...) EXPAND4(EXPAND4(EXPAND4(EXPAND4(__VA_ARGS__))))
#define EXPAND4(...) __VA_ARGS__

#define SIZE(type) helloworld
#define CALL(fn, ...) fn(__VA_ARGS__)
#define XSTR(x) CALL(STR, EXPAND(x))
#define STR(x) #x

int main()
{
	uint32_t a = 10;
    uint32_t b = 11;
    uint32_t c = 1 + ~(a - b);
    typeof(c) d = 3;
    typeof(d)* e = &d;
	char* f = XSTR(SIZE(d));
    printf("%s", f);
}
