#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <locale>
#include <queue>


using namespace std;

CommandType commands[] = { LEFT, RIGHT, UP, DOWN, WAIT, ABORT, DUMMY };

long str_hash(const string& str);

int main(int argc, char **argv)/*{{{*/
{
    Game game; // get map data from standard input
    queue<Game> game_queue;
    game_queue.push(game);
    while (!game_queue.empty()) {
        Game g = game_queue.front(); game_queue.pop();
        g.move();
    }

    return 0;
}/*}}}*/

static locale loc;
static const collate<char>& coll = use_facet<collate<char> >(loc);
long str_hash(const string& str) {
    return coll.hash(str.data(), str.data()+str.length());
}
