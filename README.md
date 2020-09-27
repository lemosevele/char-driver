# char-driver

#Comandos

make -C /lib/modules/$(uname -r)/build M=$PWD modules

sudo insmod ./char_driver.ko

lsmod | grep char

cat /proc/devices

sudo mknod -m 666 /dev/char_driver c 240 0

sudo tail -f /var/log/syslog

cat /dev/char_driver

echo "test" > /dev/char_driver

cat /dev/char_driver

sudo rmmod char_driver
