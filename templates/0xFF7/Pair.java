
/**
 * The immutable pair
 */
public final class Pair<T, U> {
    public final T _1;
    public final U _2;

    public Pair(T __1, U __2) { _1 = __1; _2 = __2; }

    public Pair<T, U> _1(T _1) { return of(_1, _2); }
    public Pair<T, U> _2(U _2) { return of(_1, _2); }
    public String toString() { return "(" + _1 + "," + _2 + ")"; }

    /**
     * <p>
     * Overriding the {@code hashCode} method is STRONGLY recommended
     * when you override the {@code equals} method.
     * </p>
     */
    public int hashCode() {
        return _1.hashCode() ^ _2.hashCode();
    }

    public boolean eq(Pair<?, ?> p) {
        return _1.equals(p._1) && _2.equals(p._2);
    }

    public boolean equals(Object o) {
        return o == this
            || o instanceof Pair<?, ?> && eq((Pair<?, ?>)o);
    }

    /**
     * <p>This method helps the type inferrence.</p>
     * <p>Two expressions below are equivalent:</p>
     * {@code Pair<String, Integer> p = new Pair<String, Integer>("", 0);}
     * {@code Pair<String, Integer> p = Pair.of("", 0);}
     */
    public static <T, U> Pair<T, U> of(T _1, U _2) {
        return new Pair<T, U>(_1, _2);
    }

    public static void main(String[] args) {
        Pair<String, Integer> p = Pair.of("test", 10);
        System.out.println(p._1 + p._2);
        System.out.println(p);
        p = p._1("TEST")._2(500);
        System.out.println(p);
    }
}
