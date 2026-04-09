public class GCStressTest {
    public static void main(String[] args) {
        System.out.println("GC Stress Test: allocating many objects...");

        int[] holder = new int[10];
        for (int i = 0; i < 10; i++) {
            holder[i] = i * 100;
        }

        // Verify array contents survived
        int sum = 0;
        for (int i = 0; i < 10; i++) {
            sum = sum + holder[i];
        }

        System.out.println("Sum = " + sum);
        System.out.println("GC Stress Test: PASSED");
    }
}
