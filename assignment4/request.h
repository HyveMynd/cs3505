//
//  request.h
//  
//
//  Created by Andres Monroy on 1/29/13.
//
//

#ifndef _request_h
#define _request_h

#include<string>

namespace inventory
{
    class request
    {
    public:
        request(std::string upc, int quantity, std::string warehouse);
        std::string get_upc();
        int get_quantity();
        std::string get_warehouse();
    private:
        std::string upc;
        int quantity;
        std::string warehouse;
    };
}

#endif
