    /* This  class is used to build food_item objects for a warehouse simulation
 * food_item class
 *
 * Cody Tanner
 * u0291987
 * January, 2013
 */

#ifndef FOOD_ITEM_H
#define FOOD_ITEM_H

#include<string>
#include <list>

namespace inventory
{
  class food_item
  {
  public:
      food_item();
      food_item(std::string upc, int shelf_life, std::string name);
      food_item(const food_item&);
      const food_item& operator= (const food_item& rhs);
      bool operator <(const food_item& rhs) const;
      
      // public methods
      std::string get_upc() const;
      int get_shelf_life() const;
      std::string get_name() const;
      int get_receive_count() const;
      int get_request_count() const;
      void receive_items(int quantity);
      void request_items(int quantity);
      void next_day();
      bool is_empty();

  private:
      std::string upc;
      int shelf_life;
      std::string name;
      std::list<int> items;
      int receive_count;
      int request_count;
      
      void remove_expired();
  };
}

#endif