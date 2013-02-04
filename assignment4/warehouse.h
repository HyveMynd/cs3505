/* This  class is used to build warehouse objects for a warehouse simulation
 * warehouse class
 *
 * Cody Tanner
 * u0291987
 * January, 2013
 */

#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include<string>
#include<map>
#include "food_item.h"
#include "receive.h"
#include "request.h"
#include <list>
#include "date.h"

namespace inventory
{
  class warehouse
  {
  public:
      warehouse();
      warehouse(std::string name);
      warehouse(const warehouse&);
      const warehouse& operator= (const warehouse& rhs);
      bool operator <(const warehouse& rhs) const;
      
      // public methods
      std::string get_name() const;
      void add_food_item(food_item item);
      void move_to_next_day(date);
      void handle_receive(receive);
      void handle_request(request);
      std::list<std::string> out_of_stock_items();
      std::list<std::string> fully_stocked_items();
      date get_busiest() const;
      int get_transactions() const;
      void set_busiest(date);
      
  private:
      std::string name;
      std::map< std::string, food_item > inv;
      date busiest;
      int high_trans;
  };
}

#endif
