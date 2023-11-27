import socket

import keyboard

keyboard.add_hotkey("ctrl + shift + p", lambda: print("Hello World!"))

def run_client(server_ip, server_port):
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect((server_ip, server_port))

    try:
        while True:
            # somehow integrate our CLI here
            msg = input("Enter message: ")
            msg = msg + "\n"
            client.send(msg.encode("utf-8")[:1024])

            # do we have parial read/write in python sockets???
            # how do we know the lenght of the buffer?
            response = client.recv(1024)
            response = response.decode("utf-8")

            if response.lower() == "closed":
                break

            print(f"Received: {response}")

    except Exception as e:
        print(f"Error: {e}")
    finally:
        client.close()
        print("Connection to server closed")


run_client("127.0.0.1", 8000)
