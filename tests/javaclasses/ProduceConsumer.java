public class ProduceConsumer {
    // A simple fixed-size array acts as our bounded buffer to avoid complex java.util dependencies
    private final int[] buffer;
    private final int capacity;
    private int count = 0;
    private int putIndex = 0;
    private int takeIndex = 0;

    public ProduceConsumer(int capacity) {
        this.capacity = capacity;
        this.buffer = new int[capacity];
    }

    // The 'synchronized' keyword will compile to ACC_SYNCHRONIZED on the method, 
    // or you can use a synchronized(this) block which compiles to monitorenter/monitorexit.
    public synchronized void produce(int value) throws InterruptedException {
        // Wait until there is space in the buffer
        while (count == capacity) {
            wait(); 
        }
        
        buffer[putIndex] = value;
        putIndex = (putIndex + 1) % capacity;
        count++;
        
        System.out.println("Produced: " + value);
        
        // Notify the consumer that an item is available
        notifyAll(); 
    }

    public synchronized int consume() throws InterruptedException {
        // Wait until there is an item in the buffer
        while (count == 0) {
            wait();
        }
        
        int value = buffer[takeIndex];
        takeIndex = (takeIndex + 1) % capacity;
        count--;
        
        System.out.println("Consumed: " + value);
        
        // Notify the producer that space is available
        notifyAll(); 
        return value;
    }

    public static void main(String[] args) {
        // We must avoid string concatenation with variables if we haven't 
        // bypassed invokedynamic yet, so using static strings or basic print/println.
        System.out.println("Starting Producer-Consumer Test...");
        
        final ProduceConsumer pc = new ProduceConsumer(5);

        // Explicit Runnable to avoid Lambdas (invokedynamic)
        Thread producer = new Thread(new Runnable() {
            public void run() {
                try {
                    for (int i = 1; i <= 10; i++) {
                        pc.produce(i);
                        Thread.sleep(100); // Simulate work
                    }
                } catch (InterruptedException e) {
                    System.out.println("Producer Interrupted");
                }
            }
        });

        Thread consumer = new Thread(new Runnable() {
            public void run() {
                try {
                    for (int i = 1; i <= 10; i++) {
                        pc.consume();
                        Thread.sleep(200); // Simulate slower consumption
                    }
                } catch (InterruptedException e) {
                    System.out.println("Consumer Interrupted");
                }
            }
        });

        producer.start();
        consumer.start();

        try {
            // Main thread waits for child threads to finish
            producer.join();
            consumer.join();
        } catch (InterruptedException e) {
            System.out.println("Main Thread Interrupted");
        }
        
        System.out.println("Test Finished Successfully.");
    }
}