package thread;

/**
 * 线程状态：
 * <ul>
 *  <li>NEW</li>
 *  <li>RUNNABLE</li>
 *  <li>WAITING</li>
 *  <li>TIMED_WAITING</li>
 *  <li>BLOCKED</li>
 *  <li>TERMINATED</li>
 *</ul>
 *
 * @see java.lang.Thread.State
 * @author chiclaim
 */
public class ThreadState {

    static final Object monitorObj = new Object();
    static boolean canGo = true;

    public static void main(String[] args) throws InterruptedException{
        testBlocked();
        System.out.println("\n=============divider=============\n");
        testStates();
    }

    public static void testStates() throws InterruptedException {

        Thread myThread = new Thread(){
            @Override
            public void run() {
                super.run();
                try {
                    Thread.sleep(100);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }

                synchronized (monitorObj) {
                    System.out.println("------myThread get monitorObj");
                    try {
                        System.out.println("------before monitorObj wait");
                        while(canGo) {
                            monitorObj.wait();
                        }
                        System.out.println("------after monitorObj wait");
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        };
        //NEW
        System.out.println(myThread.getState().name());

        myThread.start();
        //RUNNABLE
        System.out.println(myThread.getState().name());

        Thread.sleep(10);
        //TIMED_WAITING
        System.out.println(myThread.getState().name());

        Thread.sleep(100);
        //WAITING
        System.out.println(myThread.getState().name());

        synchronized (monitorObj) {
            System.out.println("----main thread get monitorObj");
            canGo = false;
            monitorObj.notify();
        }
        // BLOCKED
        System.out.println(myThread.getState().name());

        // BLOCKED/RUNNABLE
        System.out.println(myThread.getState().name());

        Thread.sleep(10);
        // TERMINATED
        System.out.println(myThread.getState().name());

    }


    public static void testBlocked() throws InterruptedException {

        Thread thread = new Thread(){
            @Override
            public void run() {
                super.run();
                synchronized (ThreadInterrupt.class){
                    try {
                        Thread.sleep(1000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        };

        synchronized (ThreadInterrupt.class){
            thread.start();
            Thread.sleep(10);
            System.out.println(thread.getState().name());
        }

    }


}



