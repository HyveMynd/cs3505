//
//  warehouse_processor.h
//  
//
//  Created by Andres Monroy on 2/1/13.
//
//

#ifndef _warehouse_processor_h
#define _warehouse_processor_h

#include "food_item.h"
#include "warehouse.h"
#include "date.h"
#include "receive.h"
#include "request.h"
#include <map>
#include <list>

namespace inventory
{
    class warehouse_processor
    {
    public:
        warehouse_processor();
        
        void process_receive(receive item);
        void process_request(request item);
        void process_next();
        void set_start(date);
        
        void add_warehouse(warehouse);
        void add_food_item(food_item);
        void print_report();
        
    private:
        date start;
        std::map<std::string, warehouse> warehouses;
        std::list<food_item> food_items;
        
        void print_out_of_stock();
        void print_fully_stocked();
        void register_food_items(date);
        void print_upc_name(std::list<food_item>& a_list);
        void print_busiest_days();
    };
}

#endif
