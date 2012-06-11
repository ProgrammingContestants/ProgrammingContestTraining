#include <iostream>/*{{{*/
#include <vector>
#include <complex>
#include <climits>
#include <algorithm>
#include <set>

using namespace std;/*}}}*/

typedef unsigned long long u64;
typedef complex<int> point;

int   n;
point piece[36];
int pairs[36];
u64 joint[36];

set<u64> wrong;

/*
 * t: pieces used in A
 * w: pieces used in B
 */
bool solve( u64 t, u64 w )/*{{{*/
{
	if( wrong.find(t) != wrong.end() ) {
		return false;
	}

	if( (t|w) == (1ULL<<n)-1 ) { // all pieces were used
		return true;
	}

	for( int i = 0; i < n; ++i ) {
		u64 tm = 1ULL << i;        // new adding to A
		u64 wm = 1ULL << pairs[i]; // new adding to B (corresponds to tm)

		if( pairs[i] == -1 ||                           // no corresponding piece
				(t&tm) || (w&tm) || (t&wm) || (w&wm) || // already added
				!(joint[i]&t) ) {                       // piece[i] is not adjacent to A
			continue;
		}

		if( solve( t|tm, w|wm ) ) {
			return true;
		}
	}

	wrong.insert(t);
	return false;
}/*}}}*/

int main()/*{{{*/
{
	for( int w,h; cin>>w>>h, w|h; )	{
		int index[10][10];
		n = 0;
		// input/*{{{*/
		for( int y = 0; y < h; ++y ) {
			for( int x = 0; x < w; ++x ) {
				int r; cin >> r;

				if( r == 1 ) {
					index[y][x] = n;
					piece[n++] = point(x,y);
				} else {
					index[y][x] = -1;
				}
			}
		}/*}}}*/

		// joint check/*{{{*/
		for( int i = 0; i < n; ++i ) {
			point d(1,0);
			joint[i] = 0;

			for( int j = 0; j < n; ++j ) {
				for( int k = 0; k < 4; ++k, d *= point(0,1) ) {
					if( piece[i]+d == piece[j] ) {
						joint[i] |= 1ULL << j;
					}
				}
			}
		}/*}}}*/

		if( n&1 ) // NO if odd/*{{{*/
		{
			cout << "NO" << endl;
			continue;
		}/*}}}*/

		point base0 = piece[0];
		bool yes = false;
		for( int base_index = 1; base_index < n; ++base_index ) {
			point base1 = piece[base_index];
			point rotate = point(1,0);
			for( int rot = 0; rot < 4; ++rot, rotate *= point(0,1) ) {
				for( int mirror = 0; mirror <= 1; ++mirror ) {
					int rpairs[36];

					fill( rpairs, rpairs+n, -1 );
					fill( pairs , pairs +n, -1 );

					for( int i = 0; i < n; ++i ) {
						point t = piece[i] - base0;
						if( mirror ) {
							t.imag() = -t.imag();
						}
						t = t*rotate + base1; // base0 -> piece[i], base1 -> t

						if( t.real() < 0 || w <= t.real() ||
								t.imag() < 0 || h <= t.imag() ) {
							continue;
						}

						pairs[i] = index[t.imag()][t.real()];
						if( pairs[i] != -1 ) {
							rpairs[pairs[i]] = i;
						}
					}               

					int i;
					for( i = 0; i < n; ++i ) {
						    /* no chance of being gruent */  /* took same piece */
						if( rpairs[i] == -1 && pairs[i] == -1 || pairs[i] == i ) {
							break;
						}
					}

					wrong.clear();
					if( i == n && solve( 1ULL, 1ULL<<base_index ) ) {
						yes = true;
						goto quit;
					}
				}
			}
		}
quit:
		cout << ( yes ? "YES" : "NO" ) << endl;
	}
	return 0;
}/*}}}*/

// vim: foldmethod=marker 
