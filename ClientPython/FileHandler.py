class FileHandler:
    def get_file_content(self, path_to_file):
        try:
            with open(path_to_file, 'rb') as file:
                buffer = file.read()
            return buffer
        except FileNotFoundError:
            print("Error while reading the file: File not found.")
            return None
        except Exception as e:
            print(f"Error while reading the file: {e}")
            return None

    def create_file(buffer, path_to_file) -> int:
        try:
            with open(path_to_file, 'w') as file:
                file.write(buffer)
            return 0
        except Exception as e:
            print(f"Error while creating the file: {e}")
            return -1