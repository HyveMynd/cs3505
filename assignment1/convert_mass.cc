#include <iostream>
#include <cmath>

using namespace std;

double roundNumber (double w)
{
  w *= 100;
  w = floor(w + 0.5);
  w /= 100;
  return w;
}

int main (int argc, char* argv[])
{
  cout << "Enter a weight in pounds: ";

  double weight;

  if (!(cin >> weight) || weight <= 0){ //keyboard input here
    cout << "You did not enter a valid weight. Program will exit." << endl;
    return 0;
    }  

  weight *= 0.45;//convert to kg

  cout << "Your weight in kilograms is " << roundNumber(weight) << ".\n";
  
  return 0;
}
