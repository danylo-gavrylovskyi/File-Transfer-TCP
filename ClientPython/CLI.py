import enum

class Commands(enum.Enum):
    EXIT = 0
    GET = 1
    LIST = 2
    PUT = 3
    DELETE_FILE = 4
    INFO = 5

class CLI:
    def run(self, client_socket, file_handler) -> None:
        while True:
            print("\nChoose command:\n\t0. Exit\n\t1. GET <filename>: Request a specific file from the server.")
            print("\t2. LIST: Request a list of available files on the server.")
            print("\t3. PUT <filename>: Upload a file to the server.")
            print("\t4. DELETE <filename>: Request the server to delete a specific file.")
            print("\t5. INFO <filename>: Retrieve information about a specific file from the server.\n\t>> ", end='')
            cmd: int = int(input())

            client_socket.send_int_data(cmd)

            if (cmd == Commands.EXIT.value): break

            if (cmd == Commands.GET.value):
                filename = input("Enter filename to get from the server: ")
                client_socket.send_chunked_data(filename.encode(), 4)

                path_to_folder = input("Enter path to folder where you want to save requested file: ")
                path_to_file = path_to_folder + "/" + filename

                requestedFile = client_socket.receive_chunked_data()
                file_handler.create_file(requestedFile.decode(), path_to_file)
            elif (cmd == Commands.LIST.value):
                list_of_files = client_socket.receive_chunked_data().decode()

                print("List of files available on the server:")
                for i in range(len(list_of_files)):
                    if (list_of_files[i] == " "):
                        print("")
                    else:
                        print(list_of_files[i], end="")
            elif (cmd == Commands.PUT.value):
                path_to_file = input("Enter path to file: ")
                filename = input("Enter filename to be created on the server: ")
                client_socket.send_chunked_data(filename.encode(), 4)

                buffer = file_handler.get_file_content(path_to_file)
                client_socket.send_chunked_data(buffer, 1000000) # ???

                print(client_socket.receive_confirmation_from_server() + "\n")
            elif (cmd == Commands.DELETE_FILE.value):
                filename = input("Enter filename to delete from the server: ")
                client_socket.send_chunked_data(filename.encode(), 4)
                print(client_socket.receive_confirmation_from_server())
            elif (cmd == Commands.INFO.value):
                filename = input("Enter filename to get info about from the server: ")
                client_socket.send_chunked_data(filename.encode(), 4)

                file_info = client_socket.receive_chunked_data().decode()
                splitted_file_info = file_info.split(";")

                print("Size       : " + splitted_file_info[0] + " bytes")
                print("Created    : " + splitted_file_info[1], end="")
                print("Modified   : " + splitted_file_info[2], end="")
