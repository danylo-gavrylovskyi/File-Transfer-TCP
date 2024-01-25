import socket
import struct
class Socket:
    def connect(self, server_ip: str, port: int) -> int:
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.client_socket.connect((server_ip, port))
        return 0

    def disconnect(self) -> int:
        self.client_socket.close()
        return 0
    
    def send_int_data(self, num: int) -> int:
        self.client_socket.send(struct.pack('<I', num))
        return 0
        
    def send_chunked_data(self, data, chunk_size) -> int:
        total_size = len(data)

        self.client_socket.send(struct.pack('<I', total_size))
        self.client_socket.send(struct.pack('<I', chunk_size))
        
        total_sent = 0

        while total_sent < total_size:
            current_chunk_size = min(chunk_size, total_size - total_sent)
            chunk_data = data[total_sent:total_sent + current_chunk_size]
            self.client_socket.send(chunk_data)
            total_sent += current_chunk_size

        return 0
    
    def receive_chunked_data(self):
        total_size: int = struct.unpack("<I", self.client_socket.recv(4))[0]
        chunk_size: int = struct.unpack("<I", self.client_socket.recv(4))[0]

        assembled_data = bytearray()

        total_received: int = 0
        while total_received < total_size:
            buffer = self.client_socket.recv(chunk_size)
            if not buffer:
                print("Error in receiving chunked data.")
                break

            assembled_data.extend(buffer)
            total_received += len(buffer)

        return bytes(assembled_data)
    
    def receive_confirmation_from_server(self):
        total_size: int = struct.unpack("<I", self.client_socket.recv(4))[0]

        buffer = self.client_socket.recv(total_size)
        if not buffer:
            print("Error in receiving message from server.")
            return None
        

        return buffer.decode('utf-8')
