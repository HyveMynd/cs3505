#include <iostream>
#include <fstream>
#include <set>
#include <iterator>
#include "utah_set.h"
#include "node.h"

using namespace std;

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
}

void testADD ()
{
    
}

void testRemove ()
{
    
}

void testContains()
{
    
}

void testGET_ELEMENT ()
{
    
}

