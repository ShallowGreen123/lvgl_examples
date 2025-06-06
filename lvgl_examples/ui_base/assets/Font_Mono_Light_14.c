/*******************************************************************************
 * Size: 14 px
 * Bpp: 4
 * Opts: --no-compress --format lvgl --font .\JetBrainsMono-ExtraLight.ttf -o D:\dgx\code\T_Embed_PN532\examples\factory\assets\Font_Mono_Light_14.c --bpp 4 --size 14 -r 0x20-0x7f
 ******************************************************************************/

#include "lvgl/lvgl.h"

#ifndef FONT_MONO_LIGHT_14
#define FONT_MONO_LIGHT_14 1
#endif

#if FONT_MONO_LIGHT_14

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */

    /* U+0021 "!" */
    0x5b, 0x5, 0xb0, 0x4b, 0x4, 0xa0, 0x4a, 0x3,
    0xa0, 0x3a, 0x1, 0x40, 0x48, 0x7, 0xe0,

    /* U+0022 "\"" */
    0xc5, 0xe, 0x2c, 0x40, 0xe2, 0xb4, 0xe, 0x2b,
    0x40, 0xd1, 0x31, 0x3, 0x0,

    /* U+0023 "#" */
    0x0, 0xc, 0x0, 0xb1, 0x0, 0x1a, 0x0, 0xc0,
    0x0, 0x47, 0x1, 0xb0, 0xb, 0xdc, 0xbc, 0xd9,
    0x0, 0xb1, 0x7, 0x40, 0x0, 0xc0, 0xa, 0x10,
    0x5c, 0xeb, 0xbe, 0xb4, 0x4, 0x70, 0x1b, 0x0,
    0x7, 0x40, 0x48, 0x0, 0xa, 0x10, 0x75, 0x0,

    /* U+0024 "$" */
    0x0, 0x4, 0x0, 0x0, 0x1, 0x90, 0x0, 0x2,
    0x9d, 0x70, 0x2, 0xd5, 0xa8, 0xa0, 0x86, 0x19,
    0xd, 0x18, 0x71, 0x90, 0x0, 0x2e, 0x69, 0x0,
    0x0, 0x2a, 0xf9, 0x0, 0x0, 0x1a, 0x7b, 0x0,
    0x1, 0x90, 0xc2, 0xc2, 0x19, 0xb, 0x38, 0xa1,
    0x93, 0xe0, 0x9, 0xef, 0xd3, 0x0, 0x1, 0x90,
    0x0, 0x0, 0x19, 0x0, 0x0,

    /* U+0025 "%" */
    0x4d, 0xc7, 0x0, 0x1a, 0xb, 0x10, 0xc0, 0xa,
    0x10, 0xa2, 0xd, 0x7, 0x50, 0x3, 0xbc, 0x52,
    0x90, 0x0, 0x0, 0x0, 0xb0, 0x0, 0x0, 0x0,
    0x85, 0xac, 0x60, 0x0, 0x38, 0x76, 0xc, 0x0,
    0xb, 0x8, 0x30, 0xa1, 0x9, 0x20, 0x74, 0xb,
    0x5, 0x70, 0x1, 0xbb, 0x80,

    /* U+0026 "&" */
    0x0, 0x8d, 0xd7, 0x0, 0x0, 0x2d, 0x0, 0xb3,
    0x0, 0x2, 0xc0, 0x3, 0x20, 0x0, 0x8, 0x60,
    0x0, 0x0, 0x6, 0xce, 0x40, 0x3, 0x23, 0xb0,
    0x1c, 0x23, 0xc0, 0x76, 0x0, 0x2d, 0xc2, 0x7,
    0x60, 0x0, 0xcc, 0x0, 0x4b, 0x0, 0xa6, 0x87,
    0x0, 0x8d, 0xd6, 0x0, 0xc3,

    /* U+0027 "'" */
    0x5c, 0x5b, 0x4b, 0x4b, 0x13,

    /* U+0028 "(" */
    0x0, 0x7, 0xa0, 0xb, 0x81, 0x8, 0x90, 0x0,
    0xe1, 0x0, 0x2d, 0x0, 0x3, 0xb0, 0x0, 0x3b,
    0x0, 0x3, 0xb0, 0x0, 0x2c, 0x0, 0x1, 0xe0,
    0x0, 0xd, 0x30, 0x0, 0x5c, 0x0, 0x0, 0x7c,
    0x40, 0x0, 0x27,

    /* U+0029 ")" */
    0x59, 0x20, 0x0, 0x4d, 0x30, 0x0, 0x3d, 0x0,
    0x0, 0xb4, 0x0, 0x7, 0x80, 0x0, 0x59, 0x0,
    0x5, 0x90, 0x0, 0x59, 0x0, 0x5, 0x90, 0x0,
    0x77, 0x0, 0xc, 0x30, 0x6, 0xb0, 0x19, 0xc1,
    0x3, 0x50, 0x0,

    /* U+002A "*" */
    0x0, 0x3, 0xa0, 0x0, 0x0, 0x3, 0xa0, 0x0,
    0x39, 0x33, 0x91, 0x78, 0x5, 0xbd, 0xdc, 0x71,
    0x0, 0xb, 0xb3, 0x0, 0x0, 0x88, 0x2d, 0x0,
    0x2, 0xd0, 0x7, 0x80, 0x0, 0x10, 0x0, 0x0,

    /* U+002B "+" */
    0x0, 0x4a, 0x0, 0x0, 0x4, 0xa0, 0x0, 0x0,
    0x4a, 0x0, 0xd, 0xde, 0xfd, 0xd5, 0x0, 0x4a,
    0x0, 0x0, 0x4, 0xa0, 0x0, 0x0, 0x26, 0x0,
    0x0,

    /* U+002C "," */
    0x15, 0x5, 0xd0, 0x89, 0xb, 0x50, 0xe2, 0x0,

    /* U+002D "-" */
    0xd, 0xdd, 0xd5,

    /* U+002E "." */
    0x1, 0xc, 0xf2, 0xae, 0x10,

    /* U+002F "/" */
    0x0, 0x0, 0x7, 0x0, 0x0, 0x2, 0xd0, 0x0,
    0x0, 0x87, 0x0, 0x0, 0xe, 0x10, 0x0, 0x4,
    0xb0, 0x0, 0x0, 0xa5, 0x0, 0x0, 0xe, 0x0,
    0x0, 0x6, 0x90, 0x0, 0x0, 0xc3, 0x0, 0x0,
    0x2d, 0x0, 0x0, 0x7, 0x70, 0x0, 0x0, 0xd2,
    0x0, 0x0, 0x3c, 0x0, 0x0, 0x9, 0x60, 0x0,
    0x0,

    /* U+0030 "0" */
    0x7, 0xdd, 0xb2, 0x6, 0xa0, 0x4, 0xc0, 0xb3,
    0x0, 0xd, 0x1c, 0x20, 0x0, 0xc2, 0xc2, 0x7d,
    0xc, 0x2c, 0x21, 0x20, 0xc2, 0xc2, 0x0, 0xc,
    0x2b, 0x30, 0x0, 0xd1, 0x6a, 0x0, 0x4c, 0x0,
    0x8d, 0xdb, 0x20,

    /* U+0031 "1" */
    0x1, 0xbf, 0x10, 0x4, 0xd4, 0xd1, 0x0, 0x51,
    0xd, 0x10, 0x0, 0x0, 0xd1, 0x0, 0x0, 0xd,
    0x10, 0x0, 0x0, 0xd1, 0x0, 0x0, 0xd, 0x10,
    0x0, 0x0, 0xd1, 0x0, 0x0, 0xd, 0x10, 0x9,
    0xdd, 0xfd, 0xd6,

    /* U+0032 "2" */
    0x8, 0xdd, 0xb2, 0x8, 0x90, 0x5, 0xd0, 0xa1,
    0x0, 0xc, 0x20, 0x0, 0x0, 0xd1, 0x0, 0x0,
    0x5a, 0x0, 0x0, 0x2c, 0x10, 0x0, 0x2c, 0x20,
    0x0, 0x2c, 0x20, 0x0, 0x2c, 0x20, 0x0, 0xb,
    0xed, 0xdd, 0xd4,

    /* U+0033 "3" */
    0x7d, 0xdd, 0xec, 0x0, 0x0, 0x2b, 0x30, 0x0,
    0x4b, 0x10, 0x0, 0xc, 0xd8, 0x0, 0x0, 0x0,
    0x89, 0x0, 0x0, 0x0, 0xe0, 0x0, 0x0, 0xe,
    0xc, 0x10, 0x0, 0xe0, 0x79, 0x0, 0x89, 0x0,
    0x8d, 0xd9, 0x0,

    /* U+0034 "4" */
    0x0, 0x5, 0xb0, 0x0, 0xd, 0x20, 0x0, 0x97,
    0x0, 0x3, 0xd0, 0x0, 0xc, 0x30, 0x3b, 0x79,
    0x0, 0x3b, 0xe1, 0x0, 0x3b, 0xdd, 0xdd, 0xeb,
    0x0, 0x0, 0x3b, 0x0, 0x0, 0x3b,

    /* U+0035 "5" */
    0x7e, 0xdd, 0xda, 0x7, 0x60, 0x0, 0x0, 0x76,
    0x0, 0x0, 0x6, 0xed, 0xd9, 0x10, 0x0, 0x0,
    0x8a, 0x0, 0x0, 0x0, 0xe0, 0x10, 0x0, 0xd,
    0x1b, 0x20, 0x0, 0xe0, 0x6a, 0x0, 0x7a, 0x0,
    0x8d, 0xda, 0x10,

    /* U+0036 "6" */
    0x0, 0xc, 0x20, 0x0, 0x7, 0x50, 0x0, 0x1,
    0x90, 0x0, 0x0, 0x9a, 0xca, 0x10, 0x3b, 0x0,
    0x6d, 0xa, 0x20, 0x0, 0xb4, 0xe0, 0x0, 0x9,
    0x5e, 0x10, 0x0, 0xb3, 0x8a, 0x0, 0x5d, 0x0,
    0x8e, 0xdb, 0x10,

    /* U+0037 "7" */
    0xce, 0xdd, 0xde, 0x8c, 0x20, 0x0, 0xb4, 0x91,
    0x0, 0x1d, 0x0, 0x0, 0x8, 0x70, 0x0, 0x0,
    0xe1, 0x0, 0x0, 0x5a, 0x0, 0x0, 0xc, 0x30,
    0x0, 0x2, 0xd0, 0x0, 0x0, 0x96, 0x0, 0x0,
    0xe, 0x0, 0x0,

    /* U+0038 "8" */
    0x8, 0xdd, 0xb2, 0x7, 0xa0, 0x4, 0xd0, 0x95,
    0x0, 0xe, 0x4, 0xb0, 0x5, 0xb0, 0x7, 0xfe,
    0xc1, 0x6, 0xa1, 0x5, 0xc0, 0xd1, 0x0, 0xb,
    0x4e, 0x10, 0x0, 0xa4, 0x89, 0x0, 0x4e, 0x0,
    0x9d, 0xdc, 0x20,

    /* U+0039 "9" */
    0x8, 0xdd, 0xb2, 0x9, 0x90, 0x4, 0xd0, 0xe0,
    0x0, 0xa, 0x4e, 0x0, 0x0, 0xa4, 0x99, 0x0,
    0x4f, 0x10, 0x8d, 0xbc, 0xa0, 0x0, 0x1, 0xe1,
    0x0, 0x0, 0xa7, 0x0, 0x0, 0x3d, 0x0, 0x0,
    0xd, 0x40, 0x0,

    /* U+003A ":" */
    0xae, 0x1b, 0xf2, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0xbf, 0x2a, 0xe1,

    /* U+003B ";" */
    0xb, 0xe2, 0xb, 0xf2, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x1, 0x50, 0x6, 0xc0,
    0x9, 0x80, 0xc, 0x40, 0xf, 0x10,

    /* U+003C "<" */
    0x0, 0x0, 0x1, 0x0, 0x0, 0x7, 0xd1, 0x0,
    0x6d, 0x70, 0x4, 0xc8, 0x0, 0x0, 0xb8, 0x0,
    0x0, 0x0, 0x7d, 0x60, 0x0, 0x0, 0x8, 0xd6,
    0x0, 0x0, 0x1, 0x92,

    /* U+003D "=" */
    0x9d, 0xdd, 0xdd, 0x10, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x9, 0xdd, 0xdd, 0xd1,

    /* U+003E ">" */
    0x20, 0x0, 0x0, 0x9, 0xb2, 0x0, 0x0, 0x4,
    0xca, 0x10, 0x0, 0x0, 0x5d, 0x80, 0x0, 0x0,
    0x4e, 0x20, 0x3, 0xba, 0x20, 0x2a, 0xb3, 0x0,
    0x8, 0x40, 0x0, 0x0,

    /* U+003F "?" */
    0xe, 0xee, 0x91, 0x0, 0x0, 0x8a, 0x0, 0x0,
    0x1d, 0x0, 0x0, 0x89, 0x0, 0xbc, 0x90, 0x0,
    0xd1, 0x0, 0x0, 0x91, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x92, 0x0, 0x2, 0xe5, 0x0,

    /* U+0040 "@" */
    0x0, 0x7d, 0xcb, 0x40, 0x7, 0x90, 0x1, 0xb2,
    0xd, 0x0, 0x0, 0x48, 0x1c, 0x0, 0xab, 0x8b,
    0x3a, 0x6, 0x90, 0x6b, 0x3a, 0x8, 0x50, 0x2b,
    0x3a, 0x8, 0x50, 0x2b, 0x3a, 0x8, 0x50, 0x2b,
    0x3a, 0x5, 0x90, 0x78, 0x2c, 0x0, 0x8c, 0xa1,
    0xd, 0x10, 0x0, 0x0, 0x7, 0xb1, 0x0, 0x0,
    0x0, 0x6d, 0xda, 0x0,

    /* U+0041 "A" */
    0x0, 0x8, 0xe0, 0x0, 0x0, 0xc, 0xa3, 0x0,
    0x0, 0x1b, 0x57, 0x0, 0x0, 0x57, 0x1c, 0x0,
    0x0, 0xa2, 0xc, 0x0, 0x0, 0xc0, 0x8, 0x40,
    0x3, 0xed, 0xdd, 0x90, 0x7, 0x60, 0x0, 0xd0,
    0xb, 0x20, 0x0, 0xc2, 0xe, 0x0, 0x0, 0x86,

    /* U+0042 "B" */
    0x9e, 0xdd, 0xb2, 0x9, 0x50, 0x4, 0xd0, 0x95,
    0x0, 0xe, 0x9, 0x50, 0x5, 0xa0, 0x9e, 0xde,
    0xc1, 0x9, 0x50, 0x4, 0xb0, 0x95, 0x0, 0xb,
    0x39, 0x50, 0x0, 0xa3, 0x95, 0x0, 0x3d, 0x9,
    0xed, 0xdc, 0x20,

    /* U+0043 "C" */
    0x6, 0xdd, 0xc2, 0x4, 0xc1, 0x3, 0xd0, 0x86,
    0x0, 0x9, 0x29, 0x50, 0x0, 0x0, 0x95, 0x0,
    0x0, 0x9, 0x50, 0x0, 0x0, 0x95, 0x0, 0x0,
    0x8, 0x60, 0x0, 0x92, 0x4c, 0x0, 0x3d, 0x0,
    0x6d, 0xdc, 0x20,

    /* U+0044 "D" */
    0x9e, 0xde, 0x90, 0x9, 0x50, 0x8, 0x90, 0x95,
    0x0, 0xe, 0x9, 0x50, 0x0, 0xe0, 0x95, 0x0,
    0xe, 0x9, 0x50, 0x0, 0xe0, 0x95, 0x0, 0xe,
    0x9, 0x50, 0x0, 0xe0, 0x95, 0x0, 0x89, 0x9,
    0xed, 0xe9, 0x0,

    /* U+0045 "E" */
    0x7e, 0xdd, 0xdd, 0x27, 0x70, 0x0, 0x0, 0x77,
    0x0, 0x0, 0x7, 0x70, 0x0, 0x0, 0x7e, 0xdd,
    0xd9, 0x7, 0x70, 0x0, 0x0, 0x77, 0x0, 0x0,
    0x7, 0x70, 0x0, 0x0, 0x77, 0x0, 0x0, 0x7,
    0xed, 0xdd, 0xd2,

    /* U+0046 "F" */
    0x8e, 0xdd, 0xdd, 0x48, 0x60, 0x0, 0x0, 0x86,
    0x0, 0x0, 0x8, 0x60, 0x0, 0x0, 0x8e, 0xee,
    0xec, 0x8, 0x60, 0x0, 0x0, 0x86, 0x0, 0x0,
    0x8, 0x60, 0x0, 0x0, 0x86, 0x0, 0x0, 0x8,
    0x60, 0x0, 0x0,

    /* U+0047 "G" */
    0x7, 0xdd, 0xc3, 0x5, 0xb0, 0x3, 0xe0, 0x95,
    0x0, 0x5, 0xa, 0x40, 0x0, 0x0, 0xa4, 0xd,
    0xde, 0x2a, 0x40, 0x0, 0xb3, 0xa4, 0x0, 0xb,
    0x29, 0x50, 0x0, 0xd1, 0x5b, 0x0, 0x5b, 0x0,
    0x7d, 0xdb, 0x10,

    /* U+0048 "H" */
    0x95, 0x0, 0xe, 0x95, 0x0, 0xe, 0x95, 0x0,
    0xe, 0x95, 0x0, 0xe, 0x9e, 0xdd, 0xdf, 0x95,
    0x0, 0xe, 0x95, 0x0, 0xe, 0x95, 0x0, 0xe,
    0x95, 0x0, 0xe, 0x95, 0x0, 0xe,

    /* U+0049 "I" */
    0x5d, 0xef, 0xda, 0x0, 0x4a, 0x0, 0x0, 0x4a,
    0x0, 0x0, 0x4a, 0x0, 0x0, 0x4a, 0x0, 0x0,
    0x4a, 0x0, 0x0, 0x4a, 0x0, 0x0, 0x4a, 0x0,
    0x0, 0x4a, 0x0, 0x5d, 0xef, 0xda,

    /* U+004A "J" */
    0x0, 0x0, 0x2, 0xc0, 0x0, 0x0, 0x2c, 0x0,
    0x0, 0x2, 0xc0, 0x0, 0x0, 0x2c, 0x0, 0x0,
    0x2, 0xc0, 0x0, 0x0, 0x2c, 0x0, 0x0, 0x2,
    0xc1, 0xc0, 0x0, 0x3b, 0xc, 0x50, 0xa, 0x70,
    0x2b, 0xdd, 0x80,

    /* U+004B "K" */
    0x95, 0x0, 0xb, 0x49, 0x50, 0x4, 0xb0, 0x95,
    0x0, 0xd2, 0x9, 0x50, 0x69, 0x0, 0x9e, 0xdf,
    0x30, 0x9, 0x50, 0x78, 0x0, 0x95, 0x1, 0xe1,
    0x9, 0x50, 0x9, 0x70, 0x95, 0x0, 0x1e, 0x9,
    0x50, 0x0, 0xa6,

    /* U+004C "L" */
    0x1d, 0x0, 0x0, 0x1, 0xd0, 0x0, 0x0, 0x1d,
    0x0, 0x0, 0x1, 0xd0, 0x0, 0x0, 0x1d, 0x0,
    0x0, 0x1, 0xd0, 0x0, 0x0, 0x1d, 0x0, 0x0,
    0x1, 0xd0, 0x0, 0x0, 0x1d, 0x0, 0x0, 0x1,
    0xfd, 0xdd, 0xd9,

    /* U+004D "M" */
    0xca, 0x0, 0x4e, 0x3d, 0xa1, 0xa, 0xa3, 0xd6,
    0x60, 0xaa, 0x3d, 0x1b, 0x55, 0xa3, 0xd1, 0xac,
    0xa, 0x3d, 0x13, 0x60, 0xa3, 0xd1, 0x0, 0xa,
    0x3d, 0x10, 0x0, 0xa3, 0xd1, 0x0, 0xa, 0x3d,
    0x10, 0x0, 0xa3,

    /* U+004E "N" */
    0x9d, 0x0, 0xe, 0x9d, 0x30, 0xe, 0x97, 0x90,
    0xe, 0x95, 0xb0, 0xe, 0x95, 0x65, 0xe, 0x95,
    0xb, 0xe, 0x95, 0xa, 0x1e, 0x95, 0x4, 0x7e,
    0x95, 0x0, 0xbd, 0x95, 0x0, 0x7f,

    /* U+004F "O" */
    0x7, 0xdd, 0xb1, 0x5, 0xb0, 0x5, 0xb0, 0x95,
    0x0, 0xe, 0xa, 0x40, 0x0, 0xe0, 0xa4, 0x0,
    0xe, 0xa, 0x40, 0x0, 0xe0, 0xa4, 0x0, 0xe,
    0x9, 0x50, 0x0, 0xe0, 0x5b, 0x0, 0x5b, 0x0,
    0x7d, 0xdb, 0x10,

    /* U+0050 "P" */
    0x9e, 0xdd, 0xd5, 0x9, 0x50, 0x1, 0xd3, 0x95,
    0x0, 0x7, 0x79, 0x50, 0x0, 0x77, 0x95, 0x0,
    0x2d, 0x29, 0xed, 0xdc, 0x40, 0x95, 0x0, 0x0,
    0x9, 0x50, 0x0, 0x0, 0x95, 0x0, 0x0, 0x9,
    0x50, 0x0, 0x0,

    /* U+0051 "Q" */
    0x7, 0xdd, 0xb2, 0x5, 0xb0, 0x5, 0xc0, 0x94,
    0x0, 0xe, 0xa, 0x40, 0x0, 0xd1, 0xa4, 0x0,
    0xd, 0x1a, 0x40, 0x0, 0xd1, 0xa4, 0x0, 0xd,
    0x1a, 0x40, 0x0, 0xe0, 0x5b, 0x0, 0x5c, 0x0,
    0x7d, 0xed, 0x10, 0x0, 0x1, 0xe0, 0x0, 0x0,
    0x9, 0x70, 0x0, 0x0, 0x2e, 0x0,

    /* U+0052 "R" */
    0x9e, 0xdd, 0xd5, 0x9, 0x50, 0x1, 0xd2, 0x95,
    0x0, 0x9, 0x59, 0x50, 0x2, 0xd2, 0x9e, 0xde,
    0xc4, 0x9, 0x50, 0x88, 0x0, 0x95, 0x1, 0xe0,
    0x9, 0x50, 0xa, 0x60, 0x95, 0x0, 0x3d, 0x9,
    0x50, 0x0, 0xc4,

    /* U+0053 "S" */
    0x8, 0xdd, 0xb2, 0x6, 0xb0, 0x5, 0xc0, 0x95,
    0x0, 0x8, 0x5, 0xa0, 0x0, 0x0, 0x8, 0xc8,
    0x30, 0x0, 0x0, 0x4b, 0x70, 0x0, 0x0, 0xc,
    0x1a, 0x10, 0x0, 0xa3, 0x89, 0x0, 0x3e, 0x0,
    0x8d, 0xdc, 0x30,

    /* U+0054 "T" */
    0x2d, 0xde, 0xfd, 0xd8, 0x0, 0x4, 0xa0, 0x0,
    0x0, 0x4, 0xa0, 0x0, 0x0, 0x4, 0xa0, 0x0,
    0x0, 0x4, 0xa0, 0x0, 0x0, 0x4, 0xa0, 0x0,
    0x0, 0x4, 0xa0, 0x0, 0x0, 0x4, 0xa0, 0x0,
    0x0, 0x4, 0xa0, 0x0, 0x0, 0x4, 0xa0, 0x0,

    /* U+0055 "U" */
    0x95, 0x0, 0xe, 0x95, 0x0, 0xe, 0x95, 0x0,
    0xe, 0x95, 0x0, 0xe, 0x95, 0x0, 0xe, 0x95,
    0x0, 0xe, 0x95, 0x0, 0xe, 0x86, 0x0, 0xe,
    0x4c, 0x0, 0x6b, 0x7, 0xdd, 0xb1,

    /* U+0056 "V" */
    0xe, 0x0, 0x0, 0x86, 0xb, 0x30, 0x0, 0xc2,
    0x7, 0x70, 0x0, 0xd0, 0x3, 0xb0, 0x5, 0x90,
    0x0, 0xe0, 0x9, 0x50, 0x0, 0xa4, 0xd, 0x0,
    0x0, 0x68, 0x1c, 0x0, 0x0, 0x1c, 0x67, 0x0,
    0x0, 0xd, 0xa3, 0x0, 0x0, 0x8, 0xe0, 0x0,

    /* U+0057 "W" */
    0x75, 0x5, 0xd0, 0xd, 0x57, 0x8, 0xc0, 0x1c,
    0x39, 0xa, 0x91, 0x2a, 0x1b, 0xa, 0x64, 0x48,
    0xd, 0xa, 0x46, 0x66, 0xd, 0x19, 0x28, 0x84,
    0xb, 0x56, 0xa, 0xa2, 0x9, 0x94, 0xb, 0xb0,
    0x8, 0xd2, 0xa, 0xb0, 0x6, 0xf0, 0x9, 0xb0,

    /* U+0058 "X" */
    0xd, 0x30, 0x0, 0xb4, 0x4, 0xb0, 0x4, 0xa0,
    0x0, 0xb4, 0xc, 0x10, 0x0, 0x2c, 0x77, 0x0,
    0x0, 0x8, 0xe0, 0x0, 0x0, 0xb, 0xd2, 0x0,
    0x0, 0x4a, 0x3b, 0x0, 0x0, 0xd1, 0xb, 0x40,
    0x7, 0x80, 0x2, 0xd0, 0x1d, 0x0, 0x0, 0x97,

    /* U+0059 "Y" */
    0x2d, 0x0, 0x0, 0x68, 0xa, 0x50, 0x0, 0xd1,
    0x2, 0xd0, 0x6, 0x80, 0x0, 0xa5, 0xd, 0x10,
    0x0, 0x2d, 0x68, 0x0, 0x0, 0x9, 0xe1, 0x0,
    0x0, 0x4, 0xa0, 0x0, 0x0, 0x4, 0xa0, 0x0,
    0x0, 0x4, 0xa0, 0x0, 0x0, 0x4, 0xa0, 0x0,

    /* U+005A "Z" */
    0x9d, 0xdd, 0xdf, 0x0, 0x0, 0x4, 0xb0, 0x0,
    0x0, 0xd2, 0x0, 0x0, 0x78, 0x0, 0x0, 0x1d,
    0x0, 0x0, 0xa, 0x50, 0x0, 0x4, 0xb0, 0x0,
    0x0, 0xc2, 0x0, 0x0, 0x68, 0x0, 0x0, 0xc,
    0xed, 0xdd, 0xd2,

    /* U+005B "[" */
    0xed, 0xd3, 0xe0, 0x0, 0xe0, 0x0, 0xe0, 0x0,
    0xe0, 0x0, 0xe0, 0x0, 0xe0, 0x0, 0xe0, 0x0,
    0xe0, 0x0, 0xe0, 0x0, 0xe0, 0x0, 0xe0, 0x0,
    0xe0, 0x0, 0xed, 0xd3,

    /* U+005C "\\" */
    0x52, 0x0, 0x0, 0x6, 0x90, 0x0, 0x0, 0x1e,
    0x0, 0x0, 0x0, 0xa4, 0x0, 0x0, 0x4, 0xa0,
    0x0, 0x0, 0xe, 0x10, 0x0, 0x0, 0x96, 0x0,
    0x0, 0x3, 0xc0, 0x0, 0x0, 0xd, 0x20, 0x0,
    0x0, 0x78, 0x0, 0x0, 0x1, 0xd0, 0x0, 0x0,
    0xb, 0x40, 0x0, 0x0, 0x5a, 0x0, 0x0, 0x0,
    0xe0,

    /* U+005D "]" */
    0xbd, 0xd5, 0x0, 0x86, 0x0, 0x86, 0x0, 0x86,
    0x0, 0x86, 0x0, 0x86, 0x0, 0x86, 0x0, 0x86,
    0x0, 0x86, 0x0, 0x86, 0x0, 0x86, 0x0, 0x86,
    0x0, 0x86, 0xbd, 0xe5,

    /* U+005E "^" */
    0x0, 0x26, 0x0, 0x0, 0xa, 0xd2, 0x0, 0x2,
    0xc4, 0x90, 0x0, 0x95, 0xd, 0x0, 0x1d, 0x0,
    0x77, 0x7, 0x70, 0x1, 0xd0,

    /* U+005F "_" */
    0x2d, 0xdd, 0xdd, 0xd7,

    /* U+0060 "`" */
    0x3c, 0x0, 0x6, 0xa0,

    /* U+0061 "a" */
    0x8, 0xdd, 0xb2, 0x6a, 0x0, 0x4b, 0x0, 0x0,
    0xe, 0x1a, 0xcc, 0xcf, 0xa6, 0x0, 0xe, 0xe0,
    0x0, 0xf, 0xb6, 0x0, 0x7e, 0x1b, 0xdc, 0x5e,

    /* U+0062 "b" */
    0x95, 0x0, 0x0, 0x9, 0x50, 0x0, 0x0, 0x97,
    0xbd, 0xb1, 0x9, 0xb0, 0x5, 0xb0, 0x96, 0x0,
    0xe, 0x9, 0x50, 0x0, 0xe0, 0x95, 0x0, 0xe,
    0x9, 0x60, 0x0, 0xe0, 0x9b, 0x0, 0x5b, 0x9,
    0x7b, 0xdc, 0x20,

    /* U+0063 "c" */
    0x6, 0xdd, 0xb2, 0x3, 0xc1, 0x4, 0xd0, 0x86,
    0x0, 0x8, 0x19, 0x50, 0x0, 0x0, 0x95, 0x0,
    0x0, 0x8, 0x60, 0x0, 0x81, 0x3c, 0x10, 0x3d,
    0x0, 0x6d, 0xdc, 0x20,

    /* U+0064 "d" */
    0x0, 0x0, 0xe, 0x0, 0x0, 0xe, 0x8, 0xdc,
    0x6e, 0x5b, 0x0, 0x6f, 0x95, 0x0, 0xf, 0xa4,
    0x0, 0xe, 0xa4, 0x0, 0xe, 0x95, 0x0, 0xf,
    0x5b, 0x0, 0x6f, 0x8, 0xdc, 0x6e,

    /* U+0065 "e" */
    0x7, 0xcc, 0xb2, 0x4, 0xa0, 0x4, 0xc0, 0x94,
    0x0, 0xe, 0xa, 0xdc, 0xcc, 0xd0, 0xa4, 0x0,
    0x0, 0x9, 0x50, 0x0, 0x20, 0x4c, 0x0, 0x5b,
    0x0, 0x7d, 0xdb, 0x10,

    /* U+0066 "f" */
    0x0, 0x5, 0xed, 0xd4, 0x0, 0xc, 0x30, 0x0,
    0x0, 0xd, 0x10, 0x0, 0x1d, 0xdf, 0xdd, 0xd4,
    0x0, 0xd, 0x10, 0x0, 0x0, 0xd, 0x10, 0x0,
    0x0, 0xd, 0x10, 0x0, 0x0, 0xd, 0x10, 0x0,
    0x0, 0xd, 0x10, 0x0, 0x0, 0xd, 0x10, 0x0,

    /* U+0067 "g" */
    0x7, 0xdc, 0x5e, 0x4c, 0x0, 0x7e, 0x85, 0x0,
    0xf, 0x94, 0x0, 0xe, 0x94, 0x0, 0xe, 0x86,
    0x0, 0xf, 0x3c, 0x10, 0x7e, 0x6, 0xcc, 0x4e,
    0x0, 0x0, 0xe, 0x0, 0x0, 0x4b, 0x8, 0xdd,
    0xc2,

    /* U+0068 "h" */
    0x95, 0x0, 0x0, 0x95, 0x0, 0x0, 0x97, 0xbd,
    0xb1, 0x9b, 0x0, 0x6b, 0x96, 0x0, 0xe, 0x95,
    0x0, 0xe, 0x95, 0x0, 0xe, 0x95, 0x0, 0xe,
    0x95, 0x0, 0xe, 0x95, 0x0, 0xe,

    /* U+0069 "i" */
    0x0, 0x16, 0x0, 0x0, 0x5, 0xf2, 0x0, 0x0,
    0x1, 0x0, 0x5, 0xdd, 0xf0, 0x0, 0x0, 0xe,
    0x0, 0x0, 0x0, 0xe0, 0x0, 0x0, 0xe, 0x0,
    0x0, 0x0, 0xe0, 0x0, 0x0, 0xe, 0x0, 0x0,
    0x0, 0xe0, 0x0, 0x9d, 0xdf, 0xdd, 0x80,

    /* U+006A "j" */
    0x0, 0x1, 0x60, 0x0, 0x7, 0xf1, 0x0, 0x0,
    0x10, 0x8d, 0xdd, 0xf0, 0x0, 0x0, 0xe0, 0x0,
    0x0, 0xe0, 0x0, 0x0, 0xe0, 0x0, 0x0, 0xe0,
    0x0, 0x0, 0xe0, 0x0, 0x0, 0xe0, 0x0, 0x0,
    0xe0, 0x0, 0x0, 0xe0, 0x0, 0x7, 0x90, 0x7d,
    0xda, 0x10,

    /* U+006B "k" */
    0x77, 0x0, 0x0, 0x7, 0x70, 0x0, 0x0, 0x77,
    0x0, 0x1d, 0x27, 0x70, 0xb, 0x50, 0x77, 0x7,
    0xa0, 0x7, 0xed, 0xf1, 0x0, 0x77, 0x8, 0x80,
    0x7, 0x70, 0xd, 0x20, 0x77, 0x0, 0x5b, 0x7,
    0x70, 0x0, 0xc5,

    /* U+006C "l" */
    0x5d, 0xdf, 0x10, 0x0, 0x0, 0xd, 0x10, 0x0,
    0x0, 0xd, 0x10, 0x0, 0x0, 0xd, 0x10, 0x0,
    0x0, 0xd, 0x10, 0x0, 0x0, 0xd, 0x10, 0x0,
    0x0, 0xd, 0x10, 0x0, 0x0, 0xd, 0x10, 0x0,
    0x0, 0xc, 0x30, 0x0, 0x0, 0x3, 0xdd, 0xd8,

    /* U+006D "m" */
    0xd, 0x9c, 0x69, 0xb0, 0xe, 0x4, 0xa0, 0x85,
    0xd, 0x3, 0x90, 0x77, 0xd, 0x3, 0x90, 0x77,
    0xd, 0x3, 0x90, 0x77, 0xd, 0x3, 0x90, 0x77,
    0xd, 0x3, 0x90, 0x77, 0xd, 0x3, 0x90, 0x77,

    /* U+006E "n" */
    0x98, 0xaa, 0xb1, 0x9b, 0x0, 0x4b, 0x96, 0x0,
    0xe, 0x95, 0x0, 0xe, 0x95, 0x0, 0xe, 0x95,
    0x0, 0xe, 0x95, 0x0, 0xe, 0x95, 0x0, 0xe,

    /* U+006F "o" */
    0x7, 0xdd, 0xa1, 0x4, 0xb0, 0x6, 0xb0, 0x95,
    0x0, 0xe, 0xa, 0x40, 0x0, 0xe0, 0xa4, 0x0,
    0xe, 0x9, 0x50, 0x0, 0xe0, 0x4b, 0x0, 0x5b,
    0x0, 0x7d, 0xda, 0x10,

    /* U+0070 "p" */
    0x98, 0xab, 0xb2, 0x9, 0xb0, 0x3, 0xb0, 0x96,
    0x0, 0xe, 0x9, 0x50, 0x0, 0xe0, 0x95, 0x0,
    0xe, 0x9, 0x60, 0x0, 0xe0, 0x9b, 0x0, 0x5b,
    0x9, 0x7b, 0xdc, 0x20, 0x95, 0x0, 0x0, 0x9,
    0x50, 0x0, 0x0, 0x95, 0x0, 0x0, 0x0,

    /* U+0071 "q" */
    0x8, 0xdc, 0x6e, 0x5b, 0x0, 0x6f, 0x95, 0x0,
    0xf, 0xa4, 0x0, 0xe, 0xa4, 0x0, 0xe, 0x95,
    0x0, 0xf, 0x5b, 0x0, 0x6e, 0x8, 0xdc, 0x6e,
    0x0, 0x0, 0xe, 0x0, 0x0, 0xe, 0x0, 0x0,
    0xe,

    /* U+0072 "r" */
    0x4a, 0x8a, 0xc4, 0x4, 0xe1, 0x1, 0xd0, 0x4b,
    0x0, 0xb, 0x34, 0xa0, 0x0, 0x41, 0x4a, 0x0,
    0x0, 0x4, 0xa0, 0x0, 0x0, 0x4a, 0x0, 0x0,
    0x4, 0xa0, 0x0, 0x0,

    /* U+0073 "s" */
    0x1a, 0xdc, 0xc3, 0x8, 0x70, 0x2, 0xd0, 0x95,
    0x0, 0x0, 0x2, 0xdb, 0x96, 0x0, 0x0, 0x35,
    0x9c, 0x1, 0x0, 0x0, 0xc1, 0x97, 0x0, 0x1e,
    0x1, 0xbd, 0xdd, 0x50,

    /* U+0074 "t" */
    0x0, 0xf, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0,
    0x3d, 0xdf, 0xdd, 0xd2, 0x0, 0xf, 0x0, 0x0,
    0x0, 0xf, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0,
    0x0, 0xf, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0,
    0x0, 0xe, 0x10, 0x0, 0x0, 0x5, 0xdd, 0xd1,

    /* U+0075 "u" */
    0x95, 0x0, 0xe, 0x95, 0x0, 0xe, 0x95, 0x0,
    0xe, 0x95, 0x0, 0xe, 0x95, 0x0, 0xe, 0x86,
    0x0, 0xe, 0x4c, 0x0, 0x7a, 0x7, 0xdd, 0xa1,

    /* U+0076 "v" */
    0xd, 0x20, 0x0, 0xb4, 0x8, 0x70, 0x0, 0xe0,
    0x3, 0xc0, 0x5, 0x90, 0x0, 0xd1, 0xa, 0x40,
    0x0, 0x86, 0xd, 0x0, 0x0, 0x3b, 0x49, 0x0,
    0x0, 0xd, 0xa4, 0x0, 0x0, 0x8, 0xe0, 0x0,

    /* U+0077 "w" */
    0x57, 0x5, 0xc0, 0x1b, 0x2a, 0x8, 0xb0, 0x39,
    0xc, 0xa, 0x82, 0x66, 0xc, 0xa, 0x54, 0x83,
    0xb, 0x39, 0x37, 0xb1, 0x8, 0x86, 0xa, 0xb0,
    0x5, 0xd3, 0xb, 0xb0, 0x3, 0xf1, 0xb, 0x90,

    /* U+0078 "x" */
    0x9, 0x70, 0x1, 0xd1, 0x0, 0xd2, 0xb, 0x50,
    0x0, 0x4b, 0x5b, 0x0, 0x0, 0x9, 0xe1, 0x0,
    0x0, 0xb, 0xd2, 0x0, 0x0, 0x69, 0x3c, 0x0,
    0x2, 0xd0, 0x8, 0x70, 0xc, 0x40, 0x0, 0xd2,

    /* U+0079 "y" */
    0xd, 0x20, 0x0, 0xb4, 0x8, 0x70, 0x1, 0xe0,
    0x2, 0xd0, 0x6, 0x90, 0x0, 0xc3, 0xb, 0x30,
    0x0, 0x69, 0x1d, 0x0, 0x0, 0xd, 0x68, 0x0,
    0x0, 0xa, 0xe3, 0x0, 0x0, 0x4, 0xd0, 0x0,
    0x0, 0x7, 0x70, 0x0, 0x0, 0xc, 0x20, 0x0,
    0x0, 0x2c, 0x0, 0x0,

    /* U+007A "z" */
    0x7d, 0xdd, 0xed, 0x0, 0x0, 0xa, 0x70, 0x0,
    0x5, 0xb0, 0x0, 0x2, 0xd1, 0x0, 0x0, 0xc4,
    0x0, 0x0, 0x88, 0x0, 0x0, 0x3c, 0x0, 0x0,
    0x9, 0xed, 0xdd, 0xd0,

    /* U+007B "{" */
    0x0, 0x4, 0xcc, 0x0, 0xe, 0x20, 0x0, 0xe,
    0x0, 0x0, 0xe, 0x0, 0x0, 0xd, 0x10, 0x0,
    0xb, 0x30, 0x0, 0xc, 0x10, 0xad, 0xf7, 0x0,
    0x0, 0xc, 0x20, 0x0, 0xb, 0x20, 0x0, 0xe,
    0x0, 0x0, 0xe, 0x0, 0x0, 0xe, 0x20, 0x0,
    0x5, 0xcc,

    /* U+007C "|" */
    0x25, 0x4a, 0x4a, 0x4a, 0x4a, 0x4a, 0x4a, 0x4a,
    0x4a, 0x4a, 0x4a, 0x4a, 0x4a, 0x4a,

    /* U+007D "}" */
    0x7d, 0x80, 0x0, 0x0, 0xb, 0x50, 0x0, 0x0,
    0x77, 0x0, 0x0, 0x9, 0x50, 0x0, 0x0, 0xb2,
    0x0, 0x0, 0xd, 0x10, 0x0, 0x0, 0xb3, 0x0,
    0x0, 0x3, 0xfd, 0xd2, 0x0, 0xc2, 0x0, 0x0,
    0xd, 0x10, 0x0, 0x0, 0xa3, 0x0, 0x0, 0x8,
    0x60, 0x0, 0x0, 0xa6, 0x0, 0x7, 0xd9, 0x0,
    0x0,

    /* U+007E "~" */
    0x4c, 0xa0, 0x8, 0x3c, 0x15, 0xb0, 0xb3, 0xc0,
    0x6, 0xc9, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 134, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 134, .box_w = 3, .box_h = 10, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 15, .adv_w = 134, .box_w = 5, .box_h = 5, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 28, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 68, .adv_w = 134, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 121, .adv_w = 134, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 166, .adv_w = 134, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 211, .adv_w = 134, .box_w = 2, .box_h = 5, .ofs_x = 3, .ofs_y = 5},
    {.bitmap_index = 216, .adv_w = 134, .box_w = 5, .box_h = 14, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 251, .adv_w = 134, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 286, .adv_w = 134, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 318, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 343, .adv_w = 134, .box_w = 3, .box_h = 5, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 351, .adv_w = 134, .box_w = 6, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 354, .adv_w = 134, .box_w = 3, .box_h = 3, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 359, .adv_w = 134, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 408, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 443, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 478, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 513, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 548, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 578, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 613, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 648, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 683, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 718, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 753, .adv_w = 134, .box_w = 3, .box_h = 8, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 765, .adv_w = 134, .box_w = 4, .box_h = 11, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 787, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 815, .adv_w = 134, .box_w = 7, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 829, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 857, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 887, .adv_w = 134, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 939, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 979, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1014, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1049, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1084, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1119, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1154, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1189, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1219, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1249, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1284, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1319, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1354, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1389, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1419, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1454, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1489, .adv_w = 134, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1535, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1570, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1605, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1645, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1675, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1715, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1755, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1795, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1835, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1870, .adv_w = 134, .box_w = 4, .box_h = 14, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 1898, .adv_w = 134, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1947, .adv_w = 134, .box_w = 4, .box_h = 14, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 1975, .adv_w = 134, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1996, .adv_w = 134, .box_w = 8, .box_h = 1, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2000, .adv_w = 134, .box_w = 4, .box_h = 2, .ofs_x = 2, .ofs_y = 9},
    {.bitmap_index = 2004, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2028, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2063, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2091, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2121, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2149, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2189, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2222, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2252, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2291, .adv_w = 134, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2333, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2368, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2408, .adv_w = 134, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2440, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2464, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2492, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2531, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2564, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2592, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2620, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2660, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2684, .adv_w = 134, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2716, .adv_w = 134, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2748, .adv_w = 134, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2780, .adv_w = 134, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2824, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2852, .adv_w = 134, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2894, .adv_w = 134, .box_w = 2, .box_h = 14, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 2908, .adv_w = 134, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2957, .adv_w = 134, .box_w = 7, .box_h = 3, .ofs_x = 1, .ofs_y = 4}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 4,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t Font_Mono_Light_14 = {
#else
lv_font_t Font_Mono_Light_14 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 16,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if FONT_MONO_LIGHT_14*/

