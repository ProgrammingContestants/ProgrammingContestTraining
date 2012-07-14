#include <iostream>
#include <vector>

#define EACH(c,it) for(__typeof((c).begin()) it=(c).begin(); it!=(c).end(); ++it)

using namespace std;

void input_field ()/*{{{*/
{
    int width = 0;
    int height = 0;
    vector<string> field;
    string row;
    while (getline(cin, row)) {
        width = max(width, (int)row.length());
        field.push_back(row);
    }
    EACH (field, row) {
        int len = (*row).length();
        for (int i = len; i < width; ++i) {
            (*row) += " ";
        }
    }
    height = field.size();
}/*}}}*/


int main(int argc, char **argv)
{
    input_field();
    cout << "A" << endl;

    return 0;
}
