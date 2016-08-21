#ifndef GOLLUMHASH_H
#define GOLLUMHASH_H
#include <stdint.h>
#include "uint256.h"
#define l0l 512384
uint256 gollumhash(const uint8_t* in);
#endif