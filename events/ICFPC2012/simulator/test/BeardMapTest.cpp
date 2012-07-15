#include "../inc/Game.h"
#include <fstream>

#include "gtest/gtest.h"

TEST(BeardMapTest, map1_parse) {
  ifstream ifs("map/beard1.map");
  Game game(ifs);
  Field &field = game.get_field();
  ASSERT_EQ(10, field.get_width());
  ASSERT_EQ(10, field.get_height());
}

TEST(BeardMapTest, map2_parse) {
  ifstream ifs("map/beard2.map");
  Game game(ifs);
  Field &field = game.get_field();
  ASSERT_EQ(30, field.get_width());
  ASSERT_EQ(15, field.get_height());
}

TEST(BeardMapTest, map3_parse) {
  ifstream ifs("map/beard3.map");
  Game game(ifs);
  Field &field = game.get_field();
  ASSERT_EQ(24, field.get_width());
  ASSERT_EQ(13, field.get_height());
}

TEST(BeardMapTest, map4_parse) {
  ifstream ifs("map/beard4.map");
  Game game(ifs);
  Field &field = game.get_field();
  ASSERT_EQ(20, field.get_width());
  ASSERT_EQ(16, field.get_height());
}
