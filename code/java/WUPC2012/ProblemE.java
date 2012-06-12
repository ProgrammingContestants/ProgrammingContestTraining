package WUPC2012;

import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Scanner;

public class ProblemE {

  static class Town {
    public List<Road> roads;

    public Town() {
      roads = new ArrayList<Road>();
    }
  }

  static class Road {
    public int to;
    public int cost;

    public Road(int to, int cost) {
      super();
      this.to = to;
      this.cost = cost;
    }
  }

  static class State implements Comparable<State> {
    public int town;
    public int cost;

    public State(int iTown, int cost) {
      super();
      this.town = iTown;
      this.cost = cost;
    }

    @Override
    public int compareTo(State o) {
      // コストが小さい順（昇順）にソートするための比較演算子
      // Quiz: コストが大きい順にソートするためには？
      return cost - o.cost;
    }
  }

  public static void main(String[] args) {
    new ProblemE().solve(System.in);
  }

  private void solve(InputStream in) {
    Scanner sc = new Scanner(in);
    int nTowns = sc.nextInt();
    int nRoads = sc.nextInt();
    Town[] towns = new Town[nTowns];
    for (int i = 0; i < towns.length; i++) {
      towns[i] = new Town();
    }
    for (int i = 0; i < nRoads; i++) {
      int from = sc.nextInt();
      int to = sc.nextInt();
      int cost = sc.nextInt();
      towns[from].roads.add(new Road(to, cost));
      towns[to].roads.add(new Road(from, cost));
    }
    System.out.println(dijkstra(0, nTowns - 1, towns));
  }

  private int dijkstra(int start, int goal, Town[] towns) {
    // 到達済みかどうかチェックするためのテーブル
    boolean[][] reached = new boolean[towns.length][4 * 7];
    // 初期状態の生成
    PriorityQueue<State> que = new PriorityQueue<State>();
    que.add(new State(start, 0));

    while (!que.isEmpty()) {
      State state = que.poll();
      // ゴール判定
      if (state.town == goal) {
        if (state.cost % 4 == 0 || state.cost % 7 == 0) {
          return state.cost;
        }
        // 特別ルール「一度会場に着いたらそれ以上移動することはできない」
        continue;
      }
      // 到達済みチェック
      if (reached[state.town][state.cost % 28]) {
        continue;
      }
      reached[state.town][state.cost % 28] = true;
      // 現在の状態から到達可能な状態をキューに追加
      for (Road road : towns[state.town].roads) {
        que.add(new State(road.to, state.cost + road.cost));
      }
    }

    // 念の為に非検査例外（tryで囲む必要のない例外）を投げておく
    throw new RuntimeException();
  }
}
