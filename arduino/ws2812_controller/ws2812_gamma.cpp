// ws2812_gamma.cpp
//
// dithering tables with gamma correction

#include <stdint.h>
#include "ws2812_gamma.h"

static const uint8_t  gamma0[] = {
     0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
     2,   2,   2,   2,   2,   2,   2,   3,   3,   3,   3,   3,   4,   4,   4,   4,
     5,   5,   5,   5,   6,   6,   6,   6,   7,   7,   7,   8,   8,   8,   9,   9,
    10,  10,  10,  11,  11,  12,  12,  12,  13,  13,  14,  14,  15,  15,  16,  16,
    17,  17,  18,  18,  19,  19,  20,  20,  21,  21,  22,  23,  23,  24,  24,  25,
    26,  26,  27,  28,  28,  29,  30,  30,  31,  32,  32,  33,  34,  34,  35,  36,
    37,  37,  38,  39,  40,  41,  41,  42,  43,  44,  45,  45,  46,  47,  48,  49,
    50,  51,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,  64,
    65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  80,  81,
    82,  83,  84,  85,  86,  88,  89,  90,  91,  92,  94,  95,  96,  97,  98, 100,
   101, 102, 103, 105, 106, 107, 109, 110, 111, 113, 114, 115, 117, 118, 119, 121,
   122, 123, 125, 126, 128, 129, 130, 132, 133, 135, 136, 138, 139, 141, 142, 144,
   145, 147, 148, 150, 151, 153, 154, 156, 157, 159, 161, 162, 164, 165, 167, 169,
   170, 172, 173, 175, 177, 178, 180, 182, 183, 185, 187, 189, 190, 192, 194, 196,
   197, 199, 201, 203, 204, 206, 208, 210, 212, 213, 215, 217, 219, 221, 223, 225,
   226, 228, 230, 232, 234, 236, 238, 240, 242, 244, 246, 248, 250, 252, 254, 255 };

static const uint8_t  gamma1[] = {
     0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1,   1,   1,
     1,   1,   1,   1,   2,   2,   2,   2,   2,   2,   3,   3,   3,   3,   4,   4,
     4,   4,   5,   5,   5,   5,   6,   6,   6,   7,   7,   7,   8,   8,   8,   9,
     9,   9,  10,  10,  11,  11,  11,  12,  12,  13,  13,  14,  14,  15,  15,  16,
    16,  17,  17,  18,  18,  19,  19,  20,  20,  21,  21,  22,  23,  23,  24,  24,
    25,  26,  26,  27,  28,  28,  29,  30,  30,  31,  32,  32,  33,  34,  35,  35,
    36,  37,  38,  38,  39,  40,  41,  42,  42,  43,  44,  45,  46,  47,  47,  48,
    49,  50,  51,  52,  53,  54,  55,  56,  56,  57,  58,  59,  60,  61,  62,  63,
    64,  65,  66,  67,  68,  69,  70,  71,  73,  74,  75,  76,  77,  78,  79,  80,
    81,  82,  84,  85,  86,  87,  88,  89,  91,  92,  93,  94,  95,  97,  98,  99,
   100, 102, 103, 104, 105, 107, 108, 109, 111, 112, 113, 115, 116, 117, 119, 120,
   121, 123, 124, 126, 127, 128, 130, 131, 133, 134, 136, 137, 139, 140, 142, 143,
   145, 146, 148, 149, 151, 152, 154, 155, 157, 158, 160, 162, 163, 165, 166, 168,
   170, 171, 173, 175, 176, 178, 180, 181, 183, 185, 186, 188, 190, 192, 193, 195,
   197, 199, 200, 202, 204, 206, 207, 209, 211, 213, 215, 217, 218, 220, 222, 224,
   226, 228, 230, 232, 233, 235, 237, 239, 241, 243, 245, 247, 249, 251, 253, 255 };

static const uint8_t  gamma2[] = {
     0,   0,   0,   0,   0,   0,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,
     1,   1,   2,   2,   2,   2,   2,   2,   3,   3,   3,   3,   3,   4,   4,   4,
     4,   5,   5,   5,   5,   6,   6,   6,   7,   7,   7,   8,   8,   8,   9,   9,
     9,  10,  10,  10,  11,  11,  12,  12,  13,  13,  13,  14,  14,  15,  15,  16,
    16,  17,  17,  18,  18,  19,  19,  20,  21,  21,  22,  22,  23,  24,  24,  25,
    25,  26,  27,  27,  28,  29,  29,  30,  31,  31,  32,  33,  33,  34,  35,  36,
    36,  37,  38,  39,  39,  40,  41,  42,  43,  43,  44,  45,  46,  47,  48,  49,
    49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,  64,
    65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79,  80,
    82,  83,  84,  85,  86,  87,  88,  90,  91,  92,  93,  94,  96,  97,  98,  99,
   101, 102, 103, 104, 106, 107, 108, 110, 111, 112, 114, 115, 116, 118, 119, 120,
   122, 123, 125, 126, 127, 129, 130, 132, 133, 134, 136, 137, 139, 140, 142, 143,
   145, 146, 148, 149, 151, 152, 154, 156, 157, 159, 160, 162, 163, 165, 167, 168,
   170, 172, 173, 175, 177, 178, 180, 182, 183, 185, 187, 188, 190, 192, 194, 195,
   197, 199, 201, 202, 204, 206, 208, 210, 211, 213, 215, 217, 219, 221, 222, 224,
   226, 228, 230, 232, 234, 236, 238, 240, 241, 243, 245, 247, 249, 251, 253, 255 };

