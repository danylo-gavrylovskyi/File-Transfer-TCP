from CLI import CLI
from Socket import Socket
from FileHandler import FileHandler

def main():
    server_ip = "127.0.0.1"
    port = 12345

    cli = CLI()
    file_handler = FileHandler()

    client_socket = Socket()
    client_socket.connect(server_ip, port)
    cli.run(client_socket, file_handler)
    client_socket.disconnect()

if __name__ == "__main__":
    main()