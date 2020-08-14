import java.util.concurrent.*;

public class semaphore
{
	
	class begin {
		static int cntr = 0;
	}
	
	public static void main(String args[]) throws InterruptedException
	{
		Semaphore sem = new Semaphore(1);
		Mythread t1 = new Mythread(sem, "one");
		Mythread t2 = new Mythread(sem, "two");
		t1.start();
		t2.start();
		t1.join();
		t2.join();
		System.out.println("cntr: " +begin.cntr);
	}

	class OS extends Thread {
		Semaphore sem;
		String n;
		public OS(Semaphore sem, String n) {
			super(n);
			this.sem = sem;
			this.n = n;
		}
		@Override
		public void run() {
			if(this.getn().equals("one")) {
				sem.acquire();
				System.out.println("Permitted thread: "+n);
			
				for(int i = 0; i<3; i++) {
					start.count++;
					Thread.sleep(6);
				}
			sem.release();
			System.out.println("Released thread: "+n);
			}
			else {
				sem.acquire();
				System.out.println("Permitted thread: "+n);
				for(int i = 0; i<3; i++) {
                                	start.count--;
                                	Thread.sleep(6);
                        	}
               		sem.release();
			System.out.println("Released thread: " +n);
			}
	}	
}
}	
