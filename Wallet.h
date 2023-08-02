#include <string>
#include <map>
#include "OrderBookEntry.h"

class Wallet
{
    public:
        Wallet();
        /**insert currency to wallet*/
        void insertCurrency(std::string type, double amount);

        /**remove currency to wallet*/
        bool removeCurrency(std::string type, double amount);

        /**check wallet contains this much currency*/
        bool containsCurrency(std::string type, double amount);

        /**check wallet can dealw ith the ask/bid*/
        bool canFulfillOrder(OrderBookEntry order);

        /**updates wallet contents assuming order made by owner of wallet*/
        void processSale(OrderBookEntry& sale);

        /**Printing out wallet contents*/
        std::string toString();

    
    private:
        std::map<std::string,double> currencies;


};