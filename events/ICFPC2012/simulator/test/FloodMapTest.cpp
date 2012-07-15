#include "../inc/Game.h"
#include <fstream>

#include "gtest/gtest.h"

TEST(FloodMapTest, map1_parse) {
  ifstream ifs("map/flood1.map");
  Game game(ifs);
  Field &field = game.get_field();
  ASSERT_EQ(11, field.get_width());
  ASSERT_EQ(8, field.get_height());
}

TEST(FloodMapTest, map2_parse) {
  ifstream ifs("map/flood2.map");
  Game game(ifs);
  Field &field = game.get_field();
  ASSERT_EQ(7, field.get_width());
  ASSERT_EQ(7, field.get_height());
}

TEST(FloodMapTest, map3_parse) {
  ifstream ifs("map/flood3.map");
  Game game(ifs);
  Field &field = game.get_field();
  ASSERT_EQ(12, field.get_width());
  ASSERT_EQ(12, field.get_height());
}

TEST(FloodMapTest, map4_parse) {
  ifstream ifs("map/flood4.map");
  Game game(ifs);
  Field &field = game.get_field();
  ASSERT_EQ(37, field.get_width());
  ASSERT_EQ(19, field.get_height());
}

TEST(FloodMapTest, map5_parse) {
  ifstream ifs("map/flood5.map");
  Game game(ifs);
  Field &field = game.get_field();
  ASSERT_EQ(9, field.get_width());
  ASSERT_EQ(9, field.get_height());
}
