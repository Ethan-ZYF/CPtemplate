
// 究极快读
namespace fastread {
const unsigned int S = 1 << 16;
char B[S + 3], *H, *T;

inline unsigned int gc() {
    if (H == T) T = (H = B) + fread(B, 1, S, stdin);
    return (H == T) ? EOF : *H++;
}

inline unsigned int read() {
    unsigned int x, ch;
    while ((ch = gc()) < 48)
        ;
    x = ch ^ '0';
    while ((ch = gc()) > 47)
        x = x * 10 + (ch ^ '0');
    return x;
}
}  // namespace fastread

using fastread::read;

// 究极快写
namespace fastwrite {
const unsigned int S = 1 << 16;
unsigned int cnt;
char B[S + 3];

inline void write(unsigned int x) {
    if (x > 9) write(x / 10);
    B[cnt++] = (x % 10) | 48;
    if (cnt == S) {
        fwrite(B, 1, S, stdout);
        cnt = 0;
    }
}

inline void space() {
    B[cnt++] = 32;
    if (cnt == S) {
        fwrite(B, 1, S, stdout);
        cnt = 0;
    }
}

inline void nl() {
    B[cnt++] = 10;
    if (cnt == S) {
        fwrite(B, 1, S, stdout);
        cnt = 0;
    }
}

inline void show() {
    fwrite(B, 1, cnt, stdout);
    cnt = 0;
}
}  // namespace fastwrite

using fastwrite::write, fastwrite::space, fastwrite::show, fastwrite::nl;