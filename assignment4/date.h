/* This  class is used to build food_item objects for a warehouse simulation
 * food_item class
 *
 * Cody Tanner
 * u0291987
 * January, 2013
 */

#ifndef DATE_H
#define DATE_H

#include<string>
#include <sstream>

namespace inventory
{
  class date
  {
  public:
      date();
      date(std::string date); //  constructor with parameter
      date(const date& other);
      const date& operator= (const date& rhs);
      
      // public methods
      int get_month();
      int get_day();
      int get_year();
      std::string get_date();
      void add_day();
      
  private:
      int month;
      int day;
      int year;
      bool is_leap_year();
      bool has_31_days();
      void next_month();
  };
}

#endif
