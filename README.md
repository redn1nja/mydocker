# mydocker

Authors (team): <mark>
- [Ostap Seryvko](https://github.com/redn1nja)
- [Anastasiia Beheni](https://github.com/beheni)
- [Olesia Omelchuk](https://github.com/OlesiaOmelchuk)
- [Sofiia Folvarochna](https://github.com/sofiiafolv)
</mark><br>

## Prerequisites
<mark>
g++, cmake, boost <br>
Python: keyboard, sys, socket <br>
</mark>

### Compilation
```./compile.sh```

### Usage example
1. **Run docker daemon** (```./mydocker <port>```):\
  ```./bin/mydocker 8000```
2. **Start client** (```python3 test_socket/client.py <port>```):\
  ```python3 test_socket/client.py 8000```
3. **Communication loop**\
   Specify the container in the dockerfile (.json). For example:
   ```
   {
    "bin" : "/bin/sh",
    "args" : [],
    "mount_points" : ["/tmp"],
    "mem_limit": 200,
    "pids_limit": 20
   }
   ```

   ```
   mydocker >>> create dockerfiles/mydockerfile.json
   mydocker >>> run 0
   mydocker >>> listen 0
   ```

### Communication with docker daemon
- create container from docker file:
  ```
  create <path-to-dockerfile>
  ```
- run the container:
  ```
  run <index>
  ```
- start listening to the container. If the ```--input``` flag is specified - the program requires input; otherwise, it doesn't:
  ```
  listen <index> [--input]
  ```
- detach from the container the client is currently listening:
  ```
  detach
  ```
- print the information about the existing containers:
  ```
  list_containers
  ```
- kill the container:
  ```
  kill_container <index>
  ```
- stop the client:
  ```
  exit
  ```

## Implementation details
[mydocker](https://drive.google.com/file/d/1XDFBG0OYWR_YkqHFdfZ5B06BbbFs3m12/view?usp=sharing) <br> 
![mydocker (1)](https://github.com/redn1nja/mydocker/assets/92575534/34fa4ff1-08c4-4157-8d82-aa46e508bb0e)

