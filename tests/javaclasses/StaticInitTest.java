public class StaticInitTest {
    static int counter = 0;

    static {
        counter = 42;
    }

    public static int getCounter() {
        return counter;
    }

    public static void main(String[] args) {
        System.out.println(getCounter());
    }
}
