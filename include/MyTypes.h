#pragma once
#include <cstdint>
#include <string>

//numbers
using signedTinyInt = std::int16_t;//short
using signedInt = std::int32_t; //int
using signedBigInt = std::int64_t;//long
using unsignedInt = std::uint32_t;// uns int
using unsignedBigInt = std::uint64_t; //uns long
// numbers end

//strings and symbols
using String = std::string;
using Byte = char; //-128 - 127
using unsignedByte = std::uint8_t; // 0 - 256
using winByte = wchar_t;
//strings and symbols end