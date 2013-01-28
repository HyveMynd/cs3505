#ifndef HUGE_NUMBER_H
#define HUGE_NUMBER_H
#include <string>
#include <iostream>
#include <sstream>

/*
 * A class to handle arithmetic of very large numbers
 */
class huge_number
{
 public:
    huge_number ();
    huge_number (const huge_number & other);
    huge_number (const std::string);
    ~huge_number();
    std::string get_value() const;

  //binary operators
    const huge_number operator+ (const huge_number & rhs) const;
    const huge_number operator- (const huge_number & rhs) const;
    const huge_number operator* (const huge_number & rhs) const;
    const huge_number operator/ (const huge_number & rhs) const;
    const huge_number operator% (const huge_number & rhs) const;
  //assignment operators
    huge_number & operator+= (const huge_number & rhs);
    huge_number & operator-= (const huge_number & rhs);
    huge_number & operator*= (const huge_number & rhs);
    huge_number & operator/= (const huge_number & rhs);
    huge_number & operator%= (const huge_number & rhs);
    huge_number & operator= (const huge_number & rhs);

 private:
    std::string *num;
    bool is_bigger (std::string, std::string);
    std::string multiply (std::string &, std::string);
    std::string subtract (std::string &, std::string);
    std::string add(std::string, std::string);
    std::string divide (std::string, std::string);
    std::string mod (std::string, std::string);
};
#endif
