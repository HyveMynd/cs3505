/* A 'utah set' is defined as a set of strings stored
 * in a hashtable that uses chaining to resolve collisions.
 *
 * Peter Jensen
 * January 17, 2013
 */

#include <iostream>
#include <string>
#include "utah_set.h"
#include "node.h"

namespace cs3505
{
  /*******************************************************
   * utah_set member function definitions
   ***************************************************** */

  
  /** Constructor:  The parameter indicates the
    *   size of the hashtable that should be used
    *   to keep this set.
    */
  utah_set::utah_set(int capacity)
  {
    // Do not change or remove the following line.
    //   It must execute for our auditing to be correct.

    utah_set::constructor_calls++;

    // Normal constructor tasks below.
    
    this->capacity = capacity;
    this->count = 0;
    this->table = new node*[capacity];  // Create table

    // Make sure the table is clear.  (Not normally cleared on new.)
    
    for (int i = 0; i < capacity; i++)
      table[i] = NULL;
  }

  
  /** Copy constructor:  Initialize this set
    *   to contain exactly the same elements as
    *   another set.
    */
  utah_set::utah_set(const utah_set & other)
  {
    // Do not change or remove the following line.
    //   It must execute for our auditing to be correct.

    utah_set::constructor_calls++;

    // Normal constructor tasks below.

    // Initialize this object to appear cleaned.
    
    this->capacity = 0;
    this->count = 0;
    this->table = NULL;

    // Use the overloaded assignment operator to do the work
    //   of copying the parameter's elements into this object.
    
    *this = other;
  }

  
  /** Destructor:  release any memory allocated
    *   for this object.
    */
  utah_set::~utah_set()
  {
    // Do not change or remove the following line.
    //   It must execute for our auditing to be correct.

    utah_set::destructor_calls++;

    // Normal destructor tasks below.
    
    clean();  // This does all the work.
  }

  
  /** Adds the specified element to this set.  If the element
    *   is already in this set, no action is taken.
    */
  void utah_set::add (std::string element)
  {
    // Locate the table entry that would contain it.
    
    int index = hash(element);
    
    // Each table entry is the head of a linked list.
    //   Follow it, looking for the element.  Also,
    //   keep track of the last node visited.

    node *current = table[index], *last = NULL;
    
    while (current != NULL)
    {
      if (current->element == element)  // Does a char-by-char comparison
	return;  // Found it - do nothing.
      last = current;           // Keep track of current as last visited node
      current = current->next;  // Advance to next node
    }

    // Element does not exist in the set.  Create a
    //   node object to contain it.  (New returns
    //   a pointer to it.)
    
    current = new node(element);

    // Add the node to our linked list.  Either
    //   add it to the end of the existing list,
    //   or start a new list.

    if (last == NULL)  // No existing list
      table[index] = current;  // The node becomes the head of a list
    else
      last->next = current;  // Add to end of existing list.

    // Keep track of the number of elements successfully added.
    
    count++;
  }

  
  /** Removes the specified element from this set.  If the
    *   element is not in the set, no action is taken.
    */
  void utah_set::remove (std::string element)
  {
    // Requirement:  When an element is removed, its
    //   enclosing node must be unlinked from that
    //   linked list, and then the node must be deleted
    //   to free up its memory.  The linked list and/or
    //   table must be appropriately updated.
      
      //find the element in the array
      int index = hash(element);
      
      node *current = table[index];
      node *prev = table[index]; //store previous node
      
      //follow the chain to the element
      while(current != NULL)
      {
          //check if the element is not in the chain
          if(!contains(element))
              return; //element does not exist
          
          //found the node
          if (current->element == element)
          {
              //if the addresses are the same, it is the first node in the chain
              if(prev == current)
              {
                  //the header node will need to be the next in the list
                  table[index] = current->next;
                  current->next = NULL; //remove 'next' pointer
                  delete current; //delete the node
                  count--;
                  return;
              }
              
              //assign the 'next' of the previous node to the currents 'next' node
              //this circumvents the current node
              prev->next = current->next;
              
              //remove the current 'next' pointer
              current->next = NULL;
              delete current; //delete the node
              count--;
              return;
          }
          //else the current node is not the one we are looking for, move pointers
          prev = current;
          current = current->next;
      }

    // (Don't forget to decrement count if an element is removed.)
  }

  
  /** Returns true if the specified element in in this set,
    *   false otherwise.
    */
  bool utah_set::contains (std::string element) const
  {
    // Locate the table entry that would contain it.
    
    int index = hash(element);

    // Each table entry is the head of a linked list.
    //   Follow it, looking for the element.

    node *current = table[index];  // Get the head of the list

    while (current != NULL)
    {
      if (current->element == element)  // Does a char-by-char comparison
          return true;  // Found it.
      
      current = current->next;  // Advance to next node
    }
    
    return false;  // Did not find it.
  }

  
  /** Returns a count of the number of elements
    *   in this set.
    */
  int utah_set::size () const
  {
    return count;
  }

  
  /*** Assignment operator ***/
  
