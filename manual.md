# CLasses

## boost::asio::io_service
this entity is uesd to talk to the operating system's input/output services. You can't have several `io_service` instance and one thread.
It would make no sense to have the following code snippet:

```CXX
for (int i = 0; i < 2; ++i)
    service_[i].run();
```

The `io_service` class is thread-safe. Several threads can call `io_service::run()`. 
If you call `io_service::run()` in only one thread, all callbacks are called in the context of that thread.

Usually one instance of an io_service will be enough.
### Synchronous part

### Asynchronous part
---
Method `run` loop will run as long as there are asynchronous operations pending

## boost::asio::ip::tcp::endpoint
this class helps to store the address and port that we want to connect to.
Each different type of socket has its own `endpoint` calss.

Example of definition:

```CXX
namespace ip = boost::asio::ip;

ip::tcp::endpoint ep1; // can be used sometimes for UDP/ICMP sockets
ip::tcp::endpoint ep2(ip::tcp::v4(), 80); // as usual used on server sockets for accepting new connections
ip::tcp::endpoint ep3( ip::address::from_string("127.0.0.1"), 2001);

// if you want to connect to a hostname(not an IP), what should you do:
io_service service;
ip::tcp::resolver resolver(service);
ip::tcp::resolver::query query("www.yandex.ru", "80");
ip::tcp::resolver::iterator iter = resolver.resolve(query);
ip::tcp::endpoint ep = *iter;
std::cout << ep.address().to_string() << ":" << ep.port()
          << "/" << ep.protocol() << std::endl;
```

## boost::asio::ip::tcp::socket
Our socket. The `socket` classes are not thread-safe.
Some functions:
* `local_endpoint()` - returns the address, where the socket is connected locally.
* `remote_endpoint()` - returns the remote address, where the socket is connected to.

### Synchronous part
---
Has a method `connect` to connect the socket to the address and port(uses on the client part).

Example of using:

```CXX
using namespace boost::asio;
namespace ip = boost::asio::ip;
io_service service;
ip::tcp::endpoint ep( ip::address::from_string("127.0.0.1"), 80);
ip::tcp::socket sock(service);
sock.open(ip::tcp::v4()); // you'll use this mainly for UDP/ICMP sockets, or for server sockets.
sock.is_open(); // returns true if open
sock.connect(ep);
sock.write_some(buffer("GET /index.html\r\n"));
std::cout << "bytes available " << sock.available() << std::endl;
char buff[1024];
size_t read = sock.read_some(buffer(buff));
sock.shutdown(ip::tcp::socket::shutdown_receive); // disables send, receive operations, or both, starting now.
sock.close(); // Any asynchronous operations on this socket are canceled immediately.
```

Read/Write functions:
* `receive(buffer [, flags])` - Synchronously receives data in the given buffer. Blocks until data is received, or an error.
* `read_some(buffer)` - This function is equivalent to `receive(buffer)`
* `receive_from(buffer, endpoint [, flags])` - Synchronously receives data from a given endpoint into the given buffer.
* `send(buffer [, flags])` - synchronously sends the buffer's data.
* `write_some(buffer)` - This function is equivalent to `send(buffer)`
* `send_to(buffer, endpoint [, flags])` - synchronously sends the buffer's data to a given endpoint.
* `available()` - Returns how many bytes can be read synchronously without blocking.

### Asynchronous part
---
Method `async_connect` uses on the client part. 
Example of using:

```CXX
using namespace boost::asio;
namespace ip = boost::asio::ip;
io_service service;
ip::tcp::endpoint ep( ip::tcp::v4(), 2001);
ip::tcp::socket sock(service);
sock.async_connect(ep, callback_function);
service.run();

void callback_function(const boost::system::error_code &ec) {
    // here we know we connected successfully
    // if ec indicates success
}
```

For asynchronous read/write functions, the signature of the handler is the same:

`void handler(const boost::system::error_code &e, size_t bytes);`

* `async_receive(buffer, [flags,] handler)` - starts the asynchronous `receive` operation of data from the socket.
* `async_read_some(buffer,handler)` - equivalent to `async_receive(buffer, handler)`
* `async_receive_from(buffer, endpoint[, flags], handler)` - starts an asynchronous receive from a specific endpoint.
* `async_send(buffer [, flags], handler)` - This function starts an asynchronous `send` function of the buffer's data.
* `async_write_some(buffer, handler)` - This function is equivalent to `async_send(buffer, handler)`
* `async_send_to(buffer, endpoint, handler)` - starts an asynchronous `send` function of the buffer' data to the specific endpoint.

Example of currect using buffers in asynchronous I/O operations:

```CXX
void on_read(char* ptr, const boost::system::error_code &err, size_t read_bytes) {
    //... some i/o operations
    delete[] ptr;
}
//...
//create  a buffer, and destroy it when the operation completes.
char *buff = new char[512];
sock.async_receive(buffer(buff), boost::bind(on_read, buff, _1, _2));
```

