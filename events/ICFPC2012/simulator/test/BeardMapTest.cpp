#include "../inc/Game.h"
#include <fstream>

#include "gtest/gtest.h"

TEST(BeardMapTest, map1_parse) {
  ifstream ifs("map/beard1.map");
  Game game(ifs);
  Field &field = game.get_field();
  ASSERT_EQ(10, field.get_width());
  ASSERT_EQ(10, field.get_height());
  Metadata &m = game.get_metadata();
  ASSERT_EQ(15, m.get_growth());
  ASSERT_EQ(0, m.get_razors());
}

TEST(BeardMapTest, map2_parse) {
  ifstream ifs("map/beard2.map");
  Game game(ifs);
  Field &field = game.get_field();
  ASSERT_EQ(30, field.get_width());
  ASSERT_EQ(15, field.get_height());
  Metadata &m = game.get_metadata();
  ASSERT_EQ(25, m.get_growth());
  ASSERT_EQ(10, m.get_razors());
  ASSERT_EQ(20, m.get_flooding());
}

TEST(BeardMapTest, map3_parse) {
  ifstream ifs("map/beard3.map");
  Game game(ifs);
  Field &field = game.get_field();
  ASSERT_EQ(24, field.get_width());
  ASSERT_EQ(13, field.get_height());
  Metadata &m = game.get_metadata();
  ASSERT_EQ(10, m.get_growth());
  ASSERT_EQ('1', m.get_target_id('A'));
}

TEST(BeardMapTest, map4_parse) {
  ifstream ifs("map/beard4.map");
  Game game(ifs);
  Field &field = game.get_field();
  ASSERT_EQ(20, field.get_width());
  ASSERT_EQ(16, field.get_height());
}
