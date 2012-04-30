import java.util.*;

class Point {
    public double x;
    public double y;

    public Point(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public Point add(Point other) {
        return new Point(this.x+other.x, this.y+other.y);
    }

    public Point sub(Point other) {
        return new Point(this.x-other.x, this.y-other.y);
    }

    public Point mul(double other) {
        return new Point(this.x*other, this.y*other);
    }

    public Point div(double other) {
        return new Point(this.x/other, this.y/other);
    }

    public double sqabs() {
        return x*x + y*y;
    }

    public double abs() {
        return Math.sqrt(sqabs());
    }

    public double dot(Point other) {
        return x*other.x + y*other.y;
    }

    public double cross(Point other) {
        return x*other.y - y*other.x;
    }

    public boolean isIncludedIn(Point p1, Point p2, Point p3) {
        double res1 = (this.sub(p1)).cross(p2.sub(p1));
        double res2 = (this.sub(p2)).cross(p3.sub(p2));
        double res3 = (this.sub(p3)).cross(p1.sub(p3));

        if ((res1<=0 && res2<=0 && res3<=0) || (res1>=0 && res2>=0 && res3>=0)) {
            return true;
        }
        return false;
    }

    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("[x=").append(x);
        sb.append(",y=").append(y).append("]");
        return sb.toString();
    }

}


public class ProblemE {

    public static double EPS = 1e-9;

    private ArrayList<Point> points;
    private ArrayList<Point> pins;

    public ProblemE(ArrayList<Point> points, ArrayList<Point> pins) {
        this.points = points;
        this.pins = pins;
    }
    
    public double getRoute() {
        double res = 0;

        int size = points.size();
        for (int i=1; i<size; i++) {
            Point p1 = points.get(i-1);
            Point p2 = points.get(i);
            res += p2.sub(p1).abs();
        }

        return res;
    }

    public double solve() {
        double route = getRoute();

        while (true) {

            int i = 0;
            while (i<points.size()-2) {
                Point p1 = points.get(i);
                Point p2 = points.get(i+1);
                Point p3 = points.get(i+2);


                // search a nearest pin in the triangle
                Point pin = null;
                double minTheta = Math.PI;
                for (Point p : pins) {
                    if (!p.isIncludedIn(p1, p2, p3)) continue;

                    Point vec1 = p2.sub(p1);
                    Point vec2 = p.sub(p1);
                    double cosVal = vec1.dot(vec2) / Math.sqrt(vec1.sqabs()*vec2.sqabs());
                    if (cosVal>1) cosVal = 1;

                    double theta = Math.acos(cosVal);
                    if (theta<minTheta) {
                        minTheta = theta;
                        pin = p;
                    }
                }

                if (pin==null) {
                    points.remove(p2);
                } else {
                    Point vec = p2.sub(pin);
                    //               pin + vec / vec.abs * EPS
                    Point newPoint = pin.add(vec.div(vec.abs()).mul(EPS));
                    points.add(i+1, newPoint);
                    i += 1;
                }

            }

            double newRoute = getRoute();
            if (Math.abs(route-newRoute)<EPS) {
                route = newRoute;
                break;
            } else {
                route = newRoute;
            }

        }

        return route;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        while (true) {
            ArrayList<Point> points = new ArrayList<Point>();
            ArrayList<Point> pins = new ArrayList<Point>();

            int m = sc.nextInt(), n = sc.nextInt();

            if (m==0 && n==0) break;

            for (int i=0; i<m; i++) {
                int x = sc.nextInt(), y = sc.nextInt();
                points.add(new Point(x,y));
            }

            for (int i=0; i<n; i++) {
                int x = sc.nextInt(), y = sc.nextInt();
                pins.add(new Point(x,y));
            }

            double ans = new ProblemE(points, pins).solve();

            System.out.println(ans);
        }

    }

}
