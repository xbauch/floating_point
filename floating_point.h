#pragma once

#include <cstdint>
#include <cstddef>
#include <cassert>

using Natural = uint64_t;

enum class Precision { halfP, singleP, doubleP, quadrupleP, octupleP };

Natural exponent_bits(Precision p) {
  switch(p) {
  case Precision::halfP :
    return 5;
  case Precision::singleP :
    return 8;
  case Precision::doubleP :
    return 11;
  case Precision::quadrupleP :
    return 15;
  case Precision::octupleP :
    return 19;
  };
  assert(false);
  return Natural{};
}

Natural significand_bits(Precision p) {
  switch(p) {
  case Precision::halfP :
    return 11;
  case Precision::singleP :
    return 24;
  case Precision::doubleP :
    return 53;
  case Precision::quadrupleP :
    return 113;
  case Precision::octupleP :
    return 237;
  };
  assert(false);
  return Natural{};
}

struct FloatingPointSize {
  size_t exponentWidth;
  size_t significandWidth;

  FloatingPointSize(size_t exponentWidth, size_t significandWidth)
    : exponentWidth(exponentWidth), significandWidth(significandWidth) {}

  size_t size() const { return exponentWidth + significandWidth; }
};

template<typename BitVectorType>
struct FloatingPointLiteral {
  bool nan;
  bool inf;
  bool zero;

  bool sign;
  BitVectorType exponent;
  BitVectorType significand;

FloatingPointLiteral(bool sign, const BitVectorType &exponent,
                     const BitVectorType &significand)
: sign(sign), exponent(exponent), significand(significand) {}

  static FloatingPointLiteral make_zero(const FloatingPointSize &fps,
                                        bool sign) {
    return FloatingPointLiteral{sign, BitVectorType(fps.exponentWidth, false),
        BitVectorType(fps.significandWidth, false)};
  }


  BitVectorType to_bitvector(Precision p) const {
    BitVectorType result={sign};
    for (size_t i = 0; i < exponent_bits(p); i++)
      result.push_back(exponent[i]);
    for (size_t i = 0; i < significand_bits(p) - 1; i++)
      result.push_back(significand[i]);

    assert(result.size() == exponent_bits(p) + significand_bits(p));
    return result;
  }
};
