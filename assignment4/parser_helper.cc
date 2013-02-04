//
//  parser_helper.cc
//  
//
//  Created by Andres Monroy on 1/28/13.
//
//

#include "parser_helper.h"
#include <sstream>
#include <iostream>
#include <string>
#include "food_item.h"
#include "warehouse.h"
#include "date.h"
#include "request.h"
#include "receive.h"
#include <stdio.h>
#include <stdlib.h>

namespace inventory
{
    food_item parser_helper::handle_food_item(std::string line)
    {
        std::string word;
        std::stringstream reader(line);
        std::string upc;
        std::string shelf_life;
        std::string name;
        
        //read through the line until until we reach the end
        while (reader.good()){
            reader >> word;
            if (word.compare("Code:") == 0){
                //read one more word to get the upc code
                reader >> word;
                upc = word;
            }
            else if(word.compare("life:") == 0){
                reader >> word;
                shelf_life = word;
            }
            else if(word.compare("Name:") == 0){
                //read in the rest of the line
                while(reader >> word){
                    //reader >> word;
                    name += word + " ";
                }
            }
        }
        
        //create the object to return
        return food_item(upc, atoi(shelf_life.c_str()), name);
    }
    
    warehouse parser_helper::handle_warehouse(std::string line)
    {
        std::string word;
        std::stringstream reader(line);
        std::string name;
        
        //read through the line until until we reach the end
        while (reader.good()){
            reader >> word;
            if (word.compare("-") == 0){
                //read one more word to get the upc code
                reader >> word;
                name = word;
            }
        }
        
        //create the object to return
        return warehouse(name);
    }

    date parser_helper::handle_date(std::string line)
    {
        std::string word;
        std::stringstream reader(line);
        std::string start;
        
        //read through the line until until we reach the end
        while (reader.good()){
            reader >> word;
            if (word.compare("date:") == 0){
                //read one more word to get the upc code
                reader >> word;
                start = word;
            }
        }
        
        return date(start);
    }
    
    request parser_helper::handle_request(std::string line)
    {
        std::string word;
        std::stringstream reader(line);
        std::string upc;
        std::string quantity;
        std::string warehouse;
        
        //read through the line until until we reach the end
        while (reader.good()){
            reader >> word;
            if (word.compare("Request:") == 0){
                //read till end of line
                reader >> word;
                upc = word;
                reader >> word;
                quantity = word;
                reader >> word;
                warehouse = word;
            }
        }
        
        //create the object to return
        return request(upc, atoi(quantity.c_str()), warehouse);
    }
    
    receive parser_helper::handle_receive(std::string line)
    {
        std::string word;
        std::stringstream reader(line);
        std::string upc;
        std::string quantity;
        std::string warehouse;
        
        //read through the line until until we reach the end
        while (reader.good()){
            reader >> word;
            if (word.compare("Receive:") == 0){
                //read till end of line
                reader >> word;
                upc = word;
                reader >> word;
                quantity = word;
                reader >> word;
                warehouse = word;
            }
        }
        
        //create the object to return
        return receive(upc, atoi(quantity.c_str()), warehouse);
    }

}