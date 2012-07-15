#include "../inc/Game.h"
#include <fstream>

#include "gtest/gtest.h"

// ---------------------- parse test ---------------------- //

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

TEST(FirstMapTest, map10_parse) {
  ifstream ifs("map/contest10.map");
  Game game(ifs);
  Field &field = game.get_field();
  ASSERT_EQ(29, field.get_width());
  ASSERT_EQ(24, field.get_height());
}

// ---------------------- tests for simulating moving ---------------------- //

TEST(FirstMapTest, map1_play) {
  ifstream ifs("map/contest1.map");
  Game game(ifs);
  GameState s = game.moves("LDRDDLRULLLDL");
  ASSERT_EQ(212, s.get_score());
}

TEST(FirstMapTest, map2_play) {
  ifstream ifs("map/contest2.map");
  Game game(ifs);
  GameState s = game.moves("RRUDRRULURULLLLDDDL");
  ASSERT_EQ(281, s.get_score());
}

TEST(FirstMapTest, map3_play) {
  ifstream ifs("map/contest3.map");
  Game game(ifs);
  GameState s = game.moves("LDDDRRRRDDLLLLLDURRRRUURR");
  ASSERT_EQ(275, s.get_score());
}

// ---------------------- tests for finding best solution and simulating moving ---------------------- //

string cmd_prefix = "../ai.out < ";
string cmd_suffix = " > ret.out 2> /dev/null & sleep 150; kill $!";

TEST(FirstMapTest, map1_best) {
  string map_path = "map/contest1.map", cmds;
  system((cmd_prefix + map_path + cmd_suffix).c_str());
  ifstream ifs(map_path.c_str()), cmds_ifs("ret.out");
  cmds_ifs >> cmds;
  Game game(ifs);
  GameState s = game.moves(cmds);
  ASSERT_EQ(212, s.get_score());
}

TEST(FirstMapTest, map2_best) {
  string map_path = "map/contest2.map", cmds;
  system((cmd_prefix + map_path + cmd_suffix).c_str());
  ifstream ifs(map_path.c_str()), cmds_ifs("ret.out");
  cmds_ifs >> cmds;
  Game game(ifs);
  GameState s = game.moves(cmds);
  ASSERT_EQ(281, s.get_score());
}

TEST(FirstMapTest, map3_best) {
  string map_path = "map/contest3.map", cmds;
  system((cmd_prefix + map_path + cmd_suffix).c_str());
  ifstream ifs(map_path.c_str()), cmds_ifs("ret.out");
  cmds_ifs >> cmds;
  Game game(ifs);
  GameState s = game.moves(cmds);
  ASSERT_EQ(275, s.get_score());
}

TEST(FirstMapTest, map4_best) {
  string map_path = "map/contest4.map", cmds;
  system((cmd_prefix + map_path + cmd_suffix).c_str());
  ifstream ifs(map_path.c_str()), cmds_ifs("ret.out");
  cmds_ifs >> cmds;
  Game game(ifs);
  GameState s = game.moves(cmds);
  ASSERT_EQ(575, s.get_score());
}

TEST(FirstMapTest, map5_best) {
  string map_path = "map/contest5.map", cmds;
  system((cmd_prefix + map_path + cmd_suffix).c_str());
  ifstream ifs(map_path.c_str()), cmds_ifs("ret.out");
  cmds_ifs >> cmds;
  Game game(ifs);
  GameState s = game.moves(cmds);
  ASSERT_EQ(1303, s.get_score());
}

TEST(FirstMapTest, map6_best) {
  string map_path = "map/contest6.map", cmds;
  system((cmd_prefix + map_path + cmd_suffix).c_str());
  ifstream ifs(map_path.c_str()), cmds_ifs("ret.out");
  cmds_ifs >> cmds;
  Game game(ifs);
  GameState s = game.moves(cmds);
  ASSERT_EQ(1177, s.get_score());
}

TEST(FirstMapTest, map7_best) {
  string map_path = "map/contest7.map", cmds;
  system((cmd_prefix + map_path + cmd_suffix).c_str());
  ifstream ifs(map_path.c_str()), cmds_ifs("ret.out");
  cmds_ifs >> cmds;
  Game game(ifs);
  GameState s = game.moves(cmds);
  ASSERT_EQ(869, s.get_score());
}

TEST(FirstMapTest, map8_best) {
  string map_path = "map/contest8.map", cmds;
  system((cmd_prefix + map_path + cmd_suffix).c_str());
  ifstream ifs(map_path.c_str()), cmds_ifs("ret.out");
  cmds_ifs >> cmds;
  Game game(ifs);
  GameState s = game.moves(cmds);
  ASSERT_EQ(1973, s.get_score());
}

TEST(FirstMapTest, map9_best) {
  string map_path = "map/contest9.map", cmds;
  system((cmd_prefix + map_path + cmd_suffix).c_str());
  ifstream ifs(map_path.c_str()), cmds_ifs("ret.out");
  cmds_ifs >> cmds;
  Game game(ifs);
  GameState s = game.moves(cmds);
  ASSERT_EQ(3093, s.get_score());
}

TEST(FirstMapTest, map10_best) {
  string map_path = "map/contest10.map", cmds;
  system((cmd_prefix + map_path + cmd_suffix).c_str());
  ifstream ifs(map_path.c_str()), cmds_ifs("ret.out");
  cmds_ifs >> cmds;
  Game game(ifs);
  GameState s = game.moves(cmds);
  ASSERT_EQ(3634, s.get_score());
}
