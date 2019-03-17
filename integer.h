#pragma once

#include <vector>

#include "bitvector.h"

struct Integer {
  std::vector<bool> data;

  Integer() = default;

  template<typename T>
  Integer(T integral_value) {
    from_integer(integral_value);
  }

  template<typename T>
  void from_integer(T value) {
    //TODO
  }

  Integer operator-() const {
    Integer result;
    //TODO
    return result;
  }

  Integer operator-(const Integer& other) const {
    Integer result;
    //TODO
    return result;
  }

  Integer operator-=(const Integer& other) {
    //TODO
    return *this;
  }

  Integer operator+(const Integer& other) const {
    Integer result;
    //TODO
    return result;
  }

  Integer operator+=(const Integer& other) {
    //TODO
    return *this;
  }

  Integer operator*=(const Integer& other) {
    //TODO
    return *this;
  }

  Integer operator*(const Integer& other) const {
    Integer result;
    //TODO
    return result;
  }

  Integer operator/(const Integer& other) const {
    Integer result;
    //TODO
    return result;
  }

  bool operator>(const Integer& other) const {
    //TODO
    return true;
  }

  bool operator==(const Integer& other) const {
    //TODO
    return true;
  }

  bool operator!=(const Integer& other) const {
    return !(*this ==other);
  }

  bool operator<(const Integer& other) const {
    //TODO
    return true;
  }

  bool operator>=(const Integer& other) const {
    return !(*this < other);
  }

  bool operator<=(const Integer& other) const {
    return !(*this > other);
  }

  template<typename O>
  friend O& operator<<(O &o, const Integer &other);

  Integer operator&(const Integer &other) {
    Integer result;
    //TODO
    return result;
  }
};

template<typename O>
O& operator<<(O& o, const Integer &other) {
  //TODO
  return o;
}
