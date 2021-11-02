dd if=/dev/urandom of=lofs.img bs=60MB count=1
sudo losetup -fP lofs.img
mkfs.ext4 lofs.img
mkdir lofsdisk
sudo mount -o loop /dev/loop0 lofsdisk
df -hP lofsdisk
