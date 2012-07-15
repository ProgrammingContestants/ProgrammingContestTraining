#include "../inc/Game.h"
#include <fstream>

#include "gtest/gtest.h"

TEST(TrampolineMapTest, map1_parse) {
  ifstream ifs("map/trampoline1.map");
  Game game(ifs);
  Field &field = game.get_field();
  ASSERT_EQ(17, field.get_width());
  ASSERT_EQ(6, field.get_height());
}

TEST(TrampolineMapTest, map2_parse) {
  ifstream ifs("map/trampoline2.map");
  Game game(ifs);
  Field &field = game.get_field();
  ASSERT_EQ(23, field.get_width());
  ASSERT_EQ(14, field.get_height());
}

TEST(TrampolineMapTest, map3_parse) {
  ifstream ifs("map/trampoline3.map");
  Game game(ifs);
  Field &field = game.get_field();
  ASSERT_EQ(39, field.get_width());
  ASSERT_EQ(25, field.get_height());
}
