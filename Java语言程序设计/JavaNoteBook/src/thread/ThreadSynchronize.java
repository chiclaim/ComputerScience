package thread;


import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.atomic.AtomicInteger;

/**
 * 线程同步（生产者和消费者）
 * @author chiclaim
 */
public class ThreadSynchronize {

    private static final int LIMIT = 15;
    private static final int MAX = 10;

    private static final AtomicInteger count = new AtomicInteger();

    private static final ConcurrentLinkedQueue<Integer> container = new ConcurrentLinkedQueue<>();

    public static void main(String[] args) {

        for (int i = 0; i < 3; i++) {
            new Thread() {
                @Override
                public void run() {
                    super.run();
                    try {
                        consumer();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }.start();

        }

        for (int i = 0; i < 3; i++) {
            new Thread() {
                @Override
                public void run() {
                    super.run();
                    try {
                        producer();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }.start();
        }
    }


    /**
     * 生产者
     */
    private static void producer() throws InterruptedException {
        for (int i = 0; i < LIMIT; i++) {
            Thread.sleep(2000);
            synchronized (container) {
                while (container.size() >= MAX) {
                    //System.out.println("----容器已满...");
                    container.wait();
                }
                count.incrementAndGet();
                container.add(count.get());
                System.out.println("producer:" + count.get() + " 容器元素个数：" + container.size());
                container.notifyAll();
            }
        }
    }


    /**
     * 消费者
     */
    private static void consumer() throws InterruptedException {
        for (int i = 0; i < LIMIT; i++) {
            Thread.sleep(1000);
            synchronized (container) {
                while (container.isEmpty()) {
                    //System.out.println("---等待生产...");
                    container.wait();
                }
                System.out.println("consumer:" + container.poll() + " 容器元素个数：" + container.size());
                container.notifyAll();
            }
        }
    }


}
