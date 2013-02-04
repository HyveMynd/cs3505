//
//  warehouse_processor.cc
//  
//
//  Created by Andres Monroy on 2/2/13.
//
//

#include "warehouse_processor.h"
#include <iostream>

namespace inventory
{
    warehouse_processor::warehouse_processor()
    {
    }
    
    /*
     * All warehouses and food_items have been registered. Add each
     * registered food_item with all warehouses and set the start date.
     */
    void warehouse_processor::set_start(date time)
    {
        start = time;
        
        //add the food_items to each warehouse
        register_food_items(time);
    }
    
    /*
     * Register a warehouse
     */
    void warehouse_processor::add_warehouse(warehouse house)
    {
        //regsiter the warehouse
        warehouses[house.get_name()] = house;
    }
    
    /*
     * Register the existance of a food_item
     */
    void warehouse_processor::add_food_item(food_item item)
    {
        //save the food items to a set to be registered to each
        //warehouse later
        food_items.push_back(item);
    }
    
    /*
     * Let all the warehouses know there is a next day
     */
    void warehouse_processor::process_next()
    {
        //loop through each warehouse and update shelf lives
        for (std::map< std::string, warehouse>::iterator iterator = warehouses.begin(); iterator != warehouses.end(); ++iterator)
        {
            iterator->second.move_to_next_day(start);
        }
        
        //add one day
        start.add_day();
    }
    
    /*
     * Let the specific warehouse know there is a receive.
     */
    void warehouse_processor::process_receive(receive item)
    {
        warehouses.find(item.get_warehouse())->second.handle_receive(item);
    }
    
    /*
     * Let the specific warehouse know there is a request.
     */
    void warehouse_processor::process_request(request item)
    {
        warehouses.find(item.get_warehouse())->second.handle_request(item);
    }
    
    /*
     * Registers all the food items with each warehouse.
     */
    void warehouse_processor::register_food_items(date time)
    {
        //loop through all warehouses and register each food_item in
        //each warehouse
        for (std::map< std::string, warehouse>::iterator it1 = warehouses.begin(); it1 != warehouses.end(); ++it1)
        {
            it1->second.set_busiest(time);
            //loop through the food_item set and add all food items
            for (std::list<food_item>::iterator it2 = food_items.begin(); it2 != food_items.end(); ++it2)
            {
                it1->second.add_food_item(*it2);
            }
        }
    }
    
    /*
     * Print out the report
     */
    void warehouse_processor::print_report()
    {
        std::cout << "Report by Andres Monroy and Cody Tanner" << "\n\n";
        
        print_out_of_stock();
        print_fully_stocked();
        print_busiest_days();
    }
    
    void warehouse_processor::print_out_of_stock()
    {
        std::cout << "Unstocked Products:" << std::endl;
        
        std::multimap< std::string, std::string > out_of_stock_pairs;
        std::list<food_item> out_of_stock_all;
        
        //loop through the warehouses and add all out of stock items from
        //each warehouse to a list
        for (std::map< std::string, warehouse>::iterator iterator = warehouses.begin(); iterator != warehouses.end(); ++iterator)
        {
            //extract the items out of stock for this warehouse
            warehouse house = iterator->second;
            std::list<std::string> items_out = house.out_of_stock_items();
            
            //loop through the upc and pair the warehouse an item is
            //missing in with its upc
            for (std::list<std::string>::iterator iterator = items_out.begin(); iterator != items_out.end(); ++iterator)
            {
                std::string upc = *iterator;
                out_of_stock_pairs.insert ( std::pair<std::string, std::string>(upc, house.get_name()));
            }
        }
        
        //if the number of times a upc pair appears in the map is
        //equal to the number of warehouses, it is missing from all warehouses
        for (std::list<food_item>::iterator it = food_items.begin(); it != food_items.end(); ++it)
        {
            std::string upc = it->get_upc();
            if(out_of_stock_pairs.count(upc) == warehouses.size()){
                out_of_stock_all.push_back(*it);
            }
        }
        print_upc_name(out_of_stock_all);
    }
    
    void warehouse_processor::print_fully_stocked()
    {
        std::cout << "Fully Stocked Products:" << std::endl;

        std::multimap< std::string, std::string > fully_stocked_pairs;
        std::list<food_item> fully_stocked_all;
        
        //loop through the warehouses and add all fully stocked items from
        //each warehouse to a list
        for (std::map< std::string, warehouse>::iterator iterator = warehouses.begin(); iterator != warehouses.end(); ++iterator)
        {
            //extract the items fully stocked for this warehouse
            warehouse house = iterator->second;
            std::list<std::string> stocked = house.fully_stocked_items();
            
            //loop through the upc and pair the warehouse with its item
            for (std::list<std::string>::iterator iterator = stocked.begin(); iterator != stocked.end(); ++iterator)
            {
                std::string upc = *iterator;
                fully_stocked_pairs.insert ( std::pair<std::string, std::string>(upc, house.get_name()));
            }
        }
        
        //if the number of times a upc pair appears in the map is
        //equal to the number of warehouses, it is stocked in all warehouses
        for (std::list<food_item>::iterator it = food_items.begin(); it != food_items.end(); ++it)
        {
            std::string upc = it->get_upc();
            if(fully_stocked_pairs.count(upc) == warehouses.size()){
                fully_stocked_all.push_back(*it);
            }
        }
        print_upc_name(fully_stocked_all);
    }
    
    /*
     * Print the upc and name of every item in the list
     */
    void warehouse_processor::print_upc_name(std::list<food_item>& a_list)
    {
        //print out the upc and name to the screen
        for (std::list<food_item>::iterator it = a_list.begin(); it != a_list.end(); ++it)
        {
            food_item item = *it;
            std::cout << item.get_upc() << "\t" << item.get_name() << std::endl;
        }
        
        std::cout << "\n";
    }
    
    /*
     * Print the busiest days in each warehouse
     */
    void warehouse_processor::print_busiest_days()
    {
        std::cout << "Busiest Days:" << std::endl;

        //loop through warehouses and print the busy days
        for (std::map< std::string, warehouse>::iterator iterator = warehouses.begin(); iterator != warehouses.end(); ++iterator)
        {
            warehouse house = iterator->second;
            std::cout << house.get_name() << " " << house.get_busiest().get_date() << " " << house.get_transactions() << std::endl;
        }
    }

}
