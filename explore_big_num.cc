/* Test code for manipulating strings  - assumes non-negative strings */

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// Forward declarations

string add (string, string);
string multiply (string a, string b);
bool is_bigger (string a, string b);
string subtract (string a, string b);
string divide (string a, string b);
string mod (string a, string b);

/*
 * Main - the application entry point
 *
 * This application was constructed just to test algorithms for
 * adding numbers represented as strings.  Note:  This is not robust.
 * Care should be taken to ensure that the strings only have numeric
 * digits within them.
 *
 */
int main ()
{
  string s = "12341278756784325896754323";
  string t =   "21";

  cout << s << endl;
  cout << t << endl;
  cout << endl;

  string u;

  u = add(s, t);

  cout << u << endl;
  cout << endl;
  
  u = multiply(s, t);

  cout << u << endl;
  cout << endl;
    
    //check bigger
    if(is_bigger(s,t))
        cout << "true, s is bigger" << "\n\n";
    else
        cout << "false, s is smaller or equal" << "\n\n";
    
    u = subtract(s,t);
    
    cout << u << "\n\n";
    
    u = divide (s,t);
    
    cout << "division: " << u << endl;
    
    u = mod(s,t);
    
    cout << "mod: " << u << endl;

  
  return 0;  // I forgot this in my other examples.
             // Returning '0' signals 'no error' to the shell.
}

/*
 * Adds two numbers stored in strings, building a string result.
 */

string add (string a, string b)
{
  // Build up a string object to contain the result.
  
  string result = "";

  // Work right to left.  (Most significant digits to least)
  
  int a_pos = a.length() - 1;
  int b_pos = b.length() - 1;
  
  int carry = 0;

  // Loop, adding columns, until no more columns and no carry.
  
  while (a_pos >= 0 || b_pos >= 0 || carry > 0)
    {
      // Get next digit from each string, or 0 if no more.
    
      int a_digit = a_pos >= 0 ? a[a_pos--]-'0' : 0;
      int b_digit = b_pos >= 0 ? b[b_pos--]-'0' : 0;

      /// Calculate the digit for this column and the carry out
    
      int sum = a_digit + b_digit + carry;
      carry = sum / 10;
      sum = sum % 10 + '0';

      // Put this column's digit at the start of the result string.
    
      result.insert(0, 1, static_cast<char>(sum));
    }

  // Strip any leading 0's  (shouldn't be any, but you'll use this elsewhere.)

  while (result[0] == '0')
    result.erase(0, 1);

  // If the string is empty, it is a 0.
  
  if (result.length() == 0)
    result = "0";

  // Return the result.
  
  return result;
}

/*
 * Multiplies two numbers stored in strings, building a string result.
 */

string multiply (string a, string b)
{
  string result = "0";

  int b_pos = b.length() - 1;

  // Loop once for each digit in b.
  while (b_pos >= 0)
    {
      int b_digit = b[b_pos--]-'0';  // Get next digit from b.

      // Add a to the result the appropriate number of times.
      
      for (int i = 0; i < b_digit; i++)
	{
	  result = add(result, a);
	  // cout << "  " << result << endl;  // Debug only
	}

      // Multiply a by 10.
      
      a.append("0");

      // Debug only.  (Useful to have string numbers for this!)      
      // cout << a << endl;
    }

  return result;
}

/*
 * Subtract two numbers represented as strings
 */
string subtract (string a, string b)
{
    string result = "";
    
    //check a negative result
    if (!is_bigger(a,b))
    {
        result = "0";
    }
    else
    {
        bool carry = false;
        
        //retrieve largest array position. least significant digit
        int a_pos = a.length()-1;
        int b_pos = b.length()-1;
        
        //work from right to left. "a" is the larger number
        while (a_pos >= 0)
        {
            //get next digit from the string
            int a_digit = a_pos >= 0 ? a[a_pos--]-'0' : 0;
            int b_digit = b_pos >= 0 ? b[b_pos--]-'0' : 0;
                        
            //subtract 1 for a previous carry
            if (carry)
            {
                a_digit -= 1;
                carry = false;
            }
            //carry a number if needed
            if (a_digit < b_digit)
            {
                carry = true;
                a_digit += 10;
            }
            
            //find the difference
            int difference = a_digit - b_digit;
            difference += '0';
            
            //insert the difference into first spot in result
            result.insert(0, 1, static_cast<char>(difference));
            
        }
        // Strip any leading 0's
        while (result[0] == '0')
            result.erase(0, 1);
    }
    return result;
}

string divide (string a, string b)
{
    ostringstream convert;
    string result = "";
    
    if (is_bigger(b,a))
        return "0";
    int next_digit = b.length();
    //perform long division
    string numerator = a.substr(0,next_digit);
    string denominator = b;
    
    while (next_digit <= a.length())
    {
        //add digit if numerator is smaller
        if (is_bigger(denominator, numerator))
        {
            result.append("0");
            numerator.append(a.substr(next_digit,1));
            next_digit++;
        }
        //loop to find a product that exceeds numerator
        else
        {
            for (int i = 1; i < 20; i++)
            {
                convert.str("");
                convert << i;
                string product = multiply(denominator, convert.str());
                //found i that exceeded product, append previous 'i'
                if (is_bigger(product, numerator))
                {
                    convert.str("");
                    i--;
                    convert << i;
                    result.append(convert.str());
                    //subtract to find remainder
                    numerator = subtract(numerator, multiply(denominator,convert.str()));
                    //drop down next number
                    numerator.append(a.substr(next_digit,1));
                    next_digit++;
                    break;
                }
            }
        }
    }
    while (result[0] == '0')
        result.erase(0, 1);
    return result;
}

/*
 *
 */
string mod (string a, string b)
{
    string result = "";
    if(is_bigger(a,b))
    {
        //find quotient and multply by divisor.
        //The difference of the product and dividend is the modulus
        string quotient = divide(a,b);
        string product = multiply(quotient,b);
        result = subtract(a, product);
    }
    else
    {
        //for fractions of a number
        result = a;
    }
    
    return result;
}

/*
 * Determine if the first string number is larger than the second 
 * string number.
 */
bool is_bigger(string a, string b)
{
    // Strip any leading 0's  (shouldn't be any, but you'll use this elsewhere.)
    while (a[0] == '0')
        a.erase(0, 1);
    while (b[0] == '0')
        b.erase(0, 1);
    
    //save lengths
    int aL = a.length();
    int bL = b.length();
    
    if (aL > bL)
    {
        return true;
    }
    else if (aL < bL)
    {
        return false;
    }
    // lenght must be equal therefore check the most significant
    // digits
    else
    {
        for (int i = 0; i < aL; i++)
        {
            //extract most significant digits
            char a_char = a[i];
            char b_char = b[i];
            
            //convert from ASCII
            int a_int = a_char - 48;
            int b_int = b_char - 48;
            
            //check for the larger of the two numbers
            if (a_int > b_int)
            {
                return true;
            }
            else if (a_int < b_int)
            {
                return false;
            }
        }
        //reached the end of the two numbers.
        //numbers are equal return false
        return false;
    }
}

// Other really useful functions

//is_bigger (a, b)
//subtract (a, b)
//divide (a, b)
//mod (a, b)

