#include <iostream>
#include <boost/asio.hpp>

int main()
{
    // Obtém as informações de conexão do servidor de achievements
    std::string ip_address = "127.0.0.1"; // Endereço IP do servidor de achievements
    unsigned short port = 8080; // Porta do servidor de achievements

    // Cria o objeto do servidor
    boost::asio::ip::tcp::endpoint endpoint(
        boost::asio::ip::address::from_string(ip_address),
        port
    );

    // Cria o objeto do socket
    boost::asio::ip::tcp::socket socket(endpoint.get_io_service());

    // Conecta ao servidor de achievements
    socket.connect(endpoint);

    std::cout << "Conectado ao servidor de achievements!" << std::endl;

    // Envia um pacote para o servidor de achievements
    std::string mensagem = "Olá";
    boost::asio::write(socket, boost::asio::buffer(mensagem));

    // Executa as operações pendentes no objeto io_service
    endpoint.get_io_service().run();

    return 0;
}