static const uint8_t  gamma3[] = {
     0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1,
     1,   1,   1,   1,   1,   1,   2,   2,   2,   2,   2,   3,   3,   3,   3,   4,
     4,   4,   4,   5,   5,   5,   5,   6,   6,   6,   7,   7,   7,   8,   8,   8,
     9,   9,  10,  10,  10,  11,  11,  12,  12,  12,  13,  13,  14,  14,  15,  15,
    16,  16,  17,  17,  18,  18,  19,  20,  20,  21,  21,  22,  22,  23,  24,  24,
    25,  25,  26,  27,  27,  28,  29,  29,  30,  31,  32,  32,  33,  34,  34,  35,
    36,  37,  37,  38,  39,  40,  41,  41,  42,  43,  44,  45,  45,  46,  47,  48,
    49,  50,  51,  52,  53,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,
    64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  76,  77,  78,  79,  80,
    81,  82,  83,  84,  86,  87,  88,  89,  90,  92,  93,  94,  95,  96,  98,  99,
   100, 101, 103, 104, 105, 107, 108, 109, 110, 112, 113, 114, 116, 117, 118, 120,
   121, 123, 124, 125, 127, 128, 130, 131, 133, 134, 135, 137, 138, 140, 141, 143,
   144, 146, 147, 149, 150, 152, 153, 155, 157, 158, 160, 161, 163, 165, 166, 168,
   169, 171, 173, 174, 176, 178, 179, 181, 183, 184, 186, 188, 190, 191, 193, 195,
   197, 198, 200, 202, 204, 205, 207, 209, 211, 213, 214, 216, 218, 220, 222, 224,
   226, 228, 229, 231, 233, 235, 237, 239, 241, 243, 245, 247, 249, 251, 253, 255 };

static const uint8_t  gamma4[] = {
     0,   0,   0,   0,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
     1,   2,   2,   2,   2,   2,   2,   2,   3,   3,   3,   3,   3,   4,   4,   4,
     4,   5,   5,   5,   5,   6,   6,   6,   7,   7,   7,   8,   8,   8,   9,   9,
     9,  10,  10,  11,  11,  11,  12,  12,  13,  13,  14,  14,  14,  15,  15,  16,
    16,  17,  17,  18,  19,  19,  20,  20,  21,  21,  22,  22,  23,  24,  24,  25,
    25,  26,  27,  27,  28,  29,  29,  30,  31,  31,  32,  33,  34,  34,  35,  36,
    37,  37,  38,  39,  40,  40,  41,  42,  43,  44,  44,  45,  46,  47,  48,  49,
    50,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,  64,
    65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79,  81,
    82,  83,  84,  85,  86,  87,  89,  90,  91,  92,  93,  95,  96,  97,  98, 100,
   101, 102, 103, 105, 106, 107, 108, 110, 111, 112, 114, 115, 116, 118, 119, 120,
   122, 123, 125, 126, 127, 129, 130, 132, 133, 135, 136, 138, 139, 140, 142, 143,
   145, 146, 148, 149, 151, 153, 154, 156, 157, 159, 160, 162, 164, 165, 167, 168,
   170, 172, 173, 175, 177, 178, 180, 182, 183, 185, 187, 188, 190, 192, 194, 195,
   197, 199, 201, 202, 204, 206, 208, 210, 211, 213, 215, 217, 219, 221, 223, 224,
   226, 228, 230, 232, 234, 236, 238, 240, 242, 244, 245, 247, 249, 251, 253, 255 };

static const uint8_t  gamma5[] = {
     0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1,   1,
     1,   1,   1,   1,   1,   2,   2,   2,   2,   2,   3,   3,   3,   3,   3,   4,
     4,   4,   4,   5,   5,   5,   6,   6,   6,   6,   7,   7,   7,   8,   8,   9,
     9,   9,  10,  10,  10,  11,  11,  12,  12,  13,  13,  14,  14,  14,  15,  15,
    16,  16,  17,  17,  18,  19,  19,  20,  20,  21,  21,  22,  23,  23,  24,  24,
    25,  26,  26,  27,  28,  28,  29,  30,  30,  31,  32,  32,  33,  34,  35,  35,
    36,  37,  38,  38,  39,  40,  41,  41,  42,  43,  44,  45,  46,  46,  47,  48,
    49,  50,  51,  52,  53,  54,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,
    64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  75,  76,  77,  78,  79,  80,
    81,  82,  83,  85,  86,  87,  88,  89,  90,  92,  93,  94,  95,  97,  98,  99,
   100, 102, 103, 104, 105, 107, 108, 109, 111, 112, 113, 115, 116, 117, 119, 120,
   121, 123, 124, 126, 127, 128, 130, 131, 133, 134, 136, 137, 138, 140, 141, 143,
   144, 146, 147, 149, 151, 152, 154, 155, 157, 158, 160, 161, 163, 165, 166, 168,
   170, 171, 173, 174, 176, 178, 179, 181, 183, 185, 186, 188, 190, 191, 193, 195,
   197, 198, 200, 202, 204, 206, 207, 209, 211, 213, 215, 216, 218, 220, 222, 224,
   226, 228, 230, 231, 233, 235, 237, 239, 241, 243, 245, 247, 249, 251, 253, 255 };

