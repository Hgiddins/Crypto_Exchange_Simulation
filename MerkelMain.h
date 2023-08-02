#pragma once
#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"

class MerkelMain{
    public:
        MerkelMain();

        /** Call to start simulation*/
        void init();
    
    private:
        void printMenu();
        void printHelp();
        void marketStats();
        void enterAsk();
        void makeBid();
        void getWalletBalance();
        void nextTimeFrame();
        int getUserOption();
        void processUserOption(int userOption); 

        std::string currentTime;
        

        OrderBook orderBook{"orders.csv"};

        Wallet wallet{};

};