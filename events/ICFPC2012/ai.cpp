#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <locale>
#include <queue>
#include <deque>
#include <set>
#include <csignal>
#include <ctime>
#include "simulator/inc/Game.h"
#include "simulator/inc/Condition.h"
#include "simulator/inc/Operation.h"
#include "simulator/inc/Robot.h"

#define arr_size(array) (sizeof(array)/sizeof(*array))

using namespace std;

static Operation operations[] = {
    Operation(Operation::LEFT),
    Operation(Operation::RIGHT),
    Operation(Operation::UP),
    Operation(Operation::DOWN),
    Operation(Operation::WAIT),
};
static Operation op_abort = Operation(Operation::ABORT);

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
    Robot robot = field.get_robot();
    int rx = robot.get_x(), ry = robot.get_y();
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

    srand(time(NULL));

    deque<Game> *game_queue = new deque<Game>();
    deque<Game> *next_queue = new deque<Game>();
    set<long> hashes;
    {
        Game game(cin); // get map data from standard input
        game_queue->push_back(game);
    }
    int depth = 0;
    while (!game_queue->empty()) {
        depth++;
        cerr << "depth:" << depth << ", state:" << game_queue->size() << ", hashes:" << hashes.size() << endl;
        while (!game_queue->empty()) {
            Game game = game_queue->front(); game_queue->pop_front();


            if (game.get_game_state().get_remain()==0) {
                // search path for goal

                deque<Game> inner_game_queue;
                inner_game_queue.push_back(game);

                while (!inner_game_queue.empty()) {
                    Game g = inner_game_queue.front(); inner_game_queue.pop_front();

                    Condition::ConditionType type = g.get_game_state().get_condition().get_type();
                    if (type==Condition::WINNING) {
                        update_score(g);
                        cerr << "WINNING score:" << max_score;
                        cerr << ", depth:" << g.get_field().get_steps();
                        cerr << ", collected:" << g.get_game_state().get_collected() << endl;
                        show_field(g.get_field());
                        goto END_SEARCH;
                    }

                    for (int i=0; i<arr_size(operations); i++) {
                        Game next_game = g;
                        next_game.move(operations[i]);
                        update_score(next_game);

                        Condition::ConditionType type = next_game.get_game_state().get_condition().get_type();
                        if (type==Condition::LOSING) continue;
                        if (type==Condition::WINNING) {
                            cerr << "WINNING score:" << max_score << endl;
                            show_field(next_game.get_field());
                            goto END_SEARCH;
                        }

                        long field_hash = str_hash(next_game.get_field().get_string());
                        if (hashes.find(field_hash)!=hashes.end()) continue;
                        hashes.insert(field_hash);

                        inner_game_queue.push_back(next_game);
                    }
                }
            } else {

                for (int i=0; i<arr_size(operations); i++) {
                    Game next_game = game;
                    next_game.move(operations[i]);
                    update_score(next_game);

                    Condition::ConditionType type = next_game.get_game_state().get_condition().get_type();
                    if (type==Condition::LOSING) continue;
                    if (type==Condition::WINNING) {
                        cerr << "WINNING score:" << max_score << endl;
                        show_field(next_game.get_field());
                        goto END_SEARCH;
                    }

                    long field_hash = str_hash(next_game.get_field().get_string());
                    if (hashes.find(field_hash)!=hashes.end()) continue;
                    hashes.insert(field_hash);

                    next_queue->push_back(next_game);
                }

                {
                    Game next_game = game;
                    next_game.move(op_abort);
                    update_score(next_game);
                }
            }

        }
        deque<Game> *tmp = next_queue;
        next_queue = game_queue;
        game_queue = tmp;
    }

    END_SEARCH:

    cout << max_operations << endl;

    return 0;
}/*}}}*/

static locale loc;
static const collate<char>& coll = use_facet<collate<char> >(loc);
long str_hash(const string& str) {
    return coll.hash(str.data(), str.data()+str.length());
}

