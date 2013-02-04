//
//  parser_helper.h
//  
//
//  Created by Andres Monroy on 1/28/13.
//
//

#ifndef _parser_helper_h
#define _parser_helper_h

#include<string>
#include"food_item.h"
#include"warehouse.h"
#include"date.h"
#include "request.h"
#include "receive.h"

namespace inventory
{
 class parser_helper
    {
    public:
        static food_item handle_food_item(std::string line);
        static warehouse handle_warehouse(std::string line);
        static date handle_date(std::string line);
        static request handle_request(std::string line);
        static receive handle_receive(std::string line);
    private:
    };
}


#endif
