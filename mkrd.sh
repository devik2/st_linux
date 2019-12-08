#/bin/bash
F=/tmp/rd.igz2
(cd rfs; find .|cpio -o -H newc --quiet | gzip -9) > $F.tmp
#(cd rfs; find .|cpio -o -H newc --quiet | xz -c -z -C crc32 -4) > $F.tmp
/home/devik/bin/mkimage -A arm -T ramdisk -a 0xc2000000 -n 'MP1 RFS1' -d $F.tmp ${F}
ls -l $F
rm $F.tmp
