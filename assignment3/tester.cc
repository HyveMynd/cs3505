/*
 * This is a tester similar to the tester written in class.  It reads
 * words from a text file, then adds the words to two sets: A built-in
 * set class, and our utah_set class.  After reading the file, it
 * prints out all the words stored in the STL set object.  At the end
 * of the test, it prints out the sizes of both sets to see that they
 * are the same.
 *
 * After the test completes, I make sure the local variabls are properly
 * cleaned up.
 *
 * If the comments wrap lines, widen your emacs window.
 *
 * Peter Jensen, Andres Monroy
 * January 17, 2013
 */

#include <iostream>
#include <fstream>
#include <set>
#include <iterator>
#include "utah_set.h"
#include "node.h"

using namespace std;

void testADD();
void testREMOVE();
void testCONTAINS();
void testGET_ELEMENT();
void testOP();

int main ()
{
  // Open up another block.  This way, when the block ends,
  // variables local to the block will be destroyed, but main
  // will still be running.  (Did you know that you can open
  // up a block at any time to control local variable scope and
  // lifetime?)
  
  {
    // Create the two sets.  Declaring the local variables constructs the objects.
  
    set<string>      stl_set_of_words;  // The built-in set class - no constructor parameters.

    cs3505::utah_set our_set_of_words(1000);  // Our set class, with a hashtable of 1000 slots.
  
    // Open the file stream for reading.  (We'll be able to use it just like
    //   the keyboard stream 'cin'.)

    ifstream in("Yankee.txt");

    // Loop for reading the file.  Note that it is controlled
    //   from within the loop (see the 'break').
    
    while (true)
    {
      // Read a word (don't worry about punctuation)
      
      string word;
      in >> word;

      // If the read failed, we're probably at end of file
      //   (or else the disk went bad).  Exit the loop.
      
      if (in.fail())
	break;

      // Word successfully read.  Add it to both sets.
      
      stl_set_of_words.insert(word);
      our_set_of_words.add(word);
    }

    // Close the file.

    in.close();

    // Print out the words found in the STL set.  I do this to show
    //   students how to get at the entries in an STL object.  For
    //   more examples, look up 'STL iterator examples'.
    // Notice that the iterator object 'it' acts like a pointer, but
    //   it is not a pointer.  (Bad, bad, bad design choice, but not mine!)
    // Feel free to comment this out.

    // Print out the number of words found in each set.

    cout << endl;
    cout << "STL set contains " << stl_set_of_words.size() << " unique words.\n";
    cout << "Our set contains " << our_set_of_words.size() << " unique words.\n";
    cout << endl;

    // Done.  Notice that this code block ends below.  Any local
    // variables declared within this block will be automatically
    // destroyed.  Local objects will have their destructors
    // called.

  }

  // Now that the objects have been destroyed, I will simply call my auditing
  // code to print out how many times constructors have been called, and
  // how many times destructors have been called.  They should exactly match.
  // If not, we have a memory problem.

  cout << "Class cs3505::utah_set:" << endl;
  cout << "    Objects created:  " << cs3505::utah_set::constructor_count() << endl;
  cout << "    Objects deleted:  " << cs3505::utah_set::destructor_count() << endl;
  cout << endl;

  cout << "Class cs3505::node:" << endl;
  cout << "    Objects created:  " << cs3505::node::constructor_count() << endl;
  cout << "    Objects deleted:  " << cs3505::node::destructor_count() << endl;
  cout << endl;

  // Now we're really done.  End main.
    
    
    //start unit tests
    testADD();
    testREMOVE();
    testCONTAINS();
    testGET_ELEMENT();
    testOP();
  
  return 0;
}




void testADD()
{
    //create table and string to add
    cs3505::utah_set table;
    bool passAll = true;
    int addCount = 0;
    
    //check for string added to the array
    //add the string
    table.add("hi");
    addCount++;
    
    //test for the string to be in the table
    //the constructor defaults to 10 so we may search through the array of 10
    if (!table.contains("hi")){
        cout << "ADD(string) FAILED. String is not being added to the pointer array." << endl;
        passAll = false;
    }
    
    //check for proper chaining in the hashset
    //hash to same slot in table
    table.add("ih");
    addCount++;
    bool passed = table.contains("hi") && table.contains("ih");
    if (!passed){
        cout << "ADD(string) FAILED. Add is not properly chaining." << endl;
        passAll = false;
    }
    
    //test the size is being updated
    if (table.size() != addCount){
        cout << "ADD(string) FAILED. Size is not being updated." << endl;
        passAll = false;
    }
    
    if (passAll)
        cout << "ADD(string) PASSED!" << endl;
}

