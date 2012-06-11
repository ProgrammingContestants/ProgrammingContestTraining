// -*- coding: utf-8 -*-

import java.util.Scanner;

public class ProblemE
{
  private static class Cell
  {
    public int xl, xr, h;
    public int value;
    public Cell l, r;

    public Cell(int xl_, int xr_, int h_)
    {
      xl = xl_;
      xr = xr_;
      h = h_;
    }

    public void part(int x, int h)
    {
      if (isLeaf())
      {
        l = new Cell(xl, x, h);
        r = new Cell(x, xr, h);
      }
      else if (x < l.xr)
      {
        l.part(x, h);
      }
      else if (r.xl < x)
      {
        r.part(x, h);
      }
    }

    public boolean isLeaf() { return l == null && r == null; }

    public int bottomArea() { return (xr - xl) * 30; }

    public boolean isFull() { return value == maxCapacity(); }

    public void fill() { value = maxCapacity(); }

    public int maxCapacity() { return h * bottomArea(); }

    public void clear()
    {
      value = 0;
      if (!isLeaf())
      {
        l.clear();
        r.clear();
      }
    }

    // 位置xに体積vの水を注ぐ
    public int water(int x, int v)
    {
      int cap = maxCapacity() - value;
      if (cap <= v) // この区画が満杯になる場合
      {
        if (!isLeaf())
        {
          l.fill();
          r.fill();
        }
        fill();
        return v - cap;
      }

      // 以下はこの区画内で水を使い切る場合

      if (isLeaf() || (l.isFull() && r.isFull())) // この区画が末端 or 左右が満杯の場合
      {
        value += v;
      }
      else // 分割されている場合
      {
        int rem = 0;
        if (x < l.xr) // 左に注ぐ
        {
          rem = l.water(x, v);
          if (l.isFull() && rem != 0)
          {
            rem = r.water(r.xl, rem);
          }
        }
        else if (r.xl < x) // 右に注ぐ
        {
          rem = r.water(x, v);
          if (r.isFull() && rem != 0)
          {
            rem = l.water(l.xr, rem);
          }
        }
        value = l.value + r.value + rem;
      }
      return 0;
    }

    public double getWaterHeight(int x)
    {
      if (isLeaf() || (l.isFull() && r.isFull())) // 末端 or 左右が満杯
      {
        return (double)value / bottomArea();
      }
      else if (x < l.xr)
      {
        return l.getWaterHeight(x);
      }
      else if (r.xl < x)
      {
        return r.getWaterHeight(x);
      }
      return -1;
    }
  }

  public static void main(String[] args)
  {
    Scanner sc = new Scanner(System.in);
    int D = sc.nextInt();
    for (;D-->0;)
    {
      int N = sc.nextInt();

      int[] div = new int[50 + 1];
      for (int i = 0; i < N; i++)
      {
        int x = sc.nextInt(), h = sc.nextInt();
        div[h] = x;
      }

      Cell root = new Cell(0, 100, 50);
      for (int h = 50; h > 0; h--)
      {
        if (div[h] > 0) root.part(div[h], h);
      }

      int M = sc.nextInt();
      int[][] flow = new int[M][2];
      for (int i = 0; i < M; i++)
      {
        int x = sc.nextInt();
        int a = sc.nextInt();
        flow[i][0] = x;
        flow[i][1] = a;
      }

      int L = sc.nextInt();
      for (int i = 0; i < L; i++)
      {
        root.clear();
        int x = sc.nextInt();
        int t = sc.nextInt();
        for (int j = 0; j < M; j++)
        {
          root.water(flow[j][0], t * flow[j][1]);
        }
        System.out.printf("%.5f\n", root.getWaterHeight(x));
      }
    }
  }
}
/*
2
5
15 40
35 20
50 45
70 30
80 10
3
20 3
60 2
65 2
6
40 4100
25 7500
10 18000
90 7000
25 15000
25 22000
5
15 40
35 20
50 45
70 30
80 10
2
60 4
75 1
3
60 6000
75 6000
85 6000
*/
