package thread;

/**
 * Thread join 方法, 挂起线程，直至 join 方法对应的线程执行完毕，才轮到当前线程继续执行.
 * @author chiclaim
 */
public class ThreadJoin {

    public static void main(String[]args){

        Thread thread1 = new Thread(){
            @Override
            public void run() {
                super.run();
                for(int i=0;i<10;i++) {
                    System.out.println("thread1-"+i);
                    try {
                        Thread.sleep(1000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        };
        thread1.start();


        Thread thread2 = new Thread(){
            @Override
            public void run() {
                super.run();
                System.out.println("thread2 start run");
                try {
                    thread1.join();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                System.out.println("thread2 end");
            }
        };
        thread2.start();

    }

}
