import enum

class Commands(enum.Enum):
    EXIT = 0
    GET = 1
    LIST = 2
    PUT = 3
    DELETE_FILE = 4
    INFO = 5

class CLI:
    def run(client_socket, file_handler) -> None:
        while True:
            print("\nChoose command:\n\t0. Exit\n\t1. GET <filename>: Request a specific file from the server.\n\t")
            print("2. LIST: Request a list of available files on the server.\n\t")
            print("3. PUT <filename>: Upload a file to the server.\n\t")
            print("4. DELETE <filename>: Request the server to delete a specific file.\n\t")
            print("5. INFO <filename>: Retrieve information about a specific file from the server.\n\t>> ")
            cmd: int = int(input())

            client_socket.send_int_data(cmd)

            if (cmd == Commands.EXIT.value): break

            if (cmd == Commands.GET):
                filename = input("Enter filename to get from the server: ")
                client_socket.send_chunked_data(filename, 4)

                path_to_folder = input("Enter path to folder where you want to save requested file: ")
                path_to_file = path_to_folder + "/" + filename

                requestedFile = client_socket.receive_chunked_data()
                file_handler.create_file(requestedFile, path_to_file)

                break
            elif (cmd == Commands.LIST):
                list_of_files = client_socket.receive_chunked_data()

                print("List of files available on the server:\n")
                for i in range(len(list_of_files)):
                    if (list_of_files[i] == " "):
                        print("\n")
                    else:
                        print(list_of_files[i])
                print("\n")

                break
            elif (cmd == Commands.PUT):
                path_to_file = input("Enter path to file: ")
                filename = input("Enter filename to be created on the server: ")
                client_socket.send_chunked_data(filename, 4)

                buffer = file_handler.get_file_content(path_to_file)
                client_socket.send_chunked_data(buffer, 10)

                print(client_socket.receive_confirmation_from_server() + "\n")
                break
            elif (cmd == Commands.DELETE_FILE):
                filename = input("Enter filename to delete from the server: ")
                client_socket.send_chunked_data(filename, 4)
                print(client_socket.receive_confirmation_from_server() + "\n")
                break
            elif (cmd == Commands.INFO):
                filename = input("Enter filename to get info about from the server: ")
                client_socket.send_chunked_data(filename, 4)

                file_info = client_socket.receive_chunked_data()
                splitted_file_info = file_info.split(";")

                print("Size       : " + splitted_file_info[0] + " bytes\n")
                print("Created    : " + splitted_file_info[1])
                print("Modified   : " + splitted_file_info[2])

                break
