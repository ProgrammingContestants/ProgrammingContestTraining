#!/bin/sh

g++ -o test/test test/*.cpp src/*.o ../gtest-1.6.0/gtest/gtest*.cc -I ../gtest-1.6.0/
test/test
