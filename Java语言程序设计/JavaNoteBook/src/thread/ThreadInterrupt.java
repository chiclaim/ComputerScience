package thread;

/**
 * 关于线程的状态
 *
 * <ul>
 *  <li>void interrupt：</li>
 *  将线程的中断状态设置为 true
 *  <li>static boolean interrupted：</li>
 *  返回线程的中断状态，如果为 true 清除中断状态，
 *  所以一个线程的中断状态为 true，连续连用两次该方法，第一次返回 true，第二次返回 false
 *  <li>boolean isInterrupted：</li>
 *  返回线程的中断状态是否为 true
 * </ul>
 *
 * <b>需要注意的是，如果抛出过 InterruptedException，那么线程的中断状态也会被清除</b>
 *
 * @author chiclaim
 */
public class ThreadInterrupt {


    public static void main(String[] args) throws InterruptedException {
        Thread myThread = new Thread() {
            @Override
            public void run() {
                super.run();

                // 需要注意的是，如果抛出过 InterruptedException，那么线程的中断状态也会被清除
                // 所以，如果下面的代码打开注释，程序不会中断，因为后续的 Thread.interrupted() 一直返回 false
                /*try {
                    Thread.sleep(10);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }*/

                System.out.println("thread start to run...");
                int i = 10000;
                while (true) {
                    i++;
                    boolean isInterrupted = Thread.interrupted();
                    System.out.println(i+" - "+isInterrupted);
                    if(isInterrupted){
                        System.out.println("call Thread.interrupted() again:"+Thread.interrupted());
                        break;
                    }
                }
            }
        };

        myThread.start();
        //Thread.sleep(10);
        // 中断线程, 仅仅是改变线程的中断状态位, 不会停止线程
        myThread.interrupt();
        // thread.isInterrupted 返回线程的中断状态是否为 true
        System.out.println("myThread.isInterrupted():" + myThread.isInterrupted());
    }

}



