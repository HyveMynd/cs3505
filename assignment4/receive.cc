//
//  receive.cc
//  
//
//  Created by Andres Monroy on 1/29/13.
//
//

#include "receive.h"
#include <string>

namespace inventory
{
    receive::receive(std::string upc, int quantity, std::string warehouse)
    {
        this->upc = upc;
        this->quantity = quantity;
        this->warehouse = warehouse;
    }
    
    std::string receive::get_upc()
    {
        return upc;
    }
    
    int receive::get_quantity()
    {
        return quantity;
    }
    
    std::string receive::get_warehouse()
    {
        return warehouse;
    }
}