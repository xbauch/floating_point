#pragma once

#include <vector>
#include <cassert>

using BitVector = std::vector<bool>;

template<typename IntegralType>
BitVector to_bitvector(const IntegralType &i, size_t required_size) {
  BitVector result(required_size, false);
  if (i < 0)
    result[0] = true;

  for (size_t n = 0; n < required_size - 1; n++)
    result[required_size - (n+1)] = bool((1<<n)&i);

  return result;
}

BitVector bit_or(const BitVector &left, const BitVector &right) {
  BitVector result(left.size(), false);
  assert(left.size() == right.size());
  for (size_t i = 0; i < left.size(); i++) {
    result[i] = left[i] | right[i];
  }
  return result;
}

template<typename NaturalType>
BitVector left_shift(const BitVector &bv, const NaturalType &shift) {
  if (shift == 0)
    return bv;

  if (shift >= bv.size())
    return BitVector(bv.size(), false);

  BitVector result = bv;

  for (NaturalType i = 0; i < bv.size(); i++) {
    if (i + shift >= bv.size())
      result[i] = false;
    else
      result[i] = bv[i + shift];
  }
  return result;
}

template<typename NaturalType>
BitVector sign_extend(const BitVector &bv, const NaturalType extension) {
  BitVector result = bv;
  result.insert(result.begin() + 1, extension, false);
  return result;
}