  /** This function overloads the assignment operator.  It
    *   clears out this set, builds an empty table, and copies
    *   the entries from the right hand side (rhs) set into
    *   this set.
    */
  const utah_set & utah_set::operator= (const utah_set & rhs)
  {
    // If we are assigning this object to this object,
    //   do nothing.

    if (this == &rhs)  // Compare addresses (not object contents)
      return *this;  // Do nothing if identical

    // Wipe away anything that is stored in this object.
    
    clean();
    
    // Create a new set (new table) and populate it with the entries
    //   from the set in rhs.  Use the capacity from rhs.  Hint:
    //   see the first constructor above (but you cannot call it).
    
    // Requirement:  Do not permanently point to arrays or nodes in rhs.  
    //   When rhs is destroyed, it will delete its array and nodes, 
    //   and we cannot count on their existence.  Instead, you will
    //   create a new array for this object, traverse rhs,
    //   and add one entry to this set for every entry in rhs.

      //make new table
      this->capacity = rhs.capacity;
      this->count = 0;
      this->table = new node*[capacity];
      
      //initialize the table to null
      for (int i = 0; i < capacity; i++)
          table[i] = NULL;
      
      //loop through rhs to copy nodes into 'this'
      for (int i = 0; i < capacity; i++)
      {
          //only stop to copy non-empty cells
          if (rhs.table[i] != NULL)
          {
              node *current = rhs.table[i];

              //copy element over to this table
              std::string ele = current->element;
              add(ele);
              current = current->next; //move to next in chain
              
              //loop through the chain if there is one
              while (current != NULL)
              {
                  ele = current->element;
                  add(ele);
                  current = current->next; //move to next in chain
              }
          }
      }

    // Done with assignment.

    return *this;
  }


  /*** Private helper functions ***/
  
  /** Computes a table index for a given string.
    *   If two strings have the same contents, their
    *   hash code (table index) will be identical.
    * The hash code is guaranteed to be in the
    *   range [0..capacity).
    */  
  int utah_set::hash (std::string s) const
  {
    // A well-known algorithm for computing string hash codes.
    // Students should not change this algorithm in any way.
    
    long long hash = 0;
    for (int i = 0; i < s.length(); i++)
      hash = ((hash * 1117) + s[i]) % capacity;

    return static_cast<int>(hash);
  }


  /** Releases any memory that was allocated by
    *   this object.  This effectively destroys the
    *   set, so it should only be called if this object
    *   is destructing, or is being assigned.
    */
  void utah_set::clean ()
  {
    // If the object is already clean, do nothing.
    //   (Our representation for a clean object is that
    //   the table pointer is NULL).
    
    if (table == NULL)  
      return;

    // Delete all the nodes in the table.

    for (int i = 0; i < capacity; i++)
    {
      // Each entry in the table is the head of a linked list.
      // Follow the head to each node and delete the nodes.

      node *current = table[i];

      while (current != NULL)
      {
	// Keep a copy of the next pointer.

	node *temp_next = current->next;
	
	// Delete the node.  All its storage should be
	//   considered illegal.  (Afterwards, we cannot access
	//   ANYTHING inside of it, not even .next)

	delete current;

	// Advance to the next node.

	current = temp_next;	
      }      
    }

    // The nodes are all deleted.  Just delete the table.

    delete [] table;  // Notice the syntax for deleting an array.
    
    // We're done freeing up memory, but we should set
    //   our pointer to the array to NULL to indicate to
    //   ourself that it has been deleted.  (This also prevents
    //   us from accidentally using it.)

    table = NULL;

    // Done cleaning up.
  }
    
    /** This function populates an array of strings with elements from the set.
     * The caller passes an array (by pointer) and a count 'n' to the function.
     * The function copies n unique elements from the set into
     * the array.  (Order does not matter.)  If 'n' is smaller
     * than the number of elements in the set, only 'n' elements are
     * copied into the array in positions [0..n-1].  If 'n' is larger than the number
     * of elements in the set, all the elements in the set are
     * copied into the first positions of the array, and excess positions
     * in the array remain unchanged.
     *
     * It is assumed that the array reference is valid and that n is non-negative.
     */
    void utah_set::get_elements(std::string *array, int n) const
    {
        int num_elements = n;
        int arr_pos = 0;
        
        //loop through the table and retrieve 'n' elements. 
        for (int i = 0; i < capacity; i++)
        {
            //found a non empty cell, copy
            if (table[i] != NULL)
            {
                node *current = table[i];
                
                //place the string in the array
                std::string ele = current->element;
                array[arr_pos] = ele;
                arr_pos++; //item was added to array, move to next position
                num_elements--; //item was added, subtract from count
                
                //check if we have copied 'n' elements
                if (num_elements==0)
                    return; //done
                
                current = current->next; //move down chain if possible
                
                //travese chain and copy elements
                while (current != NULL)
                {
                    //copy the string
                    ele = current->element;
                    array[arr_pos] = ele;
                    arr_pos++;
                    num_elements--;
                    current = current->next; //move to next node
                    
                    //check if we have copied 'n' elements
                    if (num_elements==0)
                        return; //done
                }
            }
        }
    }


  
  /*******************************************************
   * utah_set static definitions:
   *
   *     These are for debugging purposes only.  They help
   * the programmer audit their memory usage.
   *
   *     Do not change anything below this point.
   ***************************************************** */

  // We haven't covered static class members.  Since static
  // variables are not in objects, we need to define storage
  // for them.  These variables are -here-, not in any object.
  // (This is the ONLY copy of these variables that will exist.)
  
  long long utah_set::constructor_calls = 0;
  long long utah_set::destructor_calls = 0;


  /** Returns the number of times any utah_set
    *   constructor has been called.
    */
  long long utah_set::constructor_count ()
  {
    return utah_set::constructor_calls;
  }

  
  /** Returns the number of times the utah_set
    *   destructor has been called.
    */
  long long utah_set::destructor_count ()
  {
    return utah_set::destructor_calls;
  }

}
