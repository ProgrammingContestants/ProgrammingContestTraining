#include "../inc/Game.h"
#include <fstream>

#include "gtest/gtest.h"

TEST(FloodMapTest, map1_parse) {
  ifstream ifs("map/flood1.map");
  Game game(ifs);
  Field &field = game.get_field();
  ASSERT_EQ(11, field.get_width());
  ASSERT_EQ(8, field.get_height());
  Metadata &m = game.get_metadata();
  ASSERT_EQ(1, m.get_water());
  ASSERT_EQ(8, m.get_flooding());
  ASSERT_EQ(5, m.get_waterproof());
}

TEST(FloodMapTest, map2_parse) {
  ifstream ifs("map/flood2.map");
  Game game(ifs);
  Field &field = game.get_field();
  ASSERT_EQ(7, field.get_width());
  ASSERT_EQ(7, field.get_height());
  Metadata &m = game.get_metadata();
  ASSERT_EQ(5, m.get_flooding());
  ASSERT_EQ(3, m.get_waterproof());
}

TEST(FloodMapTest, map3_parse) {
  ifstream ifs("map/flood3.map");
  Game game(ifs);
  Field &field = game.get_field();
  ASSERT_EQ(12, field.get_width());
  ASSERT_EQ(12, field.get_height());
  Metadata &m = game.get_metadata();
  ASSERT_EQ(2, m.get_water());
  ASSERT_EQ(10, m.get_flooding());
  ASSERT_EQ(10, m.get_waterproof());
}

TEST(FloodMapTest, map4_parse) {
  ifstream ifs("map/flood4.map");
  Game game(ifs);
  Field &field = game.get_field();
  ASSERT_EQ(37, field.get_width());
  ASSERT_EQ(19, field.get_height());
  Metadata &m = game.get_metadata();
  ASSERT_EQ(1, m.get_water());
  ASSERT_EQ(20, m.get_flooding());
  ASSERT_EQ(10, m.get_waterproof());
}

TEST(FloodMapTest, map5_parse) {
  ifstream ifs("map/flood5.map");
  Game game(ifs);
  Field &field = game.get_field();
  ASSERT_EQ(9, field.get_width());
  ASSERT_EQ(9, field.get_height());
  Metadata &m = game.get_metadata();
  ASSERT_EQ(2, m.get_water());
  ASSERT_EQ(11, m.get_flooding());
  ASSERT_EQ(5, m.get_waterproof());
}
