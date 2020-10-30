#ifndef SRC_INCLUDES_SERVER_SERVER_HPP
#define SRC_INCLUDES_SERVER_SERVER_HPP

#include <string>
#include <fstream>
#include "ClientData.hpp"

namespace server {
  struct Server {
    struct LogHandler {
      std::ofstream log_file;
      LogHandler(const std::string& file_path);
      ~LogHandler();
      void write_log(clients::TDATA&& data);
      void reset_file(const std::string& file_path);

    } log_handler;

    Server(const std::string& file_path);
    void process_client_data(clients::TDATA&& data);
  };
}

#endif /* SRC_INCLUDES_SERVER_SERVER_HPP */
