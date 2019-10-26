/* Utility to generate table for mapping between koi8-r and utf-8.
 *
 */


/* UTF-8 encoding description.
 *
 *        Bits
 * Number for    First    Last
 * of     code   code     code
 * bytes  point  point    point     Byte 1    Byte 2    Byte 3    Byte 4
 * -----------------------------------------------------------------------
 * 1      7      U+0000   U+007F    0xxxxxxx
 * 2      11     U+0080   U+07FF    110xxxxx  10xxxxxx
 * 3      16     U+0800   U+FFFF    1110xxxx  10xxxxxx  10xxxxxx
 * 4      21     U+10000  U+10FFFF  11110xxx  10xxxxxx  10xxxxxx  10xxxxxx
 */


#include <stdio.h>


typedef unsigned int uint;
typedef unsigned char uchar;


// unicode code points for koi8-r
static uint unicode[] = {
    0x2500, 0x2502, 0x250C, 0x2510, 0x2514, 0x2518, 0x251C, 0x2524,
    0x252C, 0x2534, 0x253C, 0x2580, 0x2584, 0x2588, 0x258C, 0x2590,
    0x2591, 0x2592, 0x2593, 0x2320, 0x25A0, 0x2219, 0x221A, 0x2248,
    0x2264, 0x2265, 0x00A0, 0x2321, 0x00B0, 0x00B2, 0x00B7, 0x00F7,
    0x2550, 0x2551, 0x2552, 0x0451, 0x2553, 0x2554, 0x2555, 0x2556,
    0x2557, 0x2558, 0x2559, 0x255A, 0x255B, 0x255C, 0x255D, 0x255E,
    0x255F, 0x2560, 0x2561, 0x0401, 0x2562, 0x2563, 0x2564, 0x2565,
    0x2566, 0x2567, 0x2568, 0x2569, 0x256A, 0x256B, 0x256C, 0x00A9,
    0x044E, 0x0430, 0x0431, 0x0446, 0x0434, 0x0435, 0x0444, 0x0433,
    0x0445, 0x0438, 0x0439, 0x043A, 0x043B, 0x043C, 0x043D, 0x043E,
    0x043F, 0x044F, 0x0440, 0x0441, 0x0442, 0x0443, 0x0436, 0x0432,
    0x044C, 0x044B, 0x0437, 0x0448, 0x044D, 0x0449, 0x0447, 0x044A,
    0x042E, 0x0410, 0x0411, 0x0426, 0x0414, 0x0415, 0x0424, 0x0413,
    0x0425, 0x0418, 0x0419, 0x041A, 0x041B, 0x041C, 0x041D, 0x041E,
    0x041F, 0x042F, 0x0420, 0x0421, 0x0422, 0x0423, 0x0416, 0x0412,
    0x042C, 0x042B, 0x0417, 0x0428, 0x042D, 0x0429, 0x0427, 0x042A
};


// utf-8 encoding for koi8-r
static uchar utf8[128][3];


int main(int argc, char **argv) {
    (void)argc;
    (void)argv;

    for (int i=0; i < 128; i++) {
        uint c = unicode[i];
        if (c < 0x0800) {
            utf8[i][0] = ((c >> 6) & 0x1F) | 0xC0;
            utf8[i][1] = (c & 0x3F) | 0x80;
            utf8[i][2] = 0;
        } else {
            utf8[i][0] = ((c >> 12) & 0x0F) | 0xE0;
            utf8[i][1] = ((c >> 6) & 0x3F) | 0x80;
            utf8[i][2] = (c & 0x3F) | 0x80;
        }
    }

    for (int i1=0; i1 < 16; i1++) {
        for (int i2=0; i2 < 8; i2++) {
            uchar *u = utf8[i1*8+i2];
            printf("    {%d, %d, %d},\r\n", u[0], u[1], u[2]);
        }
        printf("\r\n");
    }
}