/* Represents a single food_item. May be strored within warehouses.
 *
 * Cody Tanner
 * u0291987
 * January, 2013
 */

#include <string>
#include "food_item.h"
#include <iostream>

namespace inventory
{
    food_item::food_item()
    {
        this->upc = "";
        this->shelf_life = 0;
        this->name = "";
        this->receive_count = 0;
        this->request_count = 0;
    }
    
    food_item::food_item(std::string u, int s, std::string n)
    {
        this->upc = u;
        this->shelf_life = s;
        this->name = n;
        this->receive_count = 0;
        this->request_count = 0;
    }
    
    food_item::food_item(const food_item& other)
    {
        this->upc = "";
        this->shelf_life = 0;
        this->name = "";
        items = std::list<int>();
        this->receive_count = 0;
        this->request_count = 0;
        
        *this = other;
    }
    
    const food_item& food_item::operator= (const food_item& rhs)
    {
        if (this == &rhs)
            return *this;
        
        this->upc = rhs.upc;
        this->shelf_life = rhs.shelf_life;
        this->name = rhs.name;
        this->items = rhs.items;
        this->receive_count = rhs.get_receive_count();
        this->request_count = rhs.get_request_count();
        
        return *this;
    }
    
    bool food_item::operator <(const food_item& rhs) const
    {
        return this->upc < rhs.get_upc();
    }
    
    /*
     * Add the received number of items to the list.
     */
    void food_item::receive_items(int quantity)
    {
        for (int i = 0; i < quantity; i++)
            items.push_back(shelf_life);
        
        receive_count+= quantity;
    }
    
    /*
     * Removes the requested number of item from the list. If the
     * request cannot be fully satisfied, the list will be emtpy.
     */
    void food_item::request_items(int quantity)
    {
        //emtpy the list if the quantity is greater than
        //the number it currently has.
        if (quantity > items.size())
        {
            items.clear();
        }
        else
        {
            for (int i = 0;i < quantity; i++)
            {
                items.pop_front();
            }
        }
        
        request_count += quantity;
    }
    
    /*
     * Subtracts one day form the shelf life of each item held in the list
     */
    void food_item::next_day()
    {
        for (std::list<int>::iterator iterator = items.begin(), next, end = items.end(); iterator != end; iterator = next) {
            next = iterator;
            ++next;
            
            int val = *iterator;
            val--;
            
            //check for removal of expired item
            if(val == 0)
                items.erase(iterator);
            else
                *iterator = val;
        }
        
        //reset counters for busy day
        receive_count = 0;
        request_count = 0;
    }
    
    /*
     * Returns true if there are no items in the list
     */
    bool food_item::is_empty()
    {
//        std::cout << upc << "\t" << receive_count << std::endl;
//        std::cout << upc << "\t" << request_count << std::endl;
        return items.size() == 0;
    }
    
    /*
     * Accessor methods
     */
    std::string food_item::get_upc() const
    {
        return upc;
    }
    int food_item::get_shelf_life() const
    {
        return shelf_life;
    }
    std::string food_item::get_name() const
    {
        return name;
    }
    int food_item::get_receive_count() const
    {
        return receive_count;
    }
    int food_item::get_request_count() const
    {
        return request_count;
    }
}
