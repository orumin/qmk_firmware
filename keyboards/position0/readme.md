# namecard2x4

静電容量無接点方式専用のキーボードです。
全部で26キーです。
2つのマイコンを利用しているため、13+13みたいなイメージです。
対応スイッチはVarmilo sakura,Varmilo Rose,Varmilo Greenのみです。
静電容量の検知にＡＴＭＥＧＡ３２８Ｐを使っています。
AVRライタを用いて、そちらにも別のファームを書き込む必要があります。

This keyboard is 26key only Varmilo sakura or Varmilo Rose or Varmilo Green Switch.
Those switch are Electrostatic-Capacitive technology as Topre,

ProMicro and using two ＡＴＭＥＧＡ３２８Ｐ.
Pro Micro is this QMK firmware.
ATMEGA328P is other firmware.
source is this page.


![position0](https://pbs.twimg.com/media/EKnLricUcAAowb0?format=jpg&name=4096x4096)




Keyboard Maintainer: [sirojake](https://github.com/ginjake)  


Make example for this keyboard (after setting up your build environment):

    make position0/rev1:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
