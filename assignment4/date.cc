/* This  class is used to build date objects for a warehouse simulation
 * date class
 *
 * Cody Tanner
 * u0291987
 * January, 2013
 */

#include <string>
#include "date.h"
#include <stdio.h>
#include <stdlib.h>

namespace inventory
{
    date::date()
    {
        this->year = 0;
        this->month = 0;
        this->day = 0;
    }
    
    date::date(std::string date)
    {
        month = atoi(date.substr(0,2).c_str());
        day = atoi(date.substr(3,2).c_str());
        year = atoi(date.substr(6,4).c_str());
    }
    
    date::date(const date& other)
    {
        this->year = 0;
        this->month = 0;
        this->day = 0;
        
        *this = other;
    }
    
    const date& date::operator= (const date& rhs)
    {
        if(this == &rhs)
            return *this;
        
        this->year = rhs.year;
        this->month = rhs.month;
        this->day = rhs.day;
        
        return *this;
    }
    
    void date::add_day()
    {
        day++;
        
        if(month == 2){
            if (day > 29 && is_leap_year())
                next_month();
            else if(day > 28 && !is_leap_year())
                next_month();
        }
        //take care of possibly going into the next month
        else if(has_31_days())
        {
            if (day > 31)
                next_month();
        }
        else{
            if(day > 30)
                next_month();
        }
    }
    
    void date::next_month()
    {
        month++;
        day = 1;
        
        //check for moving into next year
        if (month > 12){
            year ++;
            month = 1;
        }
    }
    
    bool date::is_leap_year()
    {
        return year % 4 == 0;
    }
    
    bool date::has_31_days()
    {
        return (month < 8 && month % 2 != 0) || (month >=8 && month % 2 == 0);
    }
    
    int date::get_month()
    {
        return month;
    }
    
    int date::get_day()
    {
        return day;
    }
    
    int date::get_year()
    {
        return year;
    }
    std::string date::get_date()
    {
        std::ostringstream convert;
        std::string d;
        std::string m;
        std::string y;
        
        if (day < 10){
            convert << "0";
            convert << day;
        }
        else{
            convert << day;
        }
        
        convert << "/";
        
        if (month < 10){
            convert << "0";
            convert << month;
        }
        else{
            convert << month;
        }
        
        convert << "/";
        convert << year;
        
        return convert.str();
    }
}