## boost::asio::ip::tcp::acceptor
This object accepts client connections(uses on the server part).
### Synchronous part
---
Method `accept` waits for client connection.
Example of using:
```CXX
using namespace boost::asio;
namespace ip = boost::asio::ip;
io_service service;
ip::tcp::endpoint ep( ip::tcp::v4(), 2001);
ip::tcp::acceptor acc(service, ep);
ip::tcp::socket sock(service);
acc.accept(sock);
```

### Asynchronous part
---

## boost::asio::ip::address
To deal with IP addresses we have the `ip::address`, `ip::address_v4`, `ip::address_v6` classes.

They offer quite a few functions. The most important ones:
* `ip::address(v4_or_v6_address)`  - converts a v4 or v6 address to `ip::address`
* `ip::address::from_string(str)`  - creates an address from str(in v4 or v6 format)
* `ip::address::to_string()`       - returns the friendly represenation pf the address
* `ip::address_v4::broadcast([addr, mask])` - creates a broadcast address
* `ip::address::any()`             - returns an address that represents any address
* `ip::address_v4(v6)::loopback()` - returns the loopback address
* `ip::host_name()` - returns the name of the current host as `string ` datatype

Example of using:

```CXX
ip::address addr = ip::address::from_string("127.0.0.1");

// throws an exception
ip::address addr = ip::address::from_string("www.yandex.ru");
```


## boost::asio::signal_set
This class allows waiting for signals. Example of using:

```CXX
void signal_handler(const boost::system::error_code & err, int sugnal)
{
    //log this, and terminate application
}

using namespace boost::asio;
io_service service;
signal_set sig(service, SIGINT, SIGTERM);
//SIGTERM - software terminate
//SIGINT  - signal interrupt
//SIGSEGV - segment violation
sig.async_wait(signal_handler);
```

## boost::system::error_code
All synchronous functions have overloads that either throw an exception 
or return an error code. Example:

```CXX
sync_func(arg1, arg2 ... argN); // throws
boost::system::error_code ec;
sync_func(arg1, arg2 ... argN, ec); // returns error code
```

# Functions

## The connect functions
These functions connect the socket to an endpoint:
* `connect(socket, begin [, end] [, condition])` - 
   Synchronously connects by trying each endpoint in the sequence `begin` and `end`.
* `async_connect(socket, begin [, end] [, condition], handler)` - 
   Executes the connection asynchronously, and at the end, it calls the completion handler.
   This handler's signature is `void handler(const boost::system::error_code &err, Iterator iterator)`.
   The second parameter passed to the handler is the successfully connected endpoint(or the `end` iterator otherwise).

Example of using:

```CXX
using namespace boost::asio::ip;
tcp::resolver resolver(service);
tcp::resolver iterator iter =
    resolver.resolve(tcp::resolver::query("www.yahoo.com", "80"));
tcp::socket sock(service);
connect(sock. iter);
```

## The read/write functions
These functions read from or write to a stream(which can be a socket, or any other class that behaves like a stream).
* `async_read(stream, buffer [, completion] ,handler)` - 
   Reads from a stream. On completion, handler is called.
   Handler signature is `void handler(const boost::system::error_code &err, size_t bytes`.
   You can optionally specify a `completion` function. The `completion` function is called after each successful `read`.
   It's signature is `size_t completion(const boost::system::error_code &err, size_t bytes_transfered)`.
* `async_write(stream, buffer [, completion], handler)` - asynchronously writes to a stream.
   The meaning of the arguments is similar to `async_read`.
* `read(stream, buffer [, completion])` - synchronously reads from a stream. The meaning of the arguments is similar to `async_read`.
* `write(stream, buffer [, completion])` - synchronously writes to a stream. The meaning of the arguments is similar to `async_read`.

Each `read` or `write` operation will end when one of these conditions occur:
* The supplied buffer is full (for `read`) or all the data in the buffer has been written (for `write`).
* The `completion` function returns 0 (if you supplied one such function).
* An error occurs.

Example of using:

```CXX
// The following code will asynchronously read from the socket until it meets '\n'
io_service service;
ip::tcp::socket sock(service);
char buff[512];
int offset = 0;

size_t up_to_enter(const boost::system::error_code &, size_t bytes) {
    for(size_t i = 0; i < bytes; ++i) {
        if(buff[i + offset] == '\n') { return 0; }
    }
    return 1;
}

void on_read(const boost::system::error_code &, size_t) {}
//...
async_read(sock, buffer(buff), up_to_enter, on_read);
// Boost.Asio comes with a few helper completion functors as well:
// transfer_at_least(n)
// transfer_exactly(n)
// transfer_all()
```

## The read_until/async_read_until functions
These functions read until a condition is met:
* `async_read_until(stream, stream_buffer, delim, handler)` - 
   Starts an asynchronous `read` operation. The `read` operation will stop when a delimeter is met. 
   The delimeter can be any of a character, `std::string` or `boost::regex`.
* `read_until(stream, stream_buffer, delim)` - Perfoms a synchronous `read` operation.
   The parameters' meaning is same as in `async_read_until`.