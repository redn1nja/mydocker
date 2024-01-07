import socket

#import keyboard

#keyboard.add_hotkey("ctrl + shift + p", lambda: print("Hello World!"))

def run_client(server_ip, server_port):
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect((server_ip, server_port))

    try:
        while True:
            msg = input("mydocker >>> ")
            msg = msg + "\n"

            client.send(msg.encode("utf-8")[:1024])
            response = client.recv(1024)
            response = response.decode("utf-8")
            if response.lower()[0:6] == "closed":
                break

            print(f"Received: {response}")

    except Exception as e:
        print(f"Error: {e}")
    except KeyboardInterrupt as e:
        client.close()
        print("Connection to server closed")
    finally:
        client.close()
        print("Connection to server closed")


run_client("127.0.0.1", 8000)
