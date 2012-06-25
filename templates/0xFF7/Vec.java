import java.util.*;
import java.math.*;

class Vec {
    public double x, y;
    public Vec(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public Vec add(Vec other)          { return new Vec(x+other.x, y+other.y); }
    public Vec sub(Vec other)          { return new Vec(x-other.x, y-other.y); }
    public Vec mul(double k)           { return new Vec(x*k, y*k); }
    public Vec div(double k)           { return new Vec(x*k, y*k); }
    public Vec mul(double a, double b) { return new Vec(x*a, y*b); }
    public Vec div(double a, double b) { return new Vec(x/a, y/b); }
    public Vec neg()                   { return mul(-1); }
    public Vec unit()                  { return div(len()); }
    public double dot(Vec other)       { return x*other.x + y*other.y; }
    public double cross(Vec other)     { return x*other.y - y*other.x; }
    public double len2()               { return dot(this); }
    public double len()                { return Math.sqrt(len2()); }
    public double arg()                { return Math.atan2(y, x); }
    public double dist(Vec other)      { return sub(other).len(); }
    public String toString()           { return String.format("(%f,%f)", x, y); }

    public boolean contained(List<Vec> points) {
        if (points.size()<3) throw new RuntimeException("Invalid Polygon");

        int size = points.size();
        boolean isLeft = points.get(0).sub(this).cross(points.get(size-1).sub(this)) < 0;
        for (int i=1; i<size; i++) {
            if (isLeft ^ (points.get(i).sub(this).cross(points.get(i-1).sub(this)) < 0)) {
                return false;
            }
        }
        return true;
    }
    public boolean contained(Vec[] points) {
        return contained(Arrays.asList(points));
    }
    @Override
    public boolean equals(Object other) {
        if (!(other instanceof Vec)) return false;
        Vec p = (Vec)other;
        if (Math.abs(x-p.x)<1e-9 && Math.abs(y-p.y)<1e-9) {
            return true;
        }
        return false;
    }

    public static Vec crossedVec(Vec a, Vec b, Vec c, Vec d) {
        double t = b.sub(a).cross(a.sub(d)) / b.sub(a).cross(c.sub(d));
        System.out.println(t);
        if (t<0 || 1<t) return null;
        return c.mul(t).add(d.mul(1-t));
    }


    public static void main(String[] args) {
    }


}
