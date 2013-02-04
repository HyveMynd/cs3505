#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include "warehouse.h"
#include "food_item.h"
#include "date.h"
#include "parser_helper.h"
#include "receive.h"
#include "request.h"
#include "warehouse_processor.h"

using namespace std;

string first_word(const string& line);

int main(int argc, char* argv[])
{
    string file_name = argv[1];
    ifstream inv_file(argv[1]);
    string line;
    string command;
    inventory::warehouse_processor processor;
    
    if (inv_file.is_open())
    {
        while ( inv_file.good() )
        {
            
            getline(inv_file, line);
            command = first_word(line);
            
            if(command == "FoodItem")
            {
                string ln = line;
                inventory::food_item item = inventory::parser_helper::handle_food_item(ln);
                
                processor.add_food_item(item);
            }
            else if(command == "Warehouse")
            {
                string ln = line;
                inventory::warehouse item = inventory::parser_helper::handle_warehouse(ln);
                
                processor.add_warehouse(item);
            }
            else if(command == "Start")
            {
                string ln = line;
                inventory::date item = inventory::parser_helper::handle_date(ln);
                
                processor.set_start(item);
            }
            else if(command == "Receive:")
            {
                string ln = line;
                inventory::receive item = inventory::parser_helper::handle_receive(ln);
                
                processor.process_receive(item);
            }
            else if(command == "Request:")
            {
                string ln = line;
                inventory::request item = inventory::parser_helper::handle_request(ln);
                
                processor.process_request(item);
            }
            else if(command == "Next")
            {
                processor.process_next();
            }
            
        }
        inv_file.close();
        processor.print_report();
    }
    return 0;
}

string first_word(const string& line)
{
    return line.substr(0, line.find(' '));
}