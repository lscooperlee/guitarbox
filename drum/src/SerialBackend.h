#ifndef SERIALBACKEND_H
#define SERIALBACKEND_H

#include <string>

class SerialBackend {
public:
  SerialBackend(std::string name);
  ~SerialBackend();
  void run();

private:
  int serial_fd = 0;
};

#endif /* SERIALBACKEND_H */
