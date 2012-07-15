#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <locale>
#include <queue>
#include <set>
#include <csignal>
#include "simulator/inc/Game.h"
#include "simulator/inc/Condition.h"
#include "simulator/inc/Operation.h"

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


static int max_score = 0;
static string max_operations = "";
void update_score(Game &game) {
    int new_score = game.get_game_state().get_score();
    if (max_score<new_score) {
        max_score = new_score;
        max_operations = game.get_operations();
    }
}


void sig_handle(int sig) {
    if (sig==2) {
        cout << max_operations << endl;
        cout.flush();
        exit(0);
    }
}


void show_field(Field &field) {
    int width = field.get_width();
    int height = field.get_height();
    for (int i=height; i>=1 ; --i) {
        for (int j=1; j<=width; ++j) {
            cerr << field.get_cell(j, i).get_char();
        }
        cerr << endl;
    }
    cerr << endl;
}


int main(int argc, char **argv)/*{{{*/
{
    if (SIG_ERR == signal(SIGINT, sig_handle)) {
        cout << "failed to set signal handler.n" << endl;
        exit(1);
    }


    queue<Game> game_queue;
    set<long> hashes;
    {
        Game game(cin); // get map data from standard input
        game_queue.push(game);
    }
    while (!game_queue.empty()) {
        Game game = game_queue.front(); game_queue.pop();


        Condition::ConditionType type = game.get_game_state().get_condition().get_type();
        if (type==Condition::ABORTING || type==Condition::LOSING) {
            if (max_score<game.get_game_state().get_score()) {
                update_score(game);
                cerr << "ABORTING score:" << max_score;
                cerr << ", collected:" << game.get_game_state().get_collected() << endl;
                show_field(game.get_field());
            }
            continue;
        } else if (type==Condition::WINNING) {
            update_score(game);
            cerr << "WINNING score:" << max_score;
            cerr << ", collected:" << game.get_game_state().get_collected() << endl;
            show_field(game.get_field());
            break;
        }

        string field_str = game.get_field().get_string();
        long field_hash = str_hash(field_str);

        if (hashes.find(field_hash)!=hashes.end()) continue;
        hashes.insert(field_hash);

        update_score(game);


        for (int i=0; i<arr_size(operations); i++) {
            Game next_game = game;
            next_game.move(operations[i]);

            game_queue.push(next_game);
        }
    }

    cout << max_operations << endl;

    return 0;
}/*}}}*/

static locale loc;
static const collate<char>& coll = use_facet<collate<char> >(loc);
long str_hash(const string& str) {
    return coll.hash(str.data(), str.data()+str.length());
}

