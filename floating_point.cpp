#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "numerical.h"
#include "rational.h"
#include "integer.h"

#include "floating_point.h"

//using Integer = int64_t;
using Rational = ArbitraryRational<Integer>;

//using FloatingPointLiteral = std::vector<bool>;
using FPL = FloatingPointLiteral<BitVector>;


FPL ieee_754_conversion(const FloatingPointSize &ct,
                                         const Rational &ri) {
  if (ri.isZero())
    return FPL::make_zero(ct, false);
  bool is_negative = ri.isNegative();

  Rational r(ri);
  r.abs();
  Rational two(2, 1);

  Integer exp(0U);
  Integer inc(1U);
  Rational working(1, 1);

  if (r < working) {
    while (r < working) {
      exp -= inc;
      working /= two;
    }
  } else {
    while (r >= working) {
      exp += inc;
      working *= two;
    }
    exp -= inc;
    working /= two;
  }
  std::cout << "working: ";
  working.print();
  std::cout << std::endl;

  assert(working <= r);
  assert(r < working * two);

  Natural expBits = 2;
  Integer doubleInt(2);
  if (exp > 0) {
    Integer representable{4};
    while (representable <= exp) {
      representable *= doubleInt;
      ++expBits;
    }
  } else if (exp < 0) {
    Integer representable{-4};
    while ((representable + doubleInt) > exp) {
      representable *= doubleInt;
      ++expBits;
    }
  }
  ++expBits;

  BitVector exactExp = to_bitvector(exp, expBits);
  Natural sigBits = ct.significandWidth + 2;
  BitVector sig = to_bitvector(0U, sigBits);
  //BitVector one = to_bitvector(1U, sigBits);
  Rational workingSig(0, 1);

  for (Natural i = 0; i < sigBits - 1; ++i) {
    Rational mid(workingSig + working);
    std::cout << "workingSig: "; workingSig.print(); std::cout << std::endl;
    std::cout << "working: "; working.print(); std::cout << std::endl;
    std::cout << "mid: "; mid.print(); std::cout << std::endl;

    if (mid <= r) {
      //sig = bit_or(sig, one);
      sig.back()=true;
      workingSig = mid;
    }

    sig = left_shift(sig, 1);
    working /= two;
  }

  Rational remainder(r - workingSig);
  assert(Rational(0, 1) <= remainder);

  if (!remainder.isZero())
    //sig = bit_or(sig, one);
    sig.back()=true;

  FloatingPointSize exactFormat(expBits, sigBits);
  Natural width = expBits;

  // Could be improved to remove overflow concerns
  uint64_t minimumExponent = ((1 << (width - 1)) - 2) + (sigBits - 1);
  // Increase width until even the smallest subnormal can be normalised
  while ((1UL << (width - 1)) < minimumExponent) {
    ++width;
  }
  Natural extension = width - expBits;
  FPL exactFloat(is_negative, sign_extend(exactExp, extension), sig);

  return exactFloat;
  //return round(ct, exactFloat);
}

// FloatingPointLiteral round(const FloatingPointSize &uf, const FloatingPointLiteral &fpl) {
//   BitVector correctedExponentInRange(collar<t>(correctedExponent, minSubnormal, maxNormal));
//   BitVector roundedExponent(correctedExponentInRange.contract(currentExponentWidth - targetExponentWidth));

//   FloatingPointLiteral roundedResult(uf.getSign(), roundedExponent, roundedSignificand);
//   FloatingPointLiteral result(rounderSpecialCases<t>(format, roundingMode, roundedResult,
//                                                  overflow, underflow, uf.getZero()));

//   return fpl;
// }

void print_bv(const BitVector &bv) {
  for (const auto &b : bv)
    std::cout << (b ? "1" : "0");
  std::cout << std::endl;
}

int main() {
  FloatingPointSize fps(11, 53);
  Rational my_rational(2342, 2234);
  auto result = ieee_754_conversion(fps, my_rational);

  auto result_bv = result.to_bitvector(Precision::singleP);
  print_bv(result_bv);
  return 0;
}
