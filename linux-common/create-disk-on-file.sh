set -x

sudo dd if=/dev/zero of=/root/diskimage bs=1M count=10240
sudo mkfs.ext4 /root/diskimage

sudo losetup -d /dev/loop0
sudo losetup /dev/loop0 /root/diskimage

echo "Don't forget to add into /etc/rc.local!"
#sudo echo -e "losetup /dev/loop0 /root/diskimage\n\n$(cat /etc/rc.local)" > /etc/rc.local

