#include "../inc/Game.h"
#include <fstream>

#include "gtest/gtest.h"

TEST(FirstMapTest, map1_parse) {
  ifstream ifs("map/contest1.map");
  Game game(ifs);
  Field &field = game.get_field();
  ASSERT_EQ(6, field.get_width());
  ASSERT_EQ(6, field.get_height());
}

TEST(FirstMapTest, map2_parse) {
  ifstream ifs("map/contest2.map");
  Game game(ifs);
  Field &field = game.get_field();
  ASSERT_EQ(7, field.get_width());
  ASSERT_EQ(7, field.get_height());
}

TEST(FirstMapTest, map3_parse) {
  ifstream ifs("map/contest3.map");
  Game game(ifs);
  Field &field = game.get_field();
  ASSERT_EQ(8, field.get_width());
  ASSERT_EQ(9, field.get_height());
}

TEST(FirstMapTest, map4_parse) {
  ifstream ifs("map/contest4.map");
  Game game(ifs);
  Field &field = game.get_field();
  ASSERT_EQ(9, field.get_width());
  ASSERT_EQ(9, field.get_height());
}

TEST(FirstMapTest, map5_parse) {
  ifstream ifs("map/contest5.map");
  Game game(ifs);
  Field &field = game.get_field();
  ASSERT_EQ(12, field.get_width());
  ASSERT_EQ(12, field.get_height());
}

TEST(FirstMapTest, map6_parse) {
  ifstream ifs("map/contest6.map");
  Game game(ifs);
  Field &field = game.get_field();
  ASSERT_EQ(15, field.get_width());
  ASSERT_EQ(15, field.get_height());
}

TEST(FirstMapTest, map7_parse) {
  ifstream ifs("map/contest7.map");
  Game game(ifs);
  Field &field = game.get_field();
  ASSERT_EQ(19, field.get_width());
  ASSERT_EQ(9, field.get_height());
}

TEST(FirstMapTest, map8_parse) {
  ifstream ifs("map/contest8.map");
  Game game(ifs);
  Field &field = game.get_field();
  ASSERT_EQ(22, field.get_width());
  ASSERT_EQ(18, field.get_height());
}

TEST(FirstMapTest, map9_parse) {
  ifstream ifs("map/contest9.map");
  Game game(ifs);
  Field &field = game.get_field();
  ASSERT_EQ(26, field.get_width());
  ASSERT_EQ(17, field.get_height());
}

TEST(FirstMapTest, map1_best) {
  ifstream ifs("map/contest1.map");
  Game game(ifs);
  GameState s = game.moves("LDRDDUULLLDDL");
  ASSERT_EQ(212, s.get_score());
}

TEST(FirstMapTest, map3_best) {
  ifstream ifs("map/contest3.map");
  Game game(ifs);
  GameState s = game.moves("LDDDRRRRDDLLLLLDURRRRUURR");
  ASSERT_EQ(275, s.get_score());
}
