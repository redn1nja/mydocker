import socket
import sys

import keyboard
def on_press(client):
    global listen_mode  # Declare that we are using the global variable
    listen_mode = False
    if not listen_mode:
        client.send("detach".encode("utf-8")[:1024])
        receive_message(client)

def cat(client):
    client.settimeout(1)  # 1 second timeout
    while True:
        try:
            response = client.recv(1024)
            response = response.decode("utf-8")
            print(response)
            if (len(response) < 1024 and response[-1] == "\n") or len(response) == 0:
                break
        except socket.timeout:
            break


def receive_message(client):
    try:
        while True:
            msg = input("mydocker >>> ")
            msg = msg + "\n"

            client.send(msg.encode("utf-8")[:1024])
            response = client.recv(1024)
            response = response.decode("utf-8")
            if response.lower()[0:6] == "closed":
                break
            if msg.lower().startswith("listen"):
                global listen_mode  # Declare that we are using the global variable
                listen_mode = True
                print("Listening to container")
                if "--input" in msg:
                    print("Listening to container with input")
                    listen_to_container(client, True)
                else:
                    listen_to_container(client, False)

            print(f"Received: {response}")

    except Exception as e:
        print(f"Error: {e}")
    except KeyboardInterrupt as e:
        client.close()
        print("Connection to server closed")
    finally:
        client.close()
        print("Connection to server closed")


def listen_to_container(client, has_input):
    global listen_mode  # Declare that we are using the global variable

    while listen_mode:
            if has_input:
                msg = input("Input for container >>> ")
                msg = msg + "\n"
                client.send(msg.encode("utf-8")[:1024])
            cat(client)



def run_client(server_ip, server_port):
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect((server_ip, server_port))
    keyboard.add_hotkey("ctrl + shift + p", lambda: on_press(client))
    receive_message(client)


listen_mode = False
run_client("127.0.0.1", int(sys.argv[1]))
