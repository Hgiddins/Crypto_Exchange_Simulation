#include "OrderBook.h"
#include <map> 


/** construct, reading a csv data file*/
OrderBook::OrderBook(std::string filename){

    orders = CSVReader::readCSV(filename);
}

/** return vector of all known products in the dataset*/
std::vector<std::string> OrderBook::getKnownProducts(){

    std::vector<std::string> products;

    std::map<std::string,bool> prodMap;

    for (OrderBookEntry& e : orders){
        prodMap[e.product] = true;
    }

    for (auto const& e : prodMap){
        products.push_back(e.first);
    }

    return products;
}

/** return vector of orders according to sent filters*/
std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type,
                                        std::string product,
                                        std::string timestamp){
    
    std::vector<OrderBookEntry> orders_sub;
    for (OrderBookEntry& e : orders){

        if (e.orderType == type &&
            e.product == product &&
            e.timestamp == timestamp){

                    orders_sub.push_back(e);
            }
    }
    return orders_sub;

}

double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders){
    double max = orders[0].price;

    for (OrderBookEntry& e : orders){
        if (e.price > max){
            max = e.price;
        }
    }
    return max;
}

double OrderBook::getLowPrice(std::vector<OrderBookEntry>& orders){
    double min = orders[0].price;

    for (OrderBookEntry& e : orders){
        if (e.price < min){
            min = e.price;
        }
    }
    return min;
}

std::string OrderBook::getEarliestTime(){
    return orders[0].timestamp;
}

std::string OrderBook::getNextTime(std::string timestamp){
    std::string next_timestamp = "";

    for (OrderBookEntry& e : orders){
        if (e.timestamp > timestamp){
            next_timestamp = e.timestamp;
            break;
        }
    }

    if (next_timestamp == ""){
        next_timestamp = orders[0].timestamp;
    }

    return next_timestamp;
}

void OrderBook::insertOrder(OrderBookEntry& order){
    orders.push_back(order);
    std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestamp);
}



// MATCHING ALGORITHM
std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string product, std::string timestamp){
    // vector of asks
    std::vector<OrderBookEntry> asks = getOrders(OrderBookType::ask,
                                                product,
                                                timestamp);

    // vector of bids
    std::vector<OrderBookEntry> bids = getOrders(OrderBookType::bid,
                                                product,
                                                timestamp);

    // vector of sales
    std::vector<OrderBookEntry> sales;

    // sort asks lowest first
    std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);

    // sort bids highest first
    std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc);

    // for ask in asks
    for (OrderBookEntry& ask : asks){
        // for bid in bids
        for (OrderBookEntry& bid : bids){
        
            // if bid price >= ask price then match
            if (bid.price >=ask.price){
                OrderBookEntry sale{ask.price, 0, timestamp, product, OrderBookType::asksale};
                
                OrderBookType type = OrderBookType::asksale;
                if (bid.username=="simuser"){
                    type = OrderBookType::bidsale;
                    sale.username ="simuser";
                    sale.orderType = type;
                }
                if (ask.username == "simuser"){
                    type = OrderBookType::asksale;
                    sale.username ="simuser";
                    sale.orderType = type;
                }

                
                // perfect match, bid and ask done with
                if (bid.amount== ask.amount){
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = 0;
                    break;
                }

                if (bid.amount > ask.amount){
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = bid.amount - ask.amount;
                    break;
                }

                // continue not break here as we have not finished processing the ask
                if (bid.amount < ask.amount && bid.amount>0){
                    sale.amount = bid.amount;
                    sales.push_back(sale);
                    ask.amount = ask.amount - bid.amount;
                    bid.amount = 0;
                    continue;
                }

            }

            

        }

    }
    return sales;
    }