void testREMOVE()
{
    cs3505::utah_set table;
    bool passAll = true;
    
    //add a string and check for a removal from the array
    table.add("hi");
    table.remove("hi");
    if (table.contains("hi")) {
        cout << "REMOVE(string) FAILED. String in not being removed from the array" << endl;
        passAll = false;
    }
    
    //check for removal in a chain
    table.add("hi");
    table.add("ih");
    table.remove("hi");
    table.remove("ih");
    if (table.contains("hi") || table.contains("ih")){
        cout << "REMOVE(string) FAILED. String in not being removed rom the chain" << endl;
        passAll = false;
    }
    
    //check the cout is being updated properly
    table.add("hi");
    table.remove("hi");
    if (table.size() != 0){
        cout << "REMOVE(string) FAILED. Size is not being updated when removing from the array" << endl;
        passAll = false;
    }
    table.add("hi");
    table.add("ih");
    table.remove("hi");
    table.remove("ih");
    if (table.size() != 0){
        cout << "REMOVE(string) FAILED. Size is not being updated when removing from the chain" << endl;
        passAll = false;
    }
    
    if (passAll)
        cout << "REMOVE(string) PASSED!" << endl;
}

void testCONTAINS()
{
    //make table and add a few elements
    cs3505::utah_set table;
    bool passAll = true;
    table.add("hi");
    
    //test while adding
    if(!table.contains("hi")){
        cout << "CONTAINS(string) FAILED. String was not found after being added." << endl;
        passAll = false;
    }
    
    //test contains while adding in chains
    table.add("ih");
    if(!table.contains("ih")){
        cout << "CONTAINS(string) FAILED. String was not found after being added in a chain." << endl;
        passAll = false;
    }
    
    //test while removing
    table.remove("hi");
    if(table.contains("hi")){
        cout << "CONTAINS(string) FAILED. String was found after removing from array." << endl;
        passAll = false;
    }
    
    //test while removing from a chain
    //test contains while adding in chains
    table.add("hi");
    table.add("ih");
    table.remove("hi");
    table.remove("ih");
    if(table.contains("ih")){
        cout << "CONTAINS(string) FAILED. String was found after being removed in a chain." << endl;
        passAll = false;
    }
        
    if(passAll)
        cout << "CONTAINS(string) PASSED!" << endl;
}

void testGET_ELEMENT()
{
    //make table and string array to test with
    cs3505::utah_set table;
    string array[5];
    bool passAll = true;
    
    //make array null
    for (int i = 0; i < 5; i++)
        array[i] = "\0";
        
    //add a few items to the table and check if the array has those items
    table.add("a");
    table.add("b");
    table.add("c");
    table.add("d");
    table.add("e");
    table.add("f");
    table.add("g");
    table.add("h");
    table.add("i");
    table.add("j");
    
    //first get when n < capacity
    table.get_elements(array, 5);
    
    //there should not be any null items
    for (int i = 0; i < 5; i++)
        if(array[i] == "\0"){
            cout << "GET_ELEMENTS(string) FAILED. Array is not complete when 'n' is less than the number of items in the hashset" << endl;
            passAll = false;
            break;
        }
    
    //test when n > capacity
    string array2[15];
    //make array null
    for (int i = 0; i < 15; i++)
        array2[i] = "\0";
    
    //first get when n < capacity
    table.get_elements(array2, 15);
    
    //first 10 should not be null
    for (int i = 0; i < 10; i++)
        if(array2[i] == "\0"){
            cout << "GET_ELEMENTS(string) FAILED. Array is not complete when 'n' is greater than the number of items in the hashset" << endl;
            passAll = false;
            break;
        }
    //next 5 should be null
    for (int i = 9; i < 5; i++)
        if(!(array2[i] == "\0")){
            cout << "GET_ELEMENTS(string) FAILED. Array is not complete when 'n' is greater than the number of items in the hashset" << endl;
            passAll = false;
            break;
        }
    
    if(passAll)
        cout << "GET_ELEMENTS(string) PASSED!" << endl;
}

void testOP ()
{
    //make table and string array to test with
    cs3505::utah_set table;
    cs3505::utah_set test;

    //add some items to one table, should appear in the other
    table.add("a");
    table.add("b");
    table.add("c");
    table.add("d");
    table.add("e");
    
    test = table;
    
    if(test.contains("a") && test.contains("b") && test.contains("c") && test.contains("d") && test.contains("e")){
        cout << "OPERATOR=(utah_set) PASSED!" << endl;
    }
    else
        cout << "OPERATOR=(utah_set) FAILED. Not all elements were present in the left hand side." << endl;
}