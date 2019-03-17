#pragma once

#include <iostream>
#include <tuple>

/// \return <p,q>: p*b+q=a
template <typename T> std::pair<T, T> extended_divide(const T &a, const T &b) {
  assert(b != 0);
  if (a == 0)
    return std::pair<T, T>{0, 0};
  if (b > a)
    return std::pair<T, T>{0, b};

  auto divisor = a / b;
  assert(a > 0);

  T round = divisor * b;
  assert(round <= a);
  T remainder = round == a ? 0 : a - round;
  assert(remainder >= 0);
  assert(remainder < b);

  return std::pair<T, T>{divisor, remainder};
}

template <typename T> T gcd(const T &a, const T &b) {
  T temp_a(a);
  T temp_b(b);
  //  std::cout << "gcd of: " << a << " and " << b;

  if (a==0 || b==0)
    return 1;

  while (temp_a != temp_b) {
    if (temp_a == 0) {
      //            std::cout << " = " << temp_b << std::endl;
      return temp_b;
    }
    if (temp_b == 0) {
      //            std::cout << " = " << temp_a << std::endl;
      return temp_a;
    }

    if (temp_a > temp_b)
      temp_a = extended_divide(temp_a, temp_b).second;
    else if (temp_b > temp_a)
      temp_b = extended_divide(temp_b, temp_a).second;
  }
  //  std::cout << "(ok) = " << temp_a << std::endl;
  return temp_a;
}

/// \return <gdc,p,q>: gcd*p=a /\ gcd*q=b
template<typename T> std::tuple<T,T,T> extended_gcd(const T &a, const T &b) {
  T result_gcd = gcd(a,b);
  return std::tuple<T,T,T>{result_gcd, a/result_gcd, b/result_gcd};
}

template <typename T> T abs(const T &a) {
  if (a < 0)
    return -a;
  else
    return a;
}

template <typename T> T lcm(const T &a, const T &b) {
  return abs(a * b) / gcd(a, b);
}

/// \return <lcm, p, q>: p*a=q*b=lcm
template <typename T> std::tuple<T, T, T> extended_lcm(const T &a, const T &b) {
  assert(a != 0 && b != 0);
  T result_lcm = lcm(a, b);
  return std::tuple<T, T, T>{result_lcm, result_lcm / a, result_lcm / b};
}
