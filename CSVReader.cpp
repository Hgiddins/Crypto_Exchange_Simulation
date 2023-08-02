#include "CSVReader.h"
#include <iostream>
#include <string>
#include <fstream>

CSVReader::CSVReader(){
    
}


std::vector<OrderBookEntry> CSVReader::readCSV(std::string CSVFilename){
    std::vector<OrderBookEntry> entries;

    std::ifstream csvFile{CSVFilename};
    std::string line;

    if (csvFile.is_open()){

        while(std::getline(csvFile, line)){
            try{
                OrderBookEntry obe = stringToOBE(tokenise(line, ','));
                entries.push_back(obe);
            }catch(const std::exception& e){
                std::cout <<  "Bad data" << std::endl; 
            }
        }//end of while
    }

    std::cout <<  "CSVReader read " << entries.size() << " entries" << std::endl; 
    return entries;
}


std::vector<std::string> CSVReader::tokenise(std::string csvLine, char separator){

    std::vector<std::string> tokens;
    std::string token;
    signed int start, end;
    start = csvLine.find_first_not_of(separator,0);

    do{
        end = csvLine.find_first_of(separator,start);

        if (start == csvLine.length() || start == end) break;
        if (end >= 0) token = csvLine.substr(start,end - start);
        else token = csvLine.substr(start, csvLine.length() -  start);

        tokens.push_back(token);
        start = end + 1;

    }while(end >0);

    return tokens;
}


OrderBookEntry CSVReader::stringToOBE(std::vector<std::string> tokens){
        // checking there are 5 tokens else bad data and skipping line
    double price, amount;

    if (tokens.size() != 5){
        std::cout << "CSVReader::stringToOBE Bad line "  << std::endl;
        throw std::exception{};
    }

    try{
        price = std::stod(tokens[3]);
        amount = std::stod(tokens[4]);
        std::cout << price << " : " << amount << std::endl;

    } catch(const std::exception& e){
        std::cout << "CSVReader::stringToOBE Bad float!" << std::endl;
        throw;
    }

           
    OrderBookEntry obe{price,
                        amount,
                        tokens[0],
                        tokens[1], 
                        OrderBookEntry::stringToOrderBookType(tokens[2])};
    return obe;
}

OrderBookEntry CSVReader::stringToOBE(std::string priceString, 
                                            std::string amountString,
                                            std::string timestamp,
                                            std::string product, 
                                            OrderBookType orderType)
    {
        double price,amount;
        try{
            price = std::stod(priceString);
            amount = std::stod(amountString);
            std::cout << price << " : " << amount << std::endl;

        } catch(const std::exception& e){
            std::cout << "CSVReader::stringToOBE Bad float!" << std::endl;
            throw;
        }

        OrderBookEntry obe{price,
                        amount,
                        timestamp,
                        product, 
                        orderType}; 
        
        return obe;
    }
