# Cryptocurrency Trading Simulator

This project provides a basic simulation environment for cryptocurrency trading. At its core, it uses a **Price-Time Priority matching algorithm** with FIFO sequencing, allowing for partial order completions on a Pro Rata basis. The user can interact with the trading system, view market stats, make offers, bid, and more.

## Features

- **User Interaction**: A simple menu-driven system that allows users to perform various operations.
- **Order Placement**: Users can make bids and offers with desired amounts.
- **Market Stats**: View statistics about different products in the order book.
- **Wallet Management**: Keep track of your cryptocurrency wallet.
- **Price-Time Priority Matching Algorithm**: Incorporates FIFO sequencing and allows partial order completions on a Pro Rata basis.

## Compilation 
g++ --std=c++11 main.cpp OrderBookEntry.cpp MerkelMain.cpp OrderBook.cpp CSVReader.cpp Wallet.cpp

## Execution
./a.out

# Simulator Options

Options:

0. Quit the simulator.
1. View a brief description about the simulation.
2. See the market statistics for all the known products.
3. Place an offer.
4. Make a bid.
5. Print the current state of your wallet.
6. Move to the next time frame.

## Limitations

This simulator is designed for educational purposes and is a simplification of a real-world trading system.
It currently supports a limited set of products, and some real-world features might be missing.

## Contribution

Feel free to fork the repository and submit pull requests for any optimizations, bug-fixes, or feature enhancements.

## License

This project is open-source, under the MIT license.

