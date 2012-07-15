#! /bin/bash
perl -e 'alarm shift; exec @ARGV' "$@";
