#!/bin/bash -xe

appnum=$1
case ${appnum} in
1|2)
  ;;
*)
  echo ERROR: app number must be 1 or 2 1>&2
  exit 1
  ;;
esac

make APP=${appnum}

rm -f ../bin/upgrade/user$1.bin

cd .output/eagle/debug/image/

xt-objcopy --only-section .text -O binary eagle.app.v6.out eagle.app.v6.text.bin
xt-objcopy --only-section .data -O binary eagle.app.v6.out eagle.app.v6.data.bin
xt-objcopy --only-section .rodata -O binary eagle.app.v6.out eagle.app.v6.rodata.bin
xt-objcopy --only-section .irom0.text -O binary eagle.app.v6.out eagle.app.v6.irom0text.bin

../../../../../tools/gen_appbin.py eagle.app.v6.out v6

../../../../../tools/gen_flashbin.py eagle.app.v6.flash.bin eagle.app.v6.irom0text.bin

cp eagle.app.flash.bin user${appnum}.bin
mkdir -p ../../../../../bin/upgrade/
cp user${appnum}.bin ../../../../../bin/upgrade/

cd ../../../../../
