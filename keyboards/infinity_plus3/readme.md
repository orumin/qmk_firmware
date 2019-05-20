# infinity_plus3

静電容量無接点方式を搭載した、名刺サイズのキーボードです。  
下側の3つはCherryMX互換スイッチ、  
上の1つはVarmilo Sakuraに対応しています。  
Varmilo SakuraスイッチはMX軸の静電容量スイッチです。  
いい感じに入手してください  
![Varmilo Sakura](https://geekhack.org/index.php?topic=94239.0)



This keyboard is Japanese namecard size(55x91mm) keyboard.

infinity_plus3 has 3 Cherry-MX switch and 1 Varmilo Sakura Switch.

[Varmilo Sakura Switch](https://geekhack.org/index.php?topic=94239.0)

[infinity_plus3](https://twitter.com/sirojake/status/1129773678005239809)




Keyboard Maintainer: [ginjake](https://twitter.com/sirojake)  


Make example for this keyboard (after setting up your build environment):

    make infinity_plus3/rev1:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).


# ビルドガイド
### 必要なもの
・Cherry MX互換スイッチ x3  
・Varmilo Sakura スイッチ x 1  
・タクトスイッチ x1  
・ProMicro x 1  
・コンスルー x 2  
・オペアンプＬＭ３５８Ｎ x 1  
・2.2kΩ抵抗 x 3 (1/6Wが理想)  
・2.2MΩ抵抗 x 3 (1/6Wが理想)  
・SK6812MINI  
・キーキャップ x 4


### 部品の取り付け
まず、こんな感じで部品を取り付けます  
[infinity_plus3](https://user-images.githubusercontent.com/16838187/58027207-1a953980-7b53-11e9-8b7e-87a39f1bbc1a.png)
  
[完成後](https://pbs.twimg.com/media/D67BE1MUIAADaWr.jpg:large)
  

2.2MΩ抵抗は直列に3本繋がっています。  
ようするに6.6MΩですが、この値が最適かは分かりません。  
2.2MΩ、4.4MΩ、6.6MΩ、10MΩで実験しましたが、抵抗が増すほど細かな検知が可能になる代わりに、静電気による誤差が増えてしまいます。  
抵抗やファームに手を入れれば、さらなる精度が出るかもしれません。  


#### ケースの印刷
次ケースを印刷します。  
基板+ゴム足だけだと、机からの静電気により誤差が出てしまう恐れがあります。  
ケースのファイルは[こちら](https://github.com/ginjake/infinity_plus3/blob/master/case/infinity_plus3_2.stl)にありますが、少しやっつけです。  
91mm×55mmで作っているので不満な方はいい感じに作ってください。  
PLAでテストしたので、他の素材ではファームに手を加えて閾値をいじる必要があるかもしれません。  

#### ゴムシート
基板とケースの間にゴムシートを入れます。  
無くても動きますが、あったほうが安定しました。  
使わない場合は、閾値の調整が必要かもしれません。  


### 閾値のチューニング
場合によっては閾値をいじる必要があります。  
抵抗やゴムシート、ケースの材質だけでなく、キーキャップの材質や形状も影響するようです。  
keymap.cの  
`if (average > 41) {　`
    や

`#define PERIOD 70` を編集していい感じにします。  
qmk_toolboxを使ってaverageの値を監視しながら調整していくのがおすすめです。 

基板のデータは
https://github.com/ginjake/infinity_plus3
にあります
