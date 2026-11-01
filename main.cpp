#include <stdexcept>
#include <All.h>

/*
This is a learning project wich only objective is to learn how to make a C++ game engine from scratch using DirectX11
*/

int main() {
	try {
		dx3d::Game game({ {1280, 720 }, dx3d::Logger::LogLevel::Info});
		game.Run();
	}
	catch (const std::runtime_error&) {
		return EXIT_FAILURE;
	}
	catch (const std::invalid_argument&) {
		return EXIT_FAILURE;
	}
	catch (const std::exception&) {
		return EXIT_FAILURE;
	}
	catch (...) {
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}
