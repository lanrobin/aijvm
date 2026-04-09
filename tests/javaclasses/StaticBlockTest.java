public class StaticBlockTest {
    static int x;
    static int y;
    static String msg;

    static {
        x = 100;
        y = 200;
        msg = "initialized";
    }

    public static void main(String[] args) {
        int sum = x + y;
        System.out.println("x = " + x);
        System.out.println("y = " + y);
        System.out.println("sum = " + sum);
        System.out.println("msg = " + msg);

        if (sum == 300) {
            System.out.println("StaticBlockTest PASSED");
        } else {
            System.out.println("StaticBlockTest FAILED");
        }
    }
}
