#include <iostream>
#include <cmath>
#include <sstream>

using namespace std;

/*
 * Simple helper method to determine if the number is prime
 */
bool isPrime (int);

int main (int argc, char* argv[])
{
  int prime;
  stringstream convert(argv[1]);//convert the text into an int

  //test if the string can be represented as an int
  if(!(convert >> prime)){
    cout << "Not a valid number. Program will exit" << endl;
    return 0;
  }

  //test for a prime number
  if (isPrime(prime)){
    cout << "Prime\n" << endl; 
  }
  else{
    cout << "Composite\n" << endl;
  }
  return 0;
}
bool isPrime (int number)
{
  if (number == 1 || number == 0 || number < 0){
    return false;
  }
  for (int i = 2; i <= number-1; i++){
    if (number % i == 0){
      return false;
    }
  }
  return true;
}

