#pragma once

#include <iostream>
#include <vector>
#include <bitset>
#include <stack>
#include <fstream>

#define BITS 16
#define OPCODE 5
#define PARAMETER BITS-OPCODE
#define FLAGS 3

#include "Memory.hpp"
#include "Registers.hpp"
#include "RKS-16.hpp"