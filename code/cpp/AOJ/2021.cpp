#include <cstdio>
#include <climits>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define INF (INT_MAX - 1)
#define MAX_M 101

//#define DEBUG
#ifdef DEBUG
#define Dprintf(fmt,...) fprintf(stderr,fmt,__VA_ARGS__)
#else
#define Dprintf(fmt,...)
#endif

int N, M, L, K, A, H;

struct qdata {
	int dist;
	int layer;
	int id;
	int tfg; // total_freezing_time
	inline bool operator > (const qdata &q) const {
		return dist > q.dist;
	}
};

struct edge {
	int to;
	int cost;
};

struct vertex {
	vector<edge> edges;
	bool freezer;
	int total_freezing_time[MAX_M];

	// for dijkstra
	bool fixed[MAX_M];
	int distance[MAX_M];

	// constructor
	vertex(bool fr = false): freezer(fr) {
		for (int i = 0; i < MAX_M; i++) {
			fixed[i] = false;
			distance[i] = INF;
			total_freezing_time[i] = 0;
		}
	}
};
vector<vertex> vertices;

void dijkstra(int start) {
	priority_queue< qdata, vector<qdata>, greater<qdata> > queue;

	vertices.at(start).distance[M] = 0;
	qdata q; q.dist = 0; q.layer = M; q.id = start; q.tfg = 0;
	queue.push(q);
	while (!queue.empty()) {
		qdata top = queue.top(); queue.pop();
		vertex* v = &vertices.at(top.id);
		int l = top.layer;

		if (v->fixed[l]) continue; // already fixed
		v->distance[l] = top.dist;
		v->fixed[l] = true;
		v->total_freezing_time[l] = top.tfg;
		Dprintf("[Layer %d] Distance to Node:%d is found to be %d (total freeze: %d)\n", l, top.id, v->distance[l], top.tfg);
		for (int i = 0; i < v->edges.size(); i++) {
			edge e = v->edges.at(i);
			int freezingtime = (v->freezer)? M - l : 0;
			int next_layer = l + freezingtime - e.cost;
			Dprintf("\t(freezing:%d)--%d-->[Layer %d](%d)\n", freezingtime, e.cost, next_layer, e.to);
			if (next_layer < 0) continue;
			if (v->distance[l] + freezingtime + e.cost < vertices.at(e.to).distance[next_layer]) { // new shorter path found
				Dprintf("\t\tis shorter than current %d\n", vertices.at(e.to).distance[next_layer]);
				qdata q; q.dist = v->distance[l] + freezingtime + e.cost; q.layer = next_layer; q.id = e.to; q.tfg = top.tfg + freezingtime;
				queue.push(q);
			}
		}
	}
}

int main(int argc, char const* argv[])
{

	while (cin >> N >> M >> L >> K >> A >> H, N || M || L || K || A || H) {
		for (int i = 0; i < N; i++) {
			vertex v; vertices.push_back(v);
		}
		for (int i = 0; i < L; i++) {
			int l; cin >> l;
			vertices.at(l).freezer = true;
		}
		for (int i = 0; i < K; i++) {
			int X, Y, T; cin >> X >> Y >> T;
			for (int i = 0; i < 2; i++) {
				edge e;
				e.to = Y; e.cost = T;
				vertices.at(X).edges.push_back(e);
				swap(X, Y);
			}
		}
		Dprintf("Start from %d, Goal is %d, Limit is %d\n", A, H, M);
		dijkstra(A);
		int ans = INF;
		for (int i = 0; i < M; i++) {
			int over_freezing;
			if (i > 0) {
				if (vertices.at(H).total_freezing_time[i] >= i) {
					over_freezing = i;
				} else {
					over_freezing = vertices.at(H).total_freezing_time[i];
				}
			} else {
				over_freezing = 0;
			}
			if (vertices.at(H).distance[i] - over_freezing < ans) {
				ans = vertices.at(H).distance[i] - over_freezing;
			}
		}
		if (ans == INF) {
			cout << "Help!" << endl;
		} else {
			cout << ans << endl;
		}

		for (int i = 0; i < N; i++) {
			vertices.at(i).edges.clear();
		}
		vertices.clear();
	}
	return 0;
}
