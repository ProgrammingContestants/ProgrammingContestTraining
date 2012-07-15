#include "../inc/Game.h"

#include "gtest/gtest.h"

TEST(GameTest, constructor) {
  string map = "";
  map += "######\n";
  map += "#. *R#\n";
  map += "#  \.#\n";
  map += "#\ * #\n";
  map += "L  .\#\n";
  map += "######\n";
  Game game();
}

