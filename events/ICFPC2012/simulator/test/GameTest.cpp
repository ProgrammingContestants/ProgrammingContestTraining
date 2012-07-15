#include "../inc/Game.h"
#include <fstream>

#include "gtest/gtest.h"

TEST(GameTest, map1_parse) {
  ifstream ifs("map/contest1.map");
  Game game(ifs);
  Field *field = game.get_field();
  ASSERT_EQ(6, field->get_width());
  ASSERT_EQ(6, field->get_height());
}

