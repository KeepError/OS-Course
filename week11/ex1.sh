sudo fallocate -l 50M lofs.img
sudo losetup -f lofs.img
LOPATH=$(losetup -a | grep "lofs.img" | grep -o "/dev/loop[0-9]*")
sudo mkfs.ext4 $LOPATH
mkdir lofsdisk
sudo mount $LOPATH ./lofsdisk
