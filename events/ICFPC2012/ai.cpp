#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <locale>
#include <queue>
#include <set>
#include "simulator/inc/Game.h"
#include "simulator/inc/Condition.h"
#include "simulator/inc/Operation.h"
#include "simulator/inc/Condition.h"

#define arr_size(array) (sizeof(array)/sizeof(*array))

using namespace std;

Operation operations[] = {
    Operation(Operation::LEFT),
    Operation(Operation::RIGHT),
    Operation(Operation::UP),
    Operation(Operation::DOWN),
    Operation(Operation::WAIT),
    Operation(Operation::ABORT),
};

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
        game.print_game_states();
        for (int i=0; i<arr_size(operations); i++) {
            Game next_game = game;
            next_game.move(operations[i]);

            Condition::ConditionType type = next_game.get_game_state()->get_condition().get_type();
            if (type==Condition::ABORTING || type==Condition::LOSING) {
                continue;
            } else if (type==Condition::WINNING) {
                goto END_GAME;
            }

            string field_str = next_game.get_field()->get_string();
            long field_hash = str_hash(field_str);

            if (hashes.find(field_hash)!=hashes.end()) continue;
            hashes.insert(field_hash);

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

