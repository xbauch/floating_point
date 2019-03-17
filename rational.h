#pragma once

#include <tuple>
#include <iostream>

template <typename T> struct ArbitraryRational {
  T numerator;
  T denominator;
  bool negative;

  ArbitraryRational(T numerator, T denominator)
      : numerator(numerator), denominator(denominator) {
    if (!is_internal_negative())
      return;
    negative = true;
    abs();
  }
  ArbitraryRational(const ArbitraryRational &other)
      : numerator(other.numerator), denominator(other.denominator),
        negative(other.negative) {}
  ArbitraryRational operator=(const ArbitraryRational &other) {
    numerator = other.numerator;
    denominator = other.denominator;
    return *this;
  }

  bool isZero() const { return numerator == 0; }

  bool isNegative() const { return negative; }

  bool is_internal_negative() const { return (numerator < 0) ^ (denominator < 0); }

  void abs() {
    if (numerator < 0)
      numerator = -numerator;
    if (denominator < 0)
      denominator = -denominator;
  }

  bool operator==(const ArbitraryRational &other) const {
    if (denominator == other.denominator)
      return numerator == other.numerator;
    auto lcm_p_q = extended_lcm(denominator, other.denominator);
    return std::get<1>(lcm_p_q) * numerator ==
           std::get<2>(lcm_p_q) * other.numerator;
  }

  /*  bool operator<(const ArbitraryRational &other) const {
    if (denominator == other.denominator)
      return numerator < other.numerator;
    auto lcm_p_q = extended_lcm(denominator, other.denominator);
    return std::get<1>(lcm_p_q) * numerator <
           std::get<2>(lcm_p_q) * other.numerator;
           }*/

  bool operator<(const ArbitraryRational &other) const {
    print();
    std::cout << "<";
    other.print();
    
    if (denominator == other.denominator) {
      std::cout << " " << (numerator < other.numerator) << std::endl;
      return numerator < other.numerator;
    }
    auto lcm_p_q = extended_lcm(denominator, other.denominator);
    std::cout << " " << (std::get<1>(lcm_p_q) * numerator <
                         std::get<2>(lcm_p_q) * other.numerator ? "true" : "false") << std::endl;
    return std::get<1>(lcm_p_q) * numerator <
      std::get<2>(lcm_p_q) * other.numerator;
  }

  bool operator>(const ArbitraryRational &other) const {
    print();
    std::cout << ">";
    other.print();
    
    if (denominator == other.denominator) {
      std::cout << " " << (numerator > other.numerator ? "true" : "false") << std::endl;
      return numerator > other.numerator;
    }
    auto lcm_p_q = extended_lcm(denominator, other.denominator);
    std::cout << " " << (std::get<1>(lcm_p_q) * numerator >
                         std::get<2>(lcm_p_q) * other.numerator ? "true" : "false") << std::endl;
    return std::get<1>(lcm_p_q) * numerator >
           std::get<2>(lcm_p_q) * other.numerator;
  }

  bool operator>=(const ArbitraryRational &other) const {
    //    print();
    //    std::cout << ">=";
    //    other.print();
    //    std::cout << " " << !(*this < other) << std::endl;
    return !(*this < other);
  }

  bool operator<=(const ArbitraryRational &other) const {
    //    print();
    //    std::cout << "<=";
    //    other.print();
    //    std::cout << " " << !(*this > other) << std::endl;
    return !(*this > other);
  }

  void print() const {
    std::cout << numerator << "/" << denominator;
  }

  void normalise() {
    if (numerator == 1)
      return; //nothing to do -- optimisation
    if (is_internal_negative()) {
      negative = true;
      abs();
    }

    //    std::cout << "before: "; print();
    auto gcd_p_q = extended_gcd(numerator, denominator);
    numerator = std::get<1>(gcd_p_q);
    denominator = std::get<2>(gcd_p_q);
    //    std::cout << " after: "; print(); std::cout << std::endl;
  }

  ArbitraryRational operator/(const ArbitraryRational &other) const {
    ArbitraryRational result(numerator, denominator);
    result.numerator *= other.denominator;
    result.denominator *= other.numerator;
    result.normalise();
    return result;
  }

  ArbitraryRational operator*(const ArbitraryRational &other) const {
    ArbitraryRational result(numerator, denominator);
    result.numerator *= other.numerator;
    result.denominator *= other.denominator;
    result.normalise();
    return result;
  }

  ArbitraryRational operator+(const ArbitraryRational &other) const {
    ArbitraryRational result(numerator, denominator);
    if (denominator == other.denominator)
      result.numerator += other.numerator;
    else {
      auto lcm_p_q = extended_lcm(denominator, other.denominator);
      result.numerator = numerator * std::get<1>(lcm_p_q) +
                         other.numerator * std::get<2>(lcm_p_q);
      result.denominator = std::get<0>(lcm_p_q);
      result.normalise();
    }
    return result;
  }

  ArbitraryRational operator-(const ArbitraryRational &other) const {
    ArbitraryRational result(numerator, denominator);
    if (denominator == other.denominator)
      result.numerator -= other.numerator;
    else {
      auto lcm_p_q = extended_lcm(denominator, other.denominator);
      result.numerator = numerator * std::get<1>(lcm_p_q) -
                         other.numerator * std::get<2>(lcm_p_q);
      result.denominator = std::get<0>(lcm_p_q);
      result.normalise();
    }
    return result;
  }

  ArbitraryRational operator/=(const ArbitraryRational &other) {
    numerator *= other.denominator;
    denominator *= other.numerator;
    normalise();
    return *this;
  }

  ArbitraryRational operator*=(const ArbitraryRational &other) {
    numerator *= other.numerator;
    denominator *= other.denominator;
    normalise();
    return *this;
  }
};
