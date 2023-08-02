#include "MerkelMain.h"
#include <iostream>
#include <vector>
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include "OrderBook.h"

MerkelMain::MerkelMain(){

}

void MerkelMain::init(){
 
    int input;
    currentTime = orderBook.getEarliestTime();
    wallet.insertCurrency("BTC", 10);

    while(true){
        printMenu();
        input = getUserOption();
        processUserOption(input);
        if (input == 0){
            std::cout << "Quitting" << std::endl;
            break;
        }

        
    }

}


void MerkelMain::printMenu() {
    std::cout << "" << std::endl;
    // 0 Quit
    std::cout << "0. Quit" << std::endl;
    // 1 print help
    std::cout << "1. Help" << std::endl;
    // 2 print exchange stats
    std::cout << "2. Exchange stats" << std::endl;
    // 3 make an offer
    std::cout << "3. Make an offer" << std::endl;
    // 4 make a bid
    std::cout << "4. Make a bid" << std::endl;
    // 5 print wallet
    std::cout << "5. Print wallet" << std::endl;
    // 6 continue
    std::cout << "6. Continue" << std::endl;

    std::cout << "=======================" << std::endl;
    std::cout << "Current Time: " << currentTime <<std::endl;
    
}

void MerkelMain::printHelp() {
    std::cout << "Your goal is to trade and make $$$" << std::endl;
}

void MerkelMain::marketStats() {
    
    for (std::string const& p : orderBook.getKnownProducts()){ 
        
        std::cout << "Product: " << p << std::endl;
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask,
                                                                    p,
                                                                    currentTime);
        std::cout << "Asks seen: " << entries.size() << std::endl;
        std::cout << "Max. Ask: " << OrderBook::getHighPrice(entries) << std::endl;
        std::cout << "Min. Ask: " << OrderBook::getLowPrice(entries) << std::endl;

    }

}

void MerkelMain::enterAsk(){
    std::cout << "Offer - enter amount: product,price,amount e.g. ETH/BTC,0.1,0.5" << std::endl;
    std::string input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, input);
    

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size()!=3){
        std::cout<<"!!! Invalid Input : "<< input << std::endl;
    }
    else{
        try{
            OrderBookEntry obe = CSVReader::stringToOBE(tokens[1],tokens[2],currentTime,tokens[0],OrderBookType::ask);
            obe.username = "simuser";
            if(wallet.canFulfillOrder(obe)){
                std::cout<<"Wallet looks good"<<std::endl;
                orderBook.insertOrder(obe);
            }
            else{
                std::cout<<"Insufficient funds"<<std::endl;
            }
        
        }catch (const std::exception& e){
            std::cout << "Bad input" << std::endl;
        }

    }
}

void MerkelMain::makeBid(){
    std::cout << "Bid - enter amount: product,price,amount e.g. ETH/BTC,0.1,0.5" << std::endl;
    std::string input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, input);
    

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size()!=3){
        std::cout<<"!!! Invalid Input : "<< input << std::endl;
    }
    else{
        try{
            OrderBookEntry obe = CSVReader::stringToOBE(tokens[1],tokens[2],currentTime,tokens[0],OrderBookType::bid);
            obe.username = "simuser";
            if(wallet.canFulfillOrder(obe)){
                std::cout<<"Wallet looks good"<<std::endl;
                orderBook.insertOrder(obe);
            }
            else{
                std::cout<<"Insufficient funds"<<std::endl;
            }
        
        }catch (const std::exception& e){
            std::cout << "Bad input" << std::endl;
        }

    }
}

void MerkelMain::getWalletBalance(){
    std::cout << wallet.toString() << std::endl;
}

void MerkelMain::nextTimeFrame() {
    std::cout << "Next Timeframe" << std::endl;
    std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids("ETH/BTC", currentTime);
    std::cout<< "Sales made: "<<sales.size()<<std::endl;
    for (OrderBookEntry& sale : sales){
        std::cout<< "sale: " << sale.price << " amount: " << sale.amount << std::endl;
        
        if (sale.username == "simuser"){
            // update the wallet
            wallet.processSale(sale);
        }
    }

    currentTime = orderBook.getNextTime(currentTime);
}

int MerkelMain::getUserOption() {
    int userOption;
    while (true) {
        std::cin >> userOption;

        // If the stream is in an error state, clear it and skip the rest of this iteration
        if (std::cin.fail()) {
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number." << std::endl;
            continue;  // Skip the rest of this loop iteration
        }

        if (userOption >= 0 && userOption <= 6) {
            break;  // Exit the loop if the input is valid
        } else {
            std::cout << "Invalid input. Please choose a number between 0 and 6." << std::endl;
        }
    }
    return userOption;
}




void MerkelMain::processUserOption(int userOption) {

    std::cout << "You chose: " << userOption << std::endl;

    
    if (userOption==1){
        printHelp();
    }
    if (userOption==2){
        marketStats();
    }
    if (userOption==3){
        enterAsk();
    }
    if (userOption==4){
        makeBid();
    }
    if (userOption==5){
        getWalletBalance();
    }
    if (userOption==6){
        nextTimeFrame();
    }
}