static const uint8_t  gamma6[] = {
     0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1,   1,   1,   1,   1,
     1,   1,   1,   2,   2,   2,   2,   2,   2,   3,   3,   3,   3,   3,   4,   4,
     4,   4,   5,   5,   5,   5,   6,   6,   6,   7,   7,   7,   8,   8,   8,   9,
     9,  10,  10,  10,  11,  11,  12,  12,  12,  13,  13,  14,  14,  15,  15,  16,
    16,  17,  17,  18,  18,  19,  19,  20,  20,  21,  22,  22,  23,  23,  24,  25,
    25,  26,  26,  27,  28,  28,  29,  30,  30,  31,  32,  33,  33,  34,  35,  36,
    36,  37,  38,  39,  39,  40,  41,  42,  43,  43,  44,  45,  46,  47,  48,  48,
    49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  58,  59,  60,  61,  62,  63,
    64,  65,  66,  67,  68,  69,  71,  72,  73,  74,  75,  76,  77,  78,  79,  80,
    81,  83,  84,  85,  86,  87,  88,  90,  91,  92,  93,  94,  96,  97,  98,  99,
   101, 102, 103, 104, 106, 107, 108, 109, 111, 112, 113, 115, 116, 117, 119, 120,
   122, 123, 124, 126, 127, 129, 130, 131, 133, 134, 136, 137, 139, 140, 142, 143,
   145, 146, 148, 149, 151, 152, 154, 155, 157, 159, 160, 162, 163, 165, 167, 168,
   170, 171, 173, 175, 176, 178, 180, 181, 183, 185, 186, 188, 190, 192, 193, 195,
   197, 199, 200, 202, 204, 206, 208, 209, 211, 213, 215, 217, 219, 220, 222, 224,
   226, 228, 230, 232, 234, 236, 237, 239, 241, 243, 245, 247, 249, 251, 253, 255 };

static const uint8_t  gamma7[] = {
     0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,
     1,   1,   1,   1,   1,   1,   2,   2,   2,   2,   2,   2,   3,   3,   3,   3,
     4,   4,   4,   4,   5,   5,   5,   6,   6,   6,   7,   7,   7,   8,   8,   8,
     9,   9,   9,  10,  10,  11,  11,  11,  12,  12,  13,  13,  14,  14,  15,  15,
    16,  16,  17,  17,  18,  18,  19,  19,  20,  21,  21,  22,  22,  23,  23,  24,
    25,  25,  26,  27,  27,  28,  29,  29,  30,  31,  31,  32,  33,  34,  34,  35,
    36,  37,  37,  38,  39,  40,  40,  41,  42,  43,  44,  45,  45,  46,  47,  48,
    49,  50,  51,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,
    64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  78,  79,  80,
    81,  82,  83,  84,  86,  87,  88,  89,  90,  91,  93,  94,  95,  96,  98,  99,
   100, 101, 103, 104, 105, 106, 108, 109, 110, 112, 113, 114, 116, 117, 118, 120,
   121, 122, 124, 125, 127, 128, 130, 131, 132, 134, 135, 137, 138, 140, 141, 143,
   144, 146, 147, 149, 150, 152, 153, 155, 156, 158, 160, 161, 163, 164, 166, 168,
   169, 171, 173, 174, 176, 178, 179, 181, 183, 184, 186, 188, 189, 191, 193, 195,
   196, 198, 200, 202, 203, 205, 207, 209, 211, 213, 214, 216, 218, 220, 222, 224,
   226, 227, 229, 231, 233, 235, 237, 239, 241, 243, 245, 247, 249, 251, 253, 255 };


#if WS2812_DITHER_NUM == 1
  const uint8_t *gamma_dither[WS2812_DITHER_NUM] = {gamma0};
#elif WS2812_DITHER_NUM == 2
  const uint8_t *gamma_dither[WS2812_DITHER_NUM] = {gamma0,gamma1};
#elif WS2812_DITHER_NUM == 4
  const uint8_t *gamma_dither[WS2812_DITHER_NUM] = {gamma0,gamma1,gamma2,gamma3};
#elif WS2812_DITHER_NUM == 8
  const uint8_t *gamma_dither[WS2812_DITHER_NUM] = {gamma0,gamma1,gamma2,gamma3,gamma4,gamma5,gamma6,gamma7};
#else
  #error Invalid WS2812_DITHER_NUM value. Allowed values are 1, 2, 4, 8
#endif

// end of file