#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <nlohmann/json.hpp>

using namespace boost::asio;
using json = nlohmann::json;

#define TRANSMITTER_IP "127.0.0.1"
#define PORT 8888

void handleConnection(ip::tcp::socket socket) {
    // Receive JSON-RPC transaction data
    boost::asio::streambuf buffer;
    try {
        boost::asio::read_until(socket, buffer, "\n");
    } catch (const boost::system::system_error& e) {
        std::cerr << "Failed to Read Data: " << e.what() << std::endl;
        return;
    }

    std::string json_data(boost::asio::buffer_cast<const char*>(buffer.data()), buffer.size());
    std::cout << "Received: " << json_data << std::endl;

    // Parse the received JSON-RPC transaction data
    try {
        json transaction = json::parse(json_data);

        // Process the parsed JSON-RPC transaction data
        // ...

        // Optionally, send a response back to the sender
        json response = {
            {"jsonrpc", "2.0"},
            {"result", "Transaction received"},
            {"id", nullptr}
        };
        std::string response_str = response.dump() + "\n";
        boost::asio::write(socket, boost::asio::buffer(response_str));
    } catch (const std::exception& e) {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
        // Optionally, send an error response back to the sender
        json error_response = {
            {"jsonrpc", "2.0"},
            {"error", {"Parse error", -32700}},
            {"id", nullptr}
        };
        std::string error_response_str = error_response.dump() + "\n";
        boost::asio::write(socket, boost::asio::buffer(error_response_str));
    }
}

int main() {
    io_service io_service;

    try {
        // Listen on PORT for incoming connections
        ip::tcp::acceptor acceptor(io_service, ip::tcp::endpoint(ip::tcp::v4(), PORT));
        std::cout << "Listening on PORT " << PORT << std::endl;

        while (true) {
            // Wait for and Accept incoming connections
            ip::tcp::socket socket(io_service);
            boost::system::error_code ec;
            acceptor.accept(socket, ec);

            if (ec) {
                std::cerr << "Failed to Accept Connection: " << ec.message() << std::endl;
                exit(EXIT_FAILURE);
            }

            // Handle the connection in a new thread
            std::thread(handleConnection, std::move(socket)).detach();
        }
    } catch (const boost::system::system_error& e) {
        std::cerr << "Failed to listen on PORT " << PORT << ": " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    return 0;
}
