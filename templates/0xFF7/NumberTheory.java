
public class NumberTheory
{
    public static boolean[] eratos(int limit)
    {
        boolean[] np = new boolean[limit + 1];

        for (int i = 2; i * i <= limit; i++)
        {
            if (!np[i])
            {
                for (int j = 2 * i; j <= limit; j += i)
                {
                    np[j] = true;
                }
            }
        }
        return np;
    }

    public static int gcd(int x, int y)
    {
        while (y > 0)
        {
            int r = x % y;
            x = y;
            y = r;
        }
        return x;
    }

    public static void main(String[] args)
    {
        final int LIM = 100;
        boolean[] np = eratos(LIM);
        for(int _=1;++_<=LIM;)if(!np[_])System.out.println(_);

        System.out.println("GCD(12707, 12319) = " + gcd(12707, 12319));
    }
}
