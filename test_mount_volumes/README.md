# BIND MOUNTS AND VOLUMES

## BIND MOUNTS

Bind mount is a type of mounting where not a filesystem is mounted but a directory from one location to another location. <br>
Requires the __CAP_SYS_ADMIN__ capability of the user. <br>  

### Example
```bash
cd ..
mkdir -p build && cd build/
cmake .. && make

mkdir -p /tmp/test_mount_src/
touch /tmp/test_mount_src/test_file
mkdir -p /tmp/test_mount_dest/
sudo ./volumes /tmp/test_mount_src/ /tmp/test_mount_dest/
```
Now you can see the file `/tmp/test_mount_src/test_file` in `/tmp/test_mount_dest/` <br>
Sudo here is required because of the __CAP_SYS_ADMIN__ capability. In the future, a specific user may be created which will manage the mounts. <br>

Mounts can be unmounted by the following command:
```bash
sudo umount /tmp/test_mount_dest/
```

## VOLUMES

Volume is a part of default Docker functionality which uses bind mounts but also provides exclusive access to the content of the volumes to containers by default. <br>
Access to volumes to user is provided by the Docker. <br>

Multiple containers may use the same volume in order to share data between them. <br>