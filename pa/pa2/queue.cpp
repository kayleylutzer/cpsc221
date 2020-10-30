/**
 * @file queue.cpp
 * Implementation of the Queue class.
 *
 * Modify and turn in this file for the PA!
 *
 */
 
 /*
 * stack_1 will be the "input" stack
 * stack_2 will be the "output" stack
 */

/**
 * Adds the parameter object to the back of the Queue.
 *
 * @param newItem object to be added to the Queue.
 */
template <class T> void Queue<T>::enq(T const &newItem)
{
  /**
   * @todo Your code here!
   */
   
   stack_1.push(newItem);
   num_items++;
  
   
}

/**
 * Removes the object at the front of the Queue, and returns it to the
 * caller.
 *
 * @return The object that used to be at the front of the Queue.
 */
template <class T> T Queue<T>::deq()
{
  /**
   * @todo Your code here! You will need to replace the following line.
   */

    if(stack_2.isEmpty()){
        while(!stack_1.isEmpty())
            stack_2.push(stack_1.pop());
	}

        T temp = null;
        if(!stack_2.isEmpty()) {
            temp = stack_2.pop();
            size--;
        }

        return temp;
}

/**
 * Finds the object at the front of the Queue, and returns it to the
 * caller. Unlike deq(), this operation does not alter the queue.
 *
 * @return The item at the front of the queue.
 */
template <class T> T Queue<T>::peek()
{
  /**
   * @todo Your code here! You will need to replace the following line.
   */
  return stack_2.peek();
}

/**
 * Determines if the Queue is empty.
 *
 * @return bool which is true if the Queue is empty, false otherwise.
 */
template <class T> bool Queue<T>::empty() const
{
  /**
   * @todo Your code here! You will need to replace the following line.
   */
  return stack_1.size(); == 0;
}
