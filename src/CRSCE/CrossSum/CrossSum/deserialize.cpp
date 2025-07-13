// file: src/CRSCE/CrossSum/deserialize.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include <istream>
#include <cstdint>

#include "CRSCE/CrossSum/CrossSum.h"
#include "utils/Exceptions/InvalidHashLength.h"

/**
 * @brief Deserializes the CrossSum content from the input stream.
 *        Unpacks each of the s elements, each b bits wide, into the internal data array.
 *
 * @param is  Input stream to read from.
 * @throws Exceptions::InvalidHashLength  If the stream contains insufficient data.
 */
void CrossSum::deserialize(std::istream& is) const {
    uint8_t  bitBuf  = 0;
    int      bitsLeft = 0;

    auto readBit = [&]() -> bool {
        if (bitsLeft == 0) {
            if (!is.read(reinterpret_cast<char*>(&bitBuf), 1)) {
                throw Exceptions::InvalidHashLength(0);
            }
            bitsLeft = 8;
        }
        return (bitBuf >> (--bitsLeft)) & 0x1;
    };

    for (CrossSumIndex i = 0; i < s; ++i) {
        uint16_t value = 0;
        for (uint8_t j = 0; j < b; ++j) {
            value = static_cast<uint16_t>((value << 1) | static_cast<uint16_t>(readBit()));
        }
        data.at(i) = CrossSumValue(value);
    }
}
