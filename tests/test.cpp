// Copyright 2021 Artem Artemov <theartemka6@mail.ru>

#include <gtest/gtest.h>

#include <cache.hpp>
#include <stdexcept>

TEST(Cache, frontTest) {
  CacheDiagnostics cd;
  cd.front_diagnostics(0);
  double time = cd.statistics[0].duration_front;
  if (time == 0.0) {
    FAIL();
  } else {
    SUCCEED();
  }
}

TEST(Cache, randomTest) {
  CacheDiagnostics cd;
  cd.random_diagnostics(4);
  double time = cd.statistics[4].duration_random;
  if (time == 0.0) {
    FAIL();
  } else {
    SUCCEED();
  }
}

TEST(Cache, reverseTest) {
  CacheDiagnostics cd;
  cd.reverse_diagnostics(0);
  double time = cd.statistics[0].duration_reverse;
  if (time == 0.0) {
    FAIL();
  } else {
    SUCCEED();
  }
}

TEST(Cache, fullDiagnosticsTest) {
  CacheDiagnostics cd;
  cd.full_diagnostics();
  double time = cd.statistics[4].duration_random;
  if (time == 0.0) {
    FAIL();
  } else {
    SUCCEED();
  }

  time = cd.statistics[3].duration_front;
  if (time == 0.0) {
    FAIL();
  } else {
    SUCCEED();
  }

  time = cd.statistics[2].duration_reverse;
  if (time == 0.0) {
    FAIL();
  } else {
    SUCCEED();
  }
}
