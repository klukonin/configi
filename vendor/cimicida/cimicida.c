#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#define LUA_LIB

static const char cimicida_code[] = {
   27, 76,117, 97, 83,  0, 25,147, 13, 10, 26, 10,  4,  8,  4,  8,  8,120,
   86,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 40,119, 64,  1,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  1,  4,171,  0,  0,  0, 11,  0,  6,  0,
   70, 64, 64,  0, 71,  0,192,  0, 10, 64,  0,128, 70, 64, 64,  0, 71,128,
  192,  0, 10, 64,  0,129, 70, 64, 64,  0, 71,192,192,  0, 10, 64,128,129,
   70, 64, 64,  0, 71,  0,193,  0, 10, 64,  0,130, 70, 64, 64,  0, 71, 64,
  193,  0, 10, 64,128,130, 70, 64, 64,  0, 71,128,193,  0, 10, 64,  0,131,
   70, 64, 64,  0, 71,192,193,  0, 10, 64,128,131, 70, 64, 64,  0, 71,  0,
  194,  0, 10, 64,  0,132, 70, 64, 64,  0, 71, 64,194,  0, 10, 64,128,132,
   70, 64, 64,  0, 71,128,194,  0, 10, 64,  0,133, 70, 64, 64,  0, 71,192,
  194,  0, 10, 64,128,133, 70, 64, 67,  0, 71,  0,195,  0, 10, 64,  0,134,
   70, 64, 67,  0, 71,128,195,  0, 10, 64,  0,135, 70, 64, 67,  0, 71,192,
  195,  0, 10, 64,128,135, 70, 64, 67,  0, 71,  0,196,  0, 10, 64,  0,136,
   70, 64, 67,  0, 71, 64,196,  0, 10, 64,128,136, 70, 64, 67,  0, 71,128,
  196,  0, 10, 64,  0,137, 70,192, 68,  0, 10, 64,128,137, 70,  0, 69,  0,
   10, 64,  0,138, 70, 64, 69,  0, 10, 64,128,138, 70,128, 69,  0, 10, 64,
    0,139, 70,192, 69,  0, 10, 64,128,139, 70,  0, 70,  0, 10, 64,  0,140,
   70,128, 70,  0, 71, 64,198,  0, 10, 64,128,140, 70,128, 70,  0, 71,192,
  198,  0, 10, 64,128,141, 70,128, 70,  0, 71,  0,199,  0, 10, 64,  0,142,
   70,128, 70,  0, 71, 64,199,  0, 10, 64,128,142, 70,128, 70,  0, 71,128,
  199,  0, 10, 64,  0,143, 70,  0, 72,  0, 71,192,199,  0, 10, 64,128,143,
   70,  0, 72,  0, 71, 64,200,  0, 10, 64,128,144, 70,  0, 72,  0, 71,128,
  200,  0, 10, 64,  0,145, 75,  0,  0,  0,139,  0,  0,  0,137,  0,  0,  0,
  236,  0,  0,  0, 74,192,128,145,236, 64,  0,  0, 74,192,  0,146,236,128,
    0,  0, 74,192,128,146,236,192,  0,  0, 74,192,  0,147,236,  0,  1,  0,
   74,192,128,147,236, 64,  1,  0, 74,192,  0,148,236,128,  1,  0, 74,192,
  128,148,236,192,  1,  0, 74,192,  0,149,236,  0,  2,  0, 74,192,128,149,
  236, 64,  2,  0, 74,192,  0,150,236,128,  2,  0, 74,192,128,150,236,192,
    2,  0, 74,192,  0,151,236,  0,  3,  0, 74,192,128,151,236, 64,  3,  0,
   74,192,  0,152,236,128,  3,  0, 74,192,128,152,236,192,  3,  0, 74,192,
    0,153,236,  0,  4,  0, 74,192,128,153,236, 64,  4,  0, 74,192,  0,154,
  236,128,  4,  0, 74,192,128,154,236,192,  4,  0, 74,192,  0,155,236,  0,
    5,  0, 74,192,128,155,236, 64,  5,  0, 74,192,  0,156,236,128,  5,  0,
   74,192,128,156,236,192,  5,  0, 74,192,  0,157,236,  0,  6,  0, 74,192,
  128,157,236, 64,  6,  0, 74,192,  0,158,236,128,  6,  0, 74,192,128,158,
  236,192,  6,  0, 74,192,  0,159,236,  0,  7,  0, 74,192,  0,133,236, 64,
    7,  0, 74,192,128,159,236,128,  7,  0, 74,192,  0,160,236,192,  7,  0,
   74,192,128,160,236,  0,  8,  0, 74,192,  0,161,236, 64,  8,  0, 74,192,
  128,142,236,128,  8,  0, 74,192,128,161,236,192,  8,  0, 74,192,  0,162,
  236,  0,  9,  0, 74,192,128,162,236, 64,  9,  0, 74,192,  0,163,236,128,
    9,  0, 74,192,128,163,102,  0,  0,  1, 38,  0,128,  0, 72,  0,  0,  0,
    4,  5,111,112,101,110,  4,  3,105,111,  4,  6, 99,108,111,115,101,  4,
    6,102,108,117,115,104,  4,  6,119,114,105,116,101,  4,  6,108,105,110,
  101,115,  4,  8,115,101,116,118, 98,117,102,  4,  6,105,110,112,117,116,
    4,  7,111,117,116,112,117,116,  4,  5,114,101, 97,100,  4,  6,112,111,
  112,101,110,  4,  7,115,116,100,101,114,114,  4,  5,102,105,110,100,  4,
    7,115,116,114,105,110,103,  4,  5,103,115,117, 98,  4,  7,102,111,114,
  109, 97,116,  4,  4,108,101,110,  4,  4,115,117, 98,  4,  7,103,109, 97,
  116, 99,104,  4,  5,116,121,112,101,  4,  6,112, 99, 97,108,108,  4,  5,
  108,111, 97,100,  4, 13,115,101,116,109,101,116, 97,116, 97, 98,108,101,
    4,  6,112, 97,105,114,115,  4,  7,105,112, 97,105,114,115,  4,  5,101,
  120,105,116,  4,  3,111,115,  4,  5,100, 97,116,101,  4,  9,100,105,102,
  102,116,105,109,101,  4,  5,116,105,109,101,  4,  8,101,120,101, 99,117,
  116,101,  4,  7, 99,111,110, 99, 97,116,  4,  6,116, 97, 98,108,101,  4,
    7,105,110,115,101,114,116,  4,  7,117,110,112, 97, 99,107,  4,  7,112,
  114,105,110,116,102,  4,  5,111,117,116,102,  4,  9, 97,112,112,101,110,
  100,108,110,  4,  7,101,114,114,111,114,102,  4,  7,112,101,114,114,111,
  114,  4,  9,119, 97,114,110,105,110,103,102,  4,  7,116,105,109,101,104,
  109,  4,  8,100, 97,116,101,121,109,100,  4, 10,116,105,109,101,115,116,
   97,109,112,  4,  5,104, 97,115,118,  4,  9, 97,114,114,116,111,114,101,
   99,  4,  8,108,110,116,111,116, 98,108,  4, 10,119,111,114,100,116,111,
  116, 98,108,  4,  9,115,116,114,116,111,116, 98,108,  4, 15,101,115, 99,
   97,112,101, 95,112, 97,116,116,101,114,110,  4, 11,102,105,108,116,101,
  114,116,118, 97,108,  4, 10,102,105,108,101,116,111,116, 98,108,  4,  6,
  116,102,105,110,100,  4, 10,115,104, 97,108,108,111,119, 99,112,  4,  7,
  115,112,108,105,116,112,  4,  7,105,115,102,105,108,101,  4,  6,102,111,
  112,101,110,  4,  7,102,119,114,105,116,101,  4,  6,103,101,116,108,110,
    4,  4,115,117, 98,  4,  8,101,120,105,116,115,116,114,  4,  7,116,114,
  117,116,104,121,  4,  6,102, 97,108,115,121,  4,  7,112,119,114,105,116,
  101,  4,  7,115,121,115,116,101,109,  4,  8,101,120,101, 99,117,116,101,
    4,  9,112,105,112,101,108,105,110,101,  4,  8,101,115, 99, 97,112,101,
  112,  4,  4,108,111,103,  4,  9,105,110,115,101,114,116,105,102,  4,  9,
  114,101,116,117,114,110,105,102,  4, 12,114,101,116,117,114,110,105,102,
  110,111,116,  1,  0,  0,  0,  1,  0, 39,  0,  0,  0,  0, 43,  0,  0,  0,
   45,  0,  0,  0,  1,  1,  5,  7,  0,  0,  0, 70,  0, 64,  0,134, 64, 64,
    0,192,  0,  0,  0, 45,  1,  0,  0,164,  0,  0,  0,100, 64,  0,  0, 38,
    0,128,  0,  2,  0,  0,  0,  4,  6,119,114,105,116,101,  4,  7,102,111,
  114,109, 97,116,  1,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0, 51,  0,  0,  0, 57,  0,  0,  0,  2,
    1,  7, 18,  0,  0,  0,134,  0, 64,  0,164,128,128,  0,198,  0, 64,  0,
    0,  1,  0,  0,228, 64,  0,  1,198, 64, 64,  0,  6,129, 64,  0, 64,  1,
  128,  0,173,  1,  0,  0, 36,  1,  0,  0,228,192,  0,  0, 70,  1, 64,  0,
  128,  1,  0,  1,100, 65,  0,  1, 64,  1,128,  1,128,  1,  0,  2,102,  1,
  128,  1, 38,  0,128,  0,  3,  0,  0,  0,  4,  7,111,117,116,112,117,116,
    4,  6,119,114,105,116,101,  4,  7,102,111,114,109, 97,116,  1,  0,  0,
    0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0, 63,  0,  0,  0, 65,  0,  0,  0,  2,  0,  6,  7,  0,  0,  0,134,
    0, 64,  0,193, 64,  0,  0,  0,  1,  0,  0, 64,  1,128,  0,165,  0,  0,
    2,166,  0,  0,  0, 38,  0,128,  0,  2,  0,  0,  0,  4,  7,102,111,114,
  109, 97,116,  4,  6, 37,115, 10, 37,115,  1,  0,  0,  0,  1,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 70,  0,  0,
    0, 73,  0,  0,  0,  1,  1,  5,  9,  0,  0,  0, 70,  0, 64,  0,134, 64,
  192,  0,192,  0,  0,  0, 45,  1,  0,  0,100, 64,  0,  0, 70,128,192,  0,
  129,192,  0,  0,100, 64,  0,  1, 38,  0,128,  0,  4,  0,  0,  0,  4,  5,
  111,117,116,102,  4,  7,115,116,100,101,114,114,  4,  5,101,120,105,116,
   19,  1,  0,  0,  0,  0,  0,  0,  0,  2,  0,  0,  0,  1,  1,  1,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 80,  0,
    0,  0, 86,  0,  0,  0,  2,  1,  5, 10,  0,  0,  0, 34,  0,  0,  0, 30,
  128,  0,128,131,  0,128,  0,166,  0,  0,  1, 30,192,  0,128,134,  0, 64,
    0,192,  0,128,  0, 45,  1,  0,  0,164, 64,  0,  0, 38,  0,128,  0,  1,
    0,  0,  0,  4,  7,101,114,114,111,114,102,  1,  0,  0,  0,  1,  1,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 91,  0,
    0,  0, 93,  0,  0,  0,  1,  1,  5,  6,  0,  0,  0, 70,  0, 64,  0,134,
   64,192,  0,192,  0,  0,  0, 45,  1,  0,  0,100, 64,  0,  0, 38,  0,128,
    0,  2,  0,  0,  0,  4,  5,111,117,116,102,  4,  7,115,116,100,101,114,
  114,  2,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0, 97,  0,  0,  0, 99,  0,  0,  0,  0,  0,
    2,  5,  0,  0,  0,  6,  0, 64,  0, 65, 64,  0,  0, 37,  0,  0,  1, 38,
    0,  0,  0, 38,  0,128,  0,  2,  0,  0,  0,  4,  5,100, 97,116,101,  4,
    6, 37, 72, 58, 37, 77,  1,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,104,  0,  0,  0,106,  0,  0,
    0,  0,  0,  2,  5,  0,  0,  0,  6,  0, 64,  0, 65, 64,  0,  0, 37,  0,
    0,  1, 38,  0,  0,  0, 38,  0,128,  0,  2,  0,  0,  0,  4,  5,100, 97,
  116,101,  4,  9, 37, 89, 45, 37,109, 45, 37,100,  1,  0,  0,  0,  1,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,110,
    0,  0,  0,112,  0,  0,  0,  0,  0,  2,  5,  0,  0,  0,  6,  0, 64,  0,
   65, 64,  0,  0, 37,  0,  0,  1, 38,  0,  0,  0, 38,  0,128,  0,  2,  0,
    0,  0,  4,  5,100, 97,116,101,  4, 23, 37, 89, 45, 37,109, 45, 37,100,
   32, 37, 72, 58, 37, 77, 58, 37, 83, 32, 37, 90, 37,122,  1,  0,  0,  0,
    1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,118,  0,  0,  0,123,  0,  0,  0,  2,  0, 11, 17,  0,  0,  0,134,  0,
   64,  0,192,  0,  0,  0,164,  0,  1,  1, 30, 64,  2,128,198, 65, 64,  0,
    0,  2,  0,  3, 65,130,  0,  0,129,194,  0,  0,228,129,  0,  2,128,  1,
  128,  3, 31, 64,  0,  3, 30, 64,  0,128,195,  1,128,  0,230,  1,  0,  1,
  169,128,  0,  0, 42,193,252,127, 38,  0,128,  0,  4,  0,  0,  0,  4,  6,
  112, 97,105,114,115,  4,  5,103,115,117, 98,  4,  5, 91, 37, 99, 93,  4,
    1,  1,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,130,  0,  0,  0,134,  0,  0,  0,  2,  0,  8, 10,
    0,  0,  0,139,  0,  0,  0,193,  0,  0,  0, 28,  1,  0,  0, 65,  1,  0,
    0,232, 64,  0,128,199,129,  1,  0,138, 64,128,  3,231,  0,255,127,166,
    0,  0,  1, 38,  0,128,  0,  1,  0,  0,  0, 19,  1,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,140,  0,  0,  0,149,  0,  0,  0,  1,  0,  8, 16,  0,
    0,  0, 75,  0,  0,  0, 34, 64,  0,  0, 30,  0,  0,128,102,  0,  0,  1,
  134,  0, 64,  0,192,  0,  0,  0,  1, 65,  0,  0,164,  0,129,  1, 30,128,
    0,128,156,  1,128,  0,141,129, 64,  3, 74, 64,  1,  3,169, 64,  0,  0,
   42,129,254,127,102,  0,  0,  1, 38,  0,128,  0,  3,  0,  0,  0,  4,  7,
  103,109, 97,116, 99,104,  4,  9, 40, 91, 94, 10, 93, 42, 41, 10, 19,  1,
    0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,154,  0,  0,  0,160,  0,
    0,  0,  1,  0,  8, 13,  0,  0,  0, 75,  0,  0,  0,134,  0, 64,  0,192,
    0,  0,  0,  1, 65,  0,  0,164,  0,129,  1, 30,128,  0,128,156,  1,128,
    0,141,129, 64,  3, 74, 64,  1,  3,169, 64,  0,  0, 42,129,254,127,102,
    0,  0,  1, 38,  0,128,  0,  3,  0,  0,  0,  4,  7,103,109, 97,116, 99,
  104,  4,  4, 37,119, 43, 19,  1,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,
    0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,165,  0,  0,  0,171,  0,  0,  0,  1,  0,  8, 13,  0,  0,  0, 75,
    0,  0,  0,134,  0, 64,  0,192,  0,  0,  0,  1, 65,  0,  0,164,  0,129,
    1, 30,128,  0,128,156,  1,128,  0,141,129, 64,  3, 74, 64,  1,  3,169,
   64,  0,  0, 42,129,254,127,102,  0,  0,  1, 38,  0,128,  0,  3,  0,  0,
    0,  4,  7,103,109, 97,116, 99,104,  4,  4, 37, 83, 43, 19,  1,  0,  0,
    0,  0,  0,  0,  0,  1,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,177,  0,  0,  0,195,  0,  0,  0,
    1,  0,  6, 21,  0,  0,  0, 75, 64,  3,  0, 74, 64, 64,128, 74,192, 64,
  129, 74, 64, 65,130, 74,192, 65,131, 74, 64, 66,132, 74,192, 66,133, 74,
   64, 67,134, 74,192, 67,135, 74, 64, 68,136, 74,192, 68,137, 74, 64, 69,
  138, 74,192, 69,139, 74, 64, 70,140,134,128, 70,  0,192,  0,  0,  0,  1,
  129,  2,  0, 64,  1,128,  0,165,  0,  0,  2,166,  0,  0,  0, 38,  0,128,
    0, 27,  0,  0,  0,  4,  2, 94,  4,  3, 37, 94,  4,  2, 36,  4,  3, 37,
   36,  4,  2, 40,  4,  3, 37, 40,  4,  2, 41,  4,  3, 37, 41,  4,  2, 37,
    4,  3, 37, 37,  4,  2, 46,  4,  3, 37, 46,  4,  2, 91,  4,  3, 37, 91,
    4,  2, 93,  4,  3, 37, 93,  4,  2, 42,  4,  3, 37, 42,  4,  2, 43,  4,
    3, 37, 43,  4,  2, 45,  4,  3, 37, 45,  4,  2, 63,  4,  3, 37, 63,  4,
    2,  0,  4,  3, 37,122,  4,  5,103,115,117, 98,  1,  0,  0,  0,  1,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,203,
    0,  0,  0,221,  0,  0,  0,  3,  0, 14, 38,  0,  0,  0,162, 64,  0,  0,
   30,  0,  0,128,132,  0,  0,  0,220,  0,  0,  0,  1,  1,  0,  0, 65, 65,
    0,  0,128,  1,128,  1,193, 65,  0,  0,104,  1,  2,128, 70,130, 64,  0,
  135,  2,  2,  0,192,  2,128,  0,  1, 67,  0,  0, 64,  3,  0,  1,100,130,
  128,  2, 98,  2,  0,  0, 30,  0,  0,128, 10,192, 64,  4,103, 65,253,127,
   65, 65,  0,  0,128,  1,128,  1,193, 65,  0,  0,104, 65,  1,128, 71,  2,
    2,  0, 95,192,192,  4, 30,128,  0,128, 13, 65, 64,  2, 71,  2,  2,  0,
   10, 64,  2,  2,103,  1,254,127, 77, 65, 64,  2,128,  1,128,  1,193, 65,
    0,  0,104,  1,  0,128, 10,192, 64,  4,103, 65,255,127, 38,  0,  0,  1,
   38,  0,128,  0,  4,  0,  0,  0, 19,  0,  0,  0,  0,  0,  0,  0,  0, 19,
    1,  0,  0,  0,  0,  0,  0,  0,  4,  5,102,105,110,100,  0,  1,  0,  0,
    0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,227,  0,  0,  0,238,  0,  0,  0,  1,  0, 10, 25,  0,  0,  0, 70,
    0, 64,  0,134, 64, 64,  0,192,  0,  0,  0,  1,129,  0,  0,100,192,  0,
    2,162,  0,  0,  0, 30,  0,  4,128,198,192, 64,  0,  0,  1,  0,  1,228,
   64,  0,  1,203,  0,  0,  0, 12,  1, 65,  1,129, 65,  1,  0, 36,  1,129,
    1, 30,128,  0,128, 28,  2,128,  1, 13,130, 65,  4,202,192,  1,  4, 41,
   65,  0,  0,170,129,254,127,  6,193, 65,  0, 64,  1,  0,  1, 36, 65,  0,
    1,230,  0,  0,  1, 38,  0,128,  0,  8,  0,  0,  0,  4,  6,112, 99, 97,
  108,108,  4,  5,111,112,101,110,  4,  3,114,101,  4,  6,102,108,117,115,
  104,  4,  6,108,105,110,101,115,  4,  3, 42, 76, 19,  1,  0,  0,  0,  0,
    0,  0,  0,  4,  6, 99,108,111,115,101,  1,  0,  0,  0,  1,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,246,  0,  0,
    0,255,  0,  0,  0,  3,  0, 15, 24,  0,  0,  0,162, 64,  0,  0, 30,  0,
    0,128,132,  0,  0,  0,196,  0,128,  0, 65,  1,  0,  0,156,  1,  0,  0,
  193,  1,  0,  0,104, 65,  3,128, 70, 66, 64,  0,134,130, 64,  0,199,  2,
    2,  0,  0,  3,128,  0, 65,  3,  0,  0,128,  3,  0,  1,100,194,  0,  3,
    0,  1,  0,  5,192,  0,128,  4,226,  0,  0,  0, 30,128,  0,128, 34,  1,
    0,  0, 30,  0,  0,128, 38,  2,  0,  1,103,  1,252,127, 38,  0,128,  0,
    3,  0,  0,  0, 19,  1,  0,  0,  0,  0,  0,  0,  0,  4,  6,112, 99, 97,
  108,108,  4,  5,102,105,110,100,  1,  0,  0,  0,  1,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  5,  1,  0,  0, 16,
    1,  0,  0,  1,  0,  9, 20,  0,  0,  0, 68,  0,  0,  0,139,  0,  0,  0,
   64,  0,  0,  1,134,  0, 64,  0,192,  0,  0,  0,164,  0,  1,  1, 30,  0,
    2,128,198, 65,192,  0,  0,  2,  0,  3,228,129,  0,  1, 31,128,192,  3,
   30,128,  0,128,203,  1,  0,  0, 74,192,129,  2, 30,  0,  0,128, 74,128,
  129,  2,169,128,  0,  0, 42,  1,253,127,102,  0,  0,  1, 38,  0,128,  0,
    3,  0,  0,  0,  4,  6,112, 97,105,114,115,  4,  5,116,121,112,101,  4,
    6,116, 97, 98,108,101,  2,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 22,  1,  0,  0, 34,
    1,  0,  0,  1,  0,  7, 37,  0,  0,  0, 70,  0, 64,  0,128,  0,  0,  0,
  100,128,  0,  1,134, 64, 64,  0,192,  0,  0,  0,  0,  1,128,  0, 64,  1,
  128,  0,164,128,  0,  2, 32, 64,  0,129, 30, 64,  2,128, 95,192, 64,  1,
   30,192,  1,128, 78,  0,193,  0,198, 64, 64,  0,  0,  1,  0,  0, 64,  1,
  128,  0,128,  1,128,  0,228,128,  0,  2,128,  0,128,  1, 30,192,252,127,
   31,128,192,  0, 30,192,  0,128,193, 64,  1,  0,  0,  1,  0,  0,230,  0,
  128,  1, 30, 64,  2,128,198, 64, 64,  0,  0,  1,  0,  0, 65,  1,  1,  0,
  142,  1,193,  0,228,128,  0,  2,  6, 65, 64,  0, 64,  1,  0,  0,141,  1,
  193,  0, 36,  1,128,  1,230,  0,  0,  0, 38,  0,128,  0,  6,  0,  0,  0,
    4,  4,108,101,110,  4,  4,115,117, 98, 19,  0,  0,  0,  0,  0,  0,  0,
    0,  4,  2, 47, 19,  1,  0,  0,  0,  0,  0,  0,  0,  4,  1,  1,  0,  0,
    0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0, 40,  1,  0,  0, 46,  1,  0,  0,  1,  0,  4, 12,  0,  0,  0, 70,
    0, 64,  0,128,  0,  0,  0,193, 64,  0,  0,100,128,128,  1, 98,  0,  0,
    0, 30,  0,  1,128,134,128, 64,  0,192,  0,128,  0,164, 64,  0,  1,131,
    0,128,  0,166,  0,  0,  1, 38,  0,128,  0,  3,  0,  0,  0,  4,  5,111,
  112,101,110,  4,  3,114, 98,  4,  6, 99,108,111,115,101,  1,  0,  0,  0,
    1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0, 51,  1,  0,  0, 59,  1,  0,  0,  1,  0, 10, 23,  0,  0,  0, 68,  0,
    0,  0,134,  0, 64,  0,192,  0,  0,  0,  1, 65,  0,  0,164,  0,129,  1,
   30,192,  1,128,134,129, 64,  0,193,193,  0,  0, 35, 66,128,  0, 30,  0,
    0,128,  1,  2,  1,  0, 64,  2,128,  2,164,129,  0,  2, 64,  0,  0,  3,
  169, 64,  0,  0, 42, 65,253,127,134, 64, 65,  0,192,  0,128,  0,164,128,
    0,  1, 95,128, 65,  1, 30,  0,  0,128,102,  0,  0,  1, 38,  0,128,  0,
    7,  0,  0,  0,  4,  6,108,105,110,101,115,  3,  0,  0,  0,  0,  0,  0,
  176, 64,  4,  7,102,111,114,109, 97,116,  4,  5, 37,115, 37,115,  4,  1,
    4,  4,108,101,110, 19,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,
    1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0, 66,  1,  0,  0, 80,  1,  0,  0,  3,  0, 10, 31,  0,  0,  0,198,  0,
   64,  0,  6, 65, 64,  0,162, 64,  0,  0, 30,  0,  0,128,129,128,  0,  0,
   70,193, 64,  0,128,  1,  0,  0,192,  1,  0,  1,100,129,128,  1, 98,  1,
    0,  0, 30,128,  4,128,140,  1,192,  2,  1,  2,  1,  0,164, 65,128,  1,
  140, 65,192,  2,  0,  2,128,  0,164,193,128,  1,  6, 66, 65,  0, 64,  2,
  128,  2, 36, 66,  0,  1,  6,130, 65,  0, 64,  2,128,  2, 36, 66,  0,  1,
  226,  1,  0,  0, 30,128,  0,128,  4,  2,  0,  0, 64,  2,128,  3, 38,  2,
  128,  1,  3,  2,128,  0, 38,  2,  0,  1, 38,  0,128,  0,  7,  0,  0,  0,
    4,  8,115,101,116,118, 98,117,102,  4,  6,119,114,105,116,101,  4,  4,
  119,101, 43,  4,  5,111,112,101,110,  4,  3,110,111,  4,  6,102,108,117,
  115,104,  4,  6, 99,108,111,115,101,  1,  0,  0,  0,  1,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 87,  1,  0,  0,
   94,  1,  0,  0,  2,  0, 10, 16,  0,  0,  0,134,  0, 64,  0,192,  0,128,
    0,164,128,  0,  1,193, 64,  0,  0,  6,129,192,  0, 64,  1,  0,  1,129,
  193,  0,  0, 36,  1,129,  1, 30,192,  0,128,205,  0,193,  1, 31,  0,128,
    1, 30,  0,  0,128,230,  1,  0,  1, 41, 65,  0,  0,170, 65,254,127, 38,
    0,128,  0,  5,  0,  0,  0,  4,  6,102,111,112,101,110, 19,  0,  0,  0,
    0,  0,  0,  0,  0,  4,  7,103,109, 97,116, 99,104,  4,  9, 40, 91, 94,
   10, 93, 42, 41, 10, 19,  1,  0,  0,  0,  0,  0,  0,  0,  2,  0,  0,  0,
    1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,105,  1,  0,  0,126,  1,  0,  0,  2,  0,  9, 12,  0,  0,  0,
  139,  0,  0,  0,196,  0,  0,  0,  6,  1, 64,  0, 70, 65, 64,  0,128,  1,
    0,  0,193,129,  0,  0, 44,  2,  0,  0, 36,193,128,  2,  0,  0,128,  2,
  192,  0,  0,  2, 38,  0,  0,  1, 38,  0,128,  0,  3,  0,  0,  0,  4,  6,
  112, 99, 97,108,108,  4,  5,103,115,117, 98,  4, 22,123,123, 91, 37,115,
   93, 45, 40, 91, 37,103, 93, 43, 41, 91, 37,115, 93, 45,125,125,  1,  0,
    0,  0,  1,  0,  1,  0,  0,  0,  0,108,  1,  0,  0,124,  1,  0,  0,  1,
    0, 11, 27,  0,  0,  0, 70,  0,192,  0,  8, 64,  0,128, 65, 64,  0,  0,
  134,128,192,  0,192,  0,128,  0,  0,  1,  0,  0,164,128,128,  1,198,192,
  192,  0,  0,  1,  0,  1, 64,  1,  0,  1,129,  1,  1,  0,198, 65,193,  0,
    5,  2,  0,  0, 75, 66,  0,  0,133,  2,  0,  1, 74,130,  2,131,228,  1,
  128,  1,228,192,  0,  0,226,  0,  0,  0, 30,  0,  1,128, 64,  1,128,  1,
  100, 65,128,  0, 70,193, 65,  0,102,  1,  0,  1, 30,  0,  0,128, 38,  0,
    0,  1, 38,  0,128,  0,  8,  0,  0,  0,  4,  5,116,121,112,101, 20, 86,
   32, 32, 32, 32, 32, 32, 32, 32, 86, 61, 37,115, 10, 32, 32, 32, 32, 32,
   32, 32, 32,105,102, 32,116,121,112,101, 40, 86, 41, 32, 61, 61, 32, 34,
  102,117,110, 99,116,105,111,110, 34, 32,116,104,101,110, 10, 32, 32, 32,
   32, 32, 32, 32, 32, 32, 32, 86, 61, 86, 40, 41, 10, 32, 32, 32, 32, 32,
   32, 32, 32,101,110,100, 10, 32, 32, 32, 32, 32, 32,  4,  7,102,111,114,
  109, 97,116,  4,  5,108,111, 97,100,  4,  2,116,  4, 13,115,101,116,109,
  101,116, 97,116, 97, 98,108,101,  4,  8, 95, 95,105,110,100,101,120,  4,
    2, 86,  3,  0,  0,  0,  1,  2,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,134,  1,  0,  0,141,  1,  0,  0,  3,  0,  7, 21,  0,
    0,  0, 95,  0,192,  0, 30, 64,  0,128, 31, 64,192,  0, 30, 64,  1,128,
  198,128, 64,  0,  1,193,  0,  0, 64,  1,  0,  0,128,  1,  0,  1,229,  0,
    0,  2,230,  0,  0,  0, 95,  0,193,  0, 30, 64,  0,128, 31, 64,193,  0,
   30, 64,  1,128,198,128, 64,  0,  1,129,  1,  0, 64,  1,  0,  0,128,  1,
    0,  1,229,  0,  0,  2,230,  0,  0,  0, 38,  0,128,  0,  7,  0,  0,  0,
    4,  5,101,120,105,116,  4,  7,101,120,105,116,101,100,  4,  7,102,111,
  114,109, 97,116,  4, 24, 37,115, 58, 32, 69,120,105,116,101,100, 32,119,
  105,116,104, 32, 99,111,100,101, 32, 37,115,  4,  7,115,105,103,110, 97,
  108,  4,  7,107,105,108,108,101,100,  4, 21, 37,115, 58, 32, 67, 97,117,
  103,104,116, 32,115,105,103,110, 97,108, 32, 37,115,  1,  0,  0,  0,  1,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  146,  1,  0,  0,154,  1,  0,  0,  1,  0,  2, 13,  0,  0,  0, 95,  0, 64,
    0, 30,192,  1,128, 95, 64, 64,  0, 30, 64,  1,128, 95,128, 64,  0, 30,
  192,  0,128, 95,192, 64,  0, 30, 64,  0,128, 31,  0, 65,  0, 30, 64,  0,
  128, 67,  0,128,  0,102,  0,  0,  1, 38,  0,128,  0,  5,  0,  0,  0,  4,
    4,121,101,115,  4,  4, 89, 69, 83,  4,  5,116,114,117,101,  4,  5, 84,
  114,117,101,  4,  5, 84, 82, 85, 69,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,159,  1,  0,  0,167,  1,
    0,  0,  1,  0,  2, 13,  0,  0,  0, 95,  0, 64,  0, 30,192,  1,128, 95,
   64, 64,  0, 30, 64,  1,128, 95,128, 64,  0, 30,192,  0,128, 95,192, 64,
    0, 30, 64,  0,128, 31,  0, 65,  0, 30, 64,  0,128, 67,  0,128,  0,102,
    0,  0,  1, 38,  0,128,  0,  5,  0,  0,  0,  4,  3,110,111,  4,  3, 78,
   79,  4,  6,102, 97,108,115,101,  4,  6, 70, 97,108,115,101,  4,  6, 70,
   65, 76, 83, 69,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,182,  1,  0,  0,209,  1,  0,  0,  4,  0, 14,
   61,  0,  0,  0, 11,  1,  0,  0, 65,  1,  0,  0, 98,  0,  0,  0, 30,192,
    1,128,134, 65, 64,  0,193,129,  0,  0,  0,  2,128,  2, 64,  2,128,  0,
  128,  2,  0,  0,164,129,128,  2,  0,  0,  0,  3, 30, 64,  1,128,134, 65,
   64,  0,193,193,  0,  0,  0,  2,128,  2, 64,  2,  0,  0,164,129,  0,  2,
    0,  0,  0,  3,134,  1, 65,  0,192,  1,  0,  0,  1, 66,  1,  0,164,129,
  128,  1,198,129, 65,  0,  0,  2,  0,  3,228, 65,  0,  1,203,  1,  0,  0,
   12,194, 65,  3, 36,  2,  1,  1, 30,128,  0,128, 28,  3,128,  3, 13,  3,
   66,  6,202,193,  2,  6, 41, 66,  0,  0,170,130,254,127,  4,  2,  0,  0,
   70,194, 66,  0,128,  2,  0,  3,100,  2,  1,  1, 10,193,  2,133, 10,129,
  130,132,  0,  2,128,  4, 10, 65, 67,134,226,  0,  0,  0, 30,192,  0,128,
   71,130, 66,  2,128,  2,  0,  2,102,  2,128,  1, 30,192,  2,128,162, 64,
    0,  0, 30,128,  0,128, 71,130, 66,  2, 31,128,195,  4, 30,192,  0,128,
   64,  2,128,  3,128,  2,  0,  2,102,  2,128,  1, 30,128,  0,128, 68,  2,
    0,  0,128,  2,  0,  2,102,  2,128,  1, 38,  0,128,  0, 15,  0,  0,  0,
    4, 48, 32, 32,115,101,116, 32, 45,101,102, 10, 32, 32,101,120,112,111,
  114,116, 32, 76, 67, 95, 65, 76, 76, 61, 67, 10, 32, 32,101,120,101, 99,
   32, 48, 62, 38, 45, 32, 50, 62, 38, 49, 10, 32, 32,  4,  7,102,111,114,
  109, 97,116,  4, 11, 37,115, 99,100, 32, 37,115, 10, 37,115,  4,  5, 37,
  115, 37,115,  4,  6,112,111,112,101,110,  4,  3,114,101,  4,  6,102,108,
  117,115,104,  4,  6,108,105,110,101,115, 19,  1,  0,  0,  0,  0,  0,  0,
    0,  4,  7,115,116, 97,116,117,115,  4,  5, 99,111,100,101,  4,  6, 99,
  108,111,115,101,  4,  4, 98,105,110,  4,  9,105,111, 46,112,111,112,101,
  110, 19,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  1,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,223,  1,  0,
    0,239,  1,  0,  0,  2,  0,  9, 33,  0,  0,  0,139,  0,  0,  0,198,  0,
   64,  0,  1, 65,  0,  0, 64,  1,  0,  0, 29, 64,  1,  2,  6,129, 64,  0,
   64,  1,  0,  0,129,193,  0,  0, 36,129,128,  1, 70,  1, 65,  0,128,  1,
    0,  2,100, 65,  0,  1, 76,  1, 64,  2,192,  1,128,  0,100, 65,128,  1,
   68,  1,  0,  0,134,193, 65,  0,192,  1,  0,  2,164,  1,  1,  1,138,  0,
    2,131,138,192,129,130, 64,  1,  0,  3,135,129, 65,  1, 31,  0, 66,  3,
   30,192,  0,128,131,  1,128,  0,192,  1,  0,  1,166,  1,128,  1, 30,128,
    0,128,132,  1,  0,  0,192,  1,  0,  1,166,  1,128,  1, 38,  0,128,  0,
    9,  0,  0,  0,  4,  6,119,114,105,116,101,  4, 36, 32, 32,115,101,116,
   32, 45,101,102, 10, 32, 32,101,120,112,111,114,116, 32, 76, 67, 95, 65,
   76, 76, 61, 67, 10, 32, 32,101,120,101, 99, 32,  4,  6,112,111,112,101,
  110,  4,  3,119,101,  4,  6,102,108,117,115,104,  4,  7,115,116, 97,116,
  117,115,  4,  5, 99,111,100,101,  4,  6, 99,108,111,115,101, 19,  0,  0,
    0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,251,  1,  0,  0, 10,  2,  0,
    0,  1,  0,  9, 25,  0,  0,  0, 75,  0,  0,  0,129,  0,  0,  0,193, 64,
    0,  0,  4,  1,  0,  0, 70,  1, 65,  0,128,  1,  0,  1,192,  1,  0,  0,
    0,  2,128,  1,157,  1,  2,  3,100,  1,  1,  1, 74,192,129,129, 74,128,
    1,129,  0,  1,128,  2, 74,128,193,130, 71,193,192,  0, 31,192,193,  2,
   30,192,  0,128, 67,  1,128,  0,128,  1,128,  0,102,  1,128,  1, 30,128,
    0,128, 68,  1,  0,  0,128,  1,128,  0,102,  1,128,  1, 38,  0,128,  0,
    8,  0,  0,  0,  4, 65, 32, 32,115,101,116, 32, 45,101,102, 10, 32, 32,
  101,120,112,111,114,116, 32, 76, 67, 95, 65, 76, 76, 61, 67, 10, 32, 32,
  101,120,101, 99, 32, 48, 62, 38, 45, 32, 50, 62, 38, 45, 32, 49, 62, 47,
  100,101,118, 47,110,117,108,108, 10, 32, 32,101,120,101, 99, 32,  4, 24,
   32, 48, 62, 38, 45, 32, 50, 62, 38, 45, 32, 49, 62, 47,100,101,118, 47,
  110,117,108,108, 32,  4,  7,115,116, 97,116,117,115,  4,  5, 99,111,100,
  101,  4,  8,101,120,101, 99,117,116,101,  4,  4, 98,105,110,  4, 11,111,
  115, 46,101,120,101, 99,117,116,101, 19,  0,  0,  0,  0,  0,  0,  0,  0,
    1,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0, 18,  2,  0,  0, 30,  2,  0,  0,  1,  0,  7, 22,  0,
    0,  0, 75,  0,  0,  0,129,  0,  0,  0,196,  0,  0,  0,  6,193, 64,  0,
   64,  1,  0,  1,128,  1,  0,  0, 93,129,129,  2, 36,  1,  1,  1, 74,128,
    1,129, 74, 64,129,128,192,  0,  0,  2,  7,129,192,  0, 31,  0, 65,  2,
   30,192,  0,128,  3,  1,128,  0, 64,  1,128,  0, 38,  1,128,  1, 30,128,
    0,128,  4,  1,  0,  0, 64,  1,128,  0, 38,  1,128,  1, 38,  0,128,  0,
    5,  0,  0,  0,  4, 42, 32, 32,115,101,116, 32, 45,101,102, 10, 32, 32,
  101,120,101, 99, 32, 48, 62, 38, 45, 32, 50, 62, 38, 45, 32, 49, 62, 47,
  100,101,118, 47,110,117,108,108, 10, 32, 32,  4,  7,115,116, 97,116,117,
  115,  4,  5, 99,111,100,101,  4,  8,101,120,101, 99,117,116,101, 19,  0,
    0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 35,  2,  0,  0, 49,  2,
    0,  0,  0,  1, 10, 44,  0,  0,  0, 11,  0,  0,  0, 75,  0,  0,  0,173,
    0,  0,  0,107, 64,  0,  0,129,  0,  0,  0,220,  0,128,  0,  1, 65,  0,
    0,168,  0,  3,128,156,  1,  0,  0,141, 65, 64,  3,198,129, 64,  0,  7,
   66,129,  0, 65,194,  0,  0,228,129,128,  1, 10,192,  1,  3,156,  1,128,
    0, 95,128,129,  2, 30,128,  0,128,156,  1,  0,  0,141, 65, 64,  3, 10,
    0, 65,  3,167, 64,252,127,135, 64,192,  0, 31, 64, 65,  1, 30,128,  1,
  128,134, 64,193,  0,198,128, 64,  0,  0,  1,  0,  0,228,  0,  0,  1,165,
    0,  0,  0,166,  0,  0,  0, 30,128,  2,128,135, 64,192,  0, 31,128, 65,
    1, 30,128,  1,128,134,128,193,  0,198,128, 64,  0,  0,  1,  0,  0,228,
    0,  0,  1,165,  0,  0,  0,166,  0,  0,  0, 30,  0,  0,128, 38,  0,128,
    0, 38,  0,128,  0,  7,  0,  0,  0, 19,  2,  0,  0,  0,  0,  0,  0,  0,
   19,  1,  0,  0,  0,  0,  0,  0,  0,  4,  7, 99,111,110, 99, 97,116,  4,
    2, 32,  4,  4, 32,124, 32,  4,  6,112,111,112,101,110,  4,  8,101,120,
  101, 99,117,116,101,  2,  0,  0,  0,  1,  0,  1,  1,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 56,  2,  0,  0, 60,  2,
    0,  0,  1,  1,  7, 17,  0,  0,  0, 70,  0, 64,  0,100,128,128,  0,139,
    0,  0,  0,192,  0,  0,  0, 45,  1,  0,  0,228,  0,  0,  0,171, 64,  0,
    0,198, 64, 64,  0,  0,  1,  0,  1,228,128,  0,  1,  6,129, 64,  0, 70,
    1, 64,  0,100,129,128,  0,128,  1,128,  0, 36,  1,128,  1,230,  0,  0,
    0, 38,  0,128,  0,  3,  0,  0,  0,  4,  5,116,105,109,101,  4,  7,117,
  110,112, 97, 99,107,  4,  9,100,105,102,102,116,105,109,101,  1,  0,  0,
    0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0, 65,  2,  0,  0, 69,  2,  0,  0,  1,  0,  5, 14,  0,  0,  0, 70,
    0, 64,  0,128,  0,  0,  0,193, 64,  0,  0,  1,129,  0,  0,100,128,  0,
    2,  0,  0,128,  0, 70,  0, 64,  0,128,  0,  0,  0,193,192,  0,  0,  1,
    1,  1,  0,100,128,  0,  2,  0,  0,128,  0, 38,  0,  0,  1, 38,  0,128,
    0,  5,  0,  0,  0,  4,  5,103,115,117, 98,  4,  2, 34,  4,  3, 92, 34,
    4,  2, 39,  4,  3, 92, 39,  1,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 76,  2,  0,  0, 95,  2,
    0,  0,  3,  0, 14, 33,  0,  0,  0,198,  0, 64,  0, 44,  1,  0,  0, 64,
    1,  0,  2,128,  1,  0,  0,100,129,  0,  1,129, 65,  0,  0,198,129, 64,
    0,  1,194,  0,  0,228,129,  0,  1, 12,  2,192,  2,129,  2,  1,  0, 36,
   66,128,  1,  6, 66,193,  0, 64,  2,128,  2,128,  2,  0,  3,192,  2,128,
    3,  0,  3,128,  0, 64,  3,  0,  1, 36,194,  0,  3,134,130, 65,  0,192,
    2,128,  2,164, 66,  0,  1,134,194, 65,  0,192,  2,128,  2,164, 66,  0,
    1, 98,  2,  0,  0, 30,128,  0,128,132,  2,  0,  0,192,  2,128,  4,166,
    2,128,  1,131,  2,128,  0,166,  2,  0,  1, 38,  0,128,  0,  8,  0,  0,
    0,  4,  8,115,101,116,118, 98,117,102,  4, 11, 37,115, 32, 37,115, 58,
   32, 37,115, 10,  4,  5,100, 97,116,101,  4, 12, 37, 97, 32, 37, 98, 32,
   37,100, 32, 37, 84,  4,  5,108,105,110,101,  4,  5,111,117,116,102,  4,
    6,102,108,117,115,104,  4,  6, 99,108,111,115,101,  2,  0,  0,  0,  1,
    0,  1,  1,  1,  0,  0,  0,  0, 78,  2,  0,  0, 83,  2,  0,  0,  1,  0,
    4,  8,  0,  0,  0, 70,  0, 64,  0,128,  0,  0,  0,193, 64,  0,  0,100,
  128,128,  1, 98,  0,  0,  0, 30,  0,  0,128,102,  0,  0,  1, 38,  0,128,
    0,  2,  0,  0,  0,  4,  5,111,112,101,110,  4,  4, 97,101, 43,  1,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,104,  2,  0,
    0,115,  2,  0,  0,  4,  0, 14, 26,  0,  0,  0, 34,  0,  0,  0, 30,128,
    5,128,  6,  1, 64,  0, 64,  1,128,  1, 36,129,  0,  1, 31, 64, 64,  2,
   30,  0,  3,128,  6,129, 64,  0, 64,  1,128,  1, 36,  1,  1,  1, 30, 64,
    1,128, 78,194,192,  3,134,  2, 65,  0,192,  2,128,  0, 13, 67,  2,  1,
   64,  3,  0,  4,164, 66,  0,  2, 41,129,  0,  0,170,193,253,127, 30,  0,
    1,128,  6,  1, 65,  0, 64,  1,128,  0,128,  1,  0,  1,192,  1,128,  1,
   36, 65,  0,  2, 38,  0,128,  0,  5,  0,  0,  0,  4,  5,116,121,112,101,
    4,  6,116, 97, 98,108,101,  4,  7,105,112, 97,105,114,115, 19,  1,  0,
    0,  0,  0,  0,  0,  0,  4,  7,105,110,115,101,114,116,  1,  0,  0,  0,
    1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,122,  2,  0,  0,126,  2,  0,  0,  2,  0,  2,  4,  0,  0,  0, 34,  0,
    0,  0, 30,  0,  0,128,102,  0,  0,  1, 38,  0,128,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,132,  2,  0,  0,136,  2,  0,  0,  2,  0,  2,  6,  0,  0,  0,
   95,  0, 64,  0, 30, 64,  0,128, 31, 64, 64,  0, 30,  0,  0,128,102,  0,
    0,  1, 38,  0,128,  0,  2,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,
};
static const size_t cimicida_code_size = sizeof cimicida_code;

LUALIB_API int luaopen_cimicida (lua_State *L) {
  luaL_loadbuffer(L, cimicida_code, cimicida_code_size, "cimicida");
  lua_pcall(L, 0, LUA_MULTRET, 0);
  return 1;
}
