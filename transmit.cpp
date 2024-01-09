#include <random>
#include <vector>
#include <iostream>
#include <boost/asio.hpp>
#include <nlohmann/json.hpp>

using namespace boost::asio;
using json = nlohmann::json;

#define TRANSMITTER_IP "127.0.0.1"
#define LISTENER_IP "127.0.0.1"
#define LISTENER_PORT 8888
#define TRANSACTIONS 1000
#define MIN 1 
#define MAX 10000

double generateRandomFloat(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(min, max);
    double randomFloat = dis(gen);
    return round(randomFloat * 100) / 100;
}

int main() {

    // Transaction data
    std::vector<json> transactions;

    // Generate the transactions
    for (int i = 1; i <= TRANSACTIONS; i++) {
        json transaction = {
            {"jsonrpc", "2.0"},
            {"method", "sendTransaction"},
            {"params", {{
                "from", TRANSMITTER_IP,
                "to", LISTENER_IP,
                "amount", generateRandomFloat(MIN, MAX)
                }}},
            {"id", i}
        };
        transactions.push_back(transaction);
    }

    // Create the I/O service
    io_service io_service;
    ip::tcp::resolver resolver(io_service);
    ip::tcp::resolver::query query(LISTENER_IP, std::to_string(LISTENER_PORT));

    // // Print the generated transactions
    // for (const auto& transaction : transactions) {
    //     std::cout << transaction << std::endl;
    // }

    std::cout << "\nTransmitting " << TRANSACTIONS << " transactions to " << LISTENER_IP << ":" << LISTENER_PORT << std::endl << std::endl;

    // Connect to the listener and transmit each transaction
    for (const auto& transaction : transactions) {

        boost::system::error_code ec;

        ip::tcp::socket socket(io_service);
        
        // if (!socket.is_open()) {
        //     ec = boost::system::errc::make_error_code(boost::system::errc::not_connected);
        //     std::cerr << "Socket Creation Failed! Error Code: " << ec.value() << ". Message: " << ec.message() << "\n\n";
        //     exit(EXIT_FAILURE);
        // }
        
        ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query, ec);

        if (ec) {
            std::cerr << "Failed to Resolve Query: " << ec.message() << "\n\n";
            exit(EXIT_FAILURE);
        }

        // Connect to the receiver
        boost::asio::connect(socket, endpoint_iterator, ec);

        if (ec) {
            std::cerr << "Failed to Connect: " << ec.message() << "\n\n";
            exit(EXIT_FAILURE);
        }

        // Send the JSON-RPC transaction data
        std::string transaction_data = transaction.dump() + "\n";
        std::cout << "Sending: " << transaction_data;
        boost::asio::write(socket, boost::asio::buffer(transaction_data), ec);

        if (ec) {
            std::cerr << "Failed to Write Data: " << ec.message() << "\n\n";
            exit(EXIT_FAILURE);
        }

        // std::cout << transaction << std::endl;

        // Shut down the socket
        socket.shutdown(ip::tcp::socket::shutdown_both, ec);
        if (ec) {
            std::cerr << "Failed to Shutdown Socket: " << ec.message() << "\n\n";
            exit(EXIT_FAILURE);
        }

        // Close the socket
        socket.close(ec);
        if (ec) {
            std::cerr << "Failed to Close Socket: " << ec.message() << "\n\n";
            exit(EXIT_FAILURE);
        }
    }

    return 0;

}
