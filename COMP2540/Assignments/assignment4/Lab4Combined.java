/*
Lab 4
COMP-2540
By: Lucas Sarweh
ID: 110042658 
*/

import java.util.Random;

public class Lab4Combined {
    // Number generator
    private static Random gen = new Random();
    public static void main(String[] args){
        // Single queue for all tellers
        CQueue<Integer> myqueue = new CQueue<>(Integer.class, 100);
        // Queue for teller 1
        CQueue<Integer> q1 = new CQueue<>(Integer.class, 100);
        // Queue for teller 2
        CQueue<Integer> q2 = new CQueue<>(Integer.class, 100);
        // Queue for teller 3
        CQueue<Integer> q3 = new CQueue<>(Integer.class, 100);
        // Total runtime
        int currentTime = 0;
        // Average time storage
        int averageTime = 0;
        int averageTime2 = 0;
        // Number of total customers
        int numCust = 0;
        // New customer timer
        int customer = 0;
        // Time until teller is available
        int teller1 = 0;
        int teller2 = 0;
        int teller3 = 0;
        // Flag to close doors after 100 customers
        boolean closed = false;
        
        while(!closed || q1.size() != 0 || q2.size() != 0 || q3.size() != 0 || myqueue.size() != 0){ // Each loop represents 1 count
            // When a customer enters get a new random for the next customer
            if(!closed && customer <= 0){
                // Add that customer to the queue with current time
                myqueue.enqueue(currentTime);
                // Add that customer to the shortest queue
                if(q1.size() < q2.size()){
                    if(q1.size() < q3.size()){
                        q1.enqueue(currentTime);
                    }else{
                        q3.enqueue(currentTime);
                    }
                }else if(q2.size() < q3.size()){
                    q2.enqueue(currentTime);
                }else{
                    q3.enqueue(currentTime);
                }

                // Add to number of customers
                ++numCust;
                // Set customer limit
                if(numCust >= 100){
                    closed = true;
                }
                // Generate random time a customer arrives
                customer = randNum();
            }
            // When a teller is available
            if(teller1 <= 0){
                Integer temp = myqueue.dequeue();
                // Make sure there is a customer
                if(temp != null){
                    // Teller accepts new customer
                    averageTime2 += (currentTime - temp);
                    // Make timer for how long it took to serve the customer
                }

                temp = q1.dequeue();
                // Make sure there is a customer
                if(temp != null){
                    // Teller accepts new customer
                    averageTime += (currentTime - temp);
                    // Make timer for how long it took to serve the customer
                }
                teller1 = randNum();
            }
            if(teller2 <= 0){
                Integer temp = myqueue.dequeue();
                // Make sure there is a customer
                if(temp != null){
                    // Teller accepts new customer
                    averageTime2 += (currentTime - temp);
                    // Make timer for how long it took to serve the customer
                }

                temp = q2.dequeue();
                // Make sure there is a customer
                if(temp != null){
                    // Teller accepts new customer
                    averageTime += (currentTime - temp);
                    // Make timer for how long it took to serve the customer
                }
                teller1 = randNum();
            }
            if(teller3 <= 0){
                Integer temp = myqueue.dequeue();
                // Make sure there is a customer
                if(temp != null){
                    // Teller accepts new customer
                    averageTime2 += (currentTime - temp);
                    // Make timer for how long it took to serve the customer
                }

                temp = q3.dequeue();
                // Make sure there is a customer
                if(temp != null){
                    // Teller accepts new customer
                    averageTime += (currentTime - temp);
                    // Make timer for how long it took to serve the customer
                }
                teller1 = randNum();
            }
            // Update timers
            ++currentTime;
            --customer;
            --teller1;
            --teller2;
            --teller3;
        }
        // Calculate average
        averageTime = averageTime / numCust;
        averageTime2 = averageTime2 / numCust;
        // Print average
        System.out.println("Average wait time 1 queue: " + averageTime2);
        System.out.println("Average wait time 3 queues: " + averageTime);
    }

    /**
     * Helper function always returns a number between 1 and 5
     * @return An int between 1 and 5
     */
    private static int randNum(){
        return gen.nextInt(5) + 1;
    }
}
