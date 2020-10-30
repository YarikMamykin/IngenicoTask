#include "Server.hpp"
#include <chrono>

namespace server {
  Server::Server(const std::string& file_path)
    : log_handler(file_path) {

    }

  void Server::LogHandler::write_log(clients::TDATA&& data) {
    using system_clock = std::chrono::system_clock;
    const std::string sep = "   ";
    if(log_file.is_open() && log_file.good()) {
      log_file << system_clock::to_time_t(system_clock::now())
        << sep
        << data.dwClientId 
        << sep
        << static_cast<DWORD>(data.cPriority)
        << sep
        << data.dwTicks
        << std::endl;
    }
  }

  Server::LogHandler::LogHandler(const std::string& file_path) 
    : log_file() { 
      reset_file(file_path);
      log_file.open(file_path, std::ofstream::out | std::ofstream::app);
    }

  Server::LogHandler::~LogHandler() { 
    log_file.close();
  }

  void Server::LogHandler::reset_file(const std::string& file_path) {
    log_file.open(file_path);
    log_file.close();
  }

  void Server::process_client_data(clients::TDATA &&data) {
    log_handler.write_log(std::move(data));
  }
}
