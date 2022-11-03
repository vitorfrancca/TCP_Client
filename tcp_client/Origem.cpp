#include <iostream>
#define ASIO_STANDALONE
#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif 
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

int main() {
	asio::error_code ec; //pega erros especificos

	//Cria o "context" 
	asio::io_context context;

	//Pega o endereço no qual estamos conectando1
	asio::ip::tcp::endpoint endpoint(asio::ip::make_address("192.168.1.100", ec), 1000);

	//Cria o socket, o context ira entregar a implementaçao
	asio::ip::tcp::socket socket(context);

	//Diz ao socket para tentar se conectar
	socket.connect(endpoint, ec);

	if (!ec) {
		std::cout << "Conectado!" << std::endl;
	}

	else {
		std::cout << "Falha de conecxao com o endereço: \n" << ec.message()/*pega mensagem associada ao erro */ << std::endl;
	}

	//Verifia se esta conectado
	if (socket.is_open()) {

		char packet_bytes[] = {"Teles"
		};




		//Se conexçao for True, escreve:
		//asio::buffer e um container, contendo bytes da string e sizer.
		socket.write_some(asio::buffer(packet_bytes, sizeof(packet_bytes)), ec);

		//Estava dando erro pelo tempo de resposta, programa indo mais rapido que a resposta.		
		socket.wait(socket.wait_read);

		size_t bytes = socket.available();
		std::cout << "Bytes Available: " << bytes << std::endl;

		if (bytes > 0) {
			//adiciona dados recebidos em um vector
			std::vector<char> vBuffer(bytes);
			socket.read_some(asio::buffer(vBuffer.data(), vBuffer.size()), ec);
			// 
			for (auto c : vBuffer) {
				std::cout << c;
			}
		}


	}
	system("pause");
	return 0;

}
