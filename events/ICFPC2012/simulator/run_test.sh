#!/bin/sh

g++ -o test/test test/*.cpp ../gtest-1.6.0/gtest/gtest*.cc -I ../gtest-1.6.0/
test/test
