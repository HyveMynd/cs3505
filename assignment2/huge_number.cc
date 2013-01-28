#include "huge_number.h"

huge_number::huge_number()
{
    *this->num = "0";
}

huge_number::huge_number(const std::string s)
{
    *this->num = s;
}

huge_number::huge_number(const huge_number & other):
    num(other.num){}

huge_number::~huge_number()
{
    delete num;
}

std::string huge_number::get_value () const
{
    return *this->num;
}

huge_number & huge_number::operator= (const huge_number &rhs)
{
    this->num = rhs.num;
    return *this;
}

const huge_number huge_number::operator+ (const huge_number & rhs) const
{
    huge_number result = *this;
    result += rhs;
    return result;
}

const huge_number huge_number::operator- (const huge_number & rhs) const
{
    huge_number result = *this;
    result -= rhs;
    return result;
}

const huge_number huge_number::operator* (const huge_number & rhs) const
{
    huge_number result = *this;
    result *= rhs;
    return result;
}

const huge_number huge_number::operator/ (const huge_number & rhs) const
{
    huge_number result = *this;
    result /= rhs;
    return result;
}

const huge_number huge_number::operator% (const huge_number & rhs) const
{
    huge_number result = *this;
    result %= rhs;
    return result;
}

huge_number & huge_number::operator+= (const huge_number & rhs)
{
    std::string a = *this->num;
    std::string b = rhs.get_value();
    *this->num = add(a,b);
    return *this;
}

huge_number & huge_number::operator-= (const huge_number & rhs)
{
    std::string a = *this->num;
    std::string b = rhs.get_value();
    *this->num = subtract(a,b);
    return *this;
}

huge_number & huge_number::operator*= (const huge_number & rhs)
{
    std::string a = *this->num;
    std::string b = rhs.get_value();
    *this->num = multiply(a,b);
    return *this;
}

huge_number & huge_number::operator/= (const huge_number & rhs)
{
    std::string a = *this->num;
    std::string b = rhs.get_value();
    *this->num = divide(a,b);
    return *this;
}

huge_number & huge_number::operator%= (const huge_number & rhs)
{
    std::string a = *this->num;
    std::string b = rhs.get_value();
    *this->num = mod(a,b);
    return *this;
}


/*
 * Determine if the first string number is larger than the second
 * string number.
 */
bool is_bigger (std::string a, std::string b)
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

std::string add(std::string a, std::string b)
{
    // Build up a string object to contain the result.
    
    std::string result = "";
    
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

std::string multiply (std::string a, std::string b)
{
    std::string result = "0";
    
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

std::string subtract (std::string a, std::string b)
{
    std::string result = "";
    
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

std::string divide (std::string a, std::string b)
{
    std::ostringstream convert;
    std::string result = "";
    
    if (is_bigger(b,a))
        return "0";
    int next_digit = b.length();
    //perform long division
    std::string numerator = a.substr(0,next_digit);
    std::string denominator = b;
    
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
                std::string product = multiply(denominator, convert.str());
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

std::string mod (std::string a, std::string b)
{
    std::string result = "";
    if(is_bigger(a,b))
    {
        //find quotient and multply by divisor.
        //The difference of the product and dividend is the modulus
        std::string quotient = divide(a,b);
        std::string product = multiply(quotient,b);
        result = subtract(a, product);
    }
    else
    {
        //for fractions of a number
        result = a;
    }
    
    return result;
}

