package thread;

public class MesaMonitor {

    static int count = 0;

    public static void main(String[] args) {


        new Thread(() -> {
            for (int i = 0; i < 10; i++) {
                try {
                    Thread.sleep(10);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                count++;
                System.out.println("produce:" + count);
                synchronized (String.class) {
                    Test.class.notifyAll();
                    System.out.println("after notify");
                    try {
                        Thread.sleep(5000);
                        System.out.println("sleep(5000)");
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        }).start();


        new Thread(() -> {
            for (int i = 0; i < 10; i++) {
                try {
                    Thread.sleep(10);
                    if (count <= 0) {
                        synchronized (String.class) {
                            Test.class.wait();
                            System.out.println("after wait1");
                            System.out.println("after wait2");
                            System.out.println("after wait3");
                        }
                    }
                    count--;
                    System.out.println("----consume:" + count);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }

            }
        }).start();
    }


}
