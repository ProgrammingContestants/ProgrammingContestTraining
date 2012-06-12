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
      // �R�X�g�����������i�����j�Ƀ\�[�g���邽�߂̔�r���Z�q
      // Quiz: �R�X�g���傫�����Ƀ\�[�g���邽�߂ɂ́H
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
    // ���B�ς݂��ǂ����`�F�b�N���邽�߂̃e�[�u��
    boolean[][] reached = new boolean[towns.length][4 * 7];
    // ������Ԃ̐���
    PriorityQueue<State> que = new PriorityQueue<State>();
    que.add(new State(start, 0));

    while (!que.isEmpty()) {
      State state = que.poll();
      // �S�[������
      if (state.town == goal) {
        if (state.cost % 4 == 0 || state.cost % 7 == 0) {
          return state.cost;
        }
        // ���ʃ��[���u��x���ɒ������炻��ȏ�ړ����邱�Ƃ͂ł��Ȃ��v
        continue;
      }
      // ���B�ς݃`�F�b�N
      if (reached[state.town][state.cost % 28]) {
        continue;
      }
      reached[state.town][state.cost % 28] = true;
      // ���݂̏�Ԃ��瓞�B�\�ȏ�Ԃ��L���[�ɒǉ�
      for (Road road : towns[state.town].roads) {
        que.add(new State(road.to, state.cost + road.cost));
      }
    }

    // �O�ׂ̈ɔ񌟍���O�itry�ň͂ޕK�v�̂Ȃ���O�j�𓊂��Ă���
    throw new RuntimeException();
  }
}
