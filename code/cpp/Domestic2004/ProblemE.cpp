#include <iostream>
#include <iomanip>

#define for_(i,a,n)  for(int i=a;i<n;++i)
#define rep(i,n)     for_(i,0,n)

using namespace std;

struct cell
{
	int xl, xr, h;
	int val;
	cell *l, *r;

	cell(int xl, int xr, int h)
		: xl(xl), xr(xr), h(h), l(NULL), r(NULL)
	{
	}

	~cell()
	{
		delete l;
		delete r;
	}

	bool is_leaf() { return l == NULL && r == NULL; }
	int width() { return xr - xl; }
	int bottom_area() { return width() * 30; }

	int capacity() { return bottom_area() * h; }
	int sub_capacity() { return is_leaf() ? 0 : l->capacity() + r->capacity(); }
	int max_margin() { return capacity() - sub_capacity(); }
	int margin() { return max_margin() - val; }
	bool is_full() { return val == max_margin(); }

	int sub_value() { return is_leaf() ? 0 : l->value() + r->value(); }
	int value() { return val + sub_value(); }

	void part(int x, int h)
	{
		if (is_leaf())
		{
			l = new cell(xl, x, h);
			r = new cell(x, xr, h);
		}
		else if (x < l->xr)
		{
			l->part(x, h);
		}
		else if (r->xl < x)
		{
			r->part(x, h);
		}
	}

	void clear()
	{
		val = 0;
		if (!is_leaf())
		{
			l->clear();
			r->clear();
		}
	}

	int water(int x, int v)
	{
		if (!is_leaf())
		{
			if (x < l->xr)
			{
				v = l->water(x, v);
				if (v != 0) v = r->water(r->xl, v);
			}
			else if (r->xl < x)
			{
				v = r->water(x, v);
				if (v != 0) v = l->water(l->xr, v);
			}
		}

		int inc = min(v, margin());
		val += inc;
		return v - inc;
	}

	double water_height(int x)
	{
		if (is_leaf() || val > 0)
		{
			return (double)value() / bottom_area();
		}
		else if (x < l->xr)
		{
			return l->water_height(x);
		}
		else if (r->xl < x)
		{
			return r->water_height(x);
		}
		return -1;
	}
};

int main()
{
	int D;
	cin>>D;
	while(D--)
	{
		int N,M,L,div[51] = { 0 },flow[10][2];
		cin>>N;
		rep(i,N)
		{
			int x, h;
			cin>>x>>h;
			div[h] = x;
		}

		cell root(0, 100, 50);
		for (int h = 50; h > 0; --h)
			if (div[h] > 0) root.part(div[h], h);

		cin>>M;
		rep(i,M) cin>>flow[i][0]>>flow[i][1];

		cin>>L;
		rep(i,L)
		{
			int x, t;
			cin>>x>>t;
			root.clear();
			rep(j,M) root.water(flow[j][0], t * flow[j][1]);
			cout << fixed << setprecision(5) << root.water_height(x) << endl;
		}
	}
	return 0;
}
