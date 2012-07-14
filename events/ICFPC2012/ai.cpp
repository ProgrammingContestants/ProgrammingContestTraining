#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <locale>
#include <queue>
#include <set>
#include "simulator/inc/Game.h"
#include "simulator/inc/Condition.h"

#define arr_size(array) (sizeof(array)/sizeof(*array))

using namespace std;

CommandType commands[] = { LEFT, RIGHT, UP, DOWN, WAIT, ABORT };

long str_hash(const string& str);


int main(int argc, char **argv)/*{{{*/
{
    queue<Game> game_queue;
    set<long> hashes;
    {
        Game game; // get map data from standard input
        game_queue.push(game);
    }
    while (!game_queue.empty()) {
        Game game = game_queue.front(); game_queue.pop();
        for (int i=0; i<arr_size(commands); i++) {
            Game next_game = game;
            next_game.move(commands[i]);

            string cond_str = next_game.get_condition().get_string();
            if (cond_str=="ABORTING" || cond_str=="LOSING") {
                continue;
            } else if (cond_str=="WINNING") {
                goto END_GAME;
            }

            string field_str = next_game.get_field().get_string();
            long field_hash = str_hash(field);

            if (hashes.find(field_hash)!=hashes.end()) continue;
            hahses.insert(field_hash);

            game_queue.push(next_game);
        }
    }

    END_GAME:

    return 0;
}/*}}}*/

static locale loc;
static const collate<char>& coll = use_facet<collate<char> >(loc);
long str_hash(const string& str) {
    return coll.hash(str.data(), str.data()+str.length());
}
