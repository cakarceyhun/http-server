
#include <iostream>
#include <memory>

struct SocketPrivateValues;

class Socket
{
public:
    Socket();

    std::string read();
private:
    std::shared_ptr<SocketPrivateValues> self;
};

