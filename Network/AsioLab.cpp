#include "net_common.h"

int main() {
    asio::error_code ec;

    //Create a context
    asio::io_context context;

    //Get the address of somewhere we wish to connect to
    asio::ip::tcp::endpoint endpoint(asio::ip::make_address("93.184.216.34", ec), 80);

    //Create a socket
    asio::ip::tcp::socket socket(context);

    //Tell socket to connect
    socket.connect(endpoint, ec);

    if(!ec){
        std::cout << "Connected!\n";
    }else{
        std::cout << "Failed to connect to address:\n" << ec.message() << '\n';
    }

 

    std::cout << "Hello world\n";
    return 0;
}