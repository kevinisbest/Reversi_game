# Reversi_game
{基於在cygwin上的黑白棋程式}


1.	如果遇到亂碼，請在右鍵options裡text選big5編碼
2.	如果遇到畫面一堆warning，請忽視，並不是error
3.	如果畫面太小，請ctrl+滾輪上來放大介面
4.	Sever連線步驟
  	gcc s.c -o sever自己想的檔名
  	./ sever
  	等待連線
5.	Client連線步驟
  	gcc c.c -o client自己想的檔名
  	./ client
    連線成功
6.	一開始是sever先動，棋子是◆
    client後動，棋子是◇
    棋盤為◎
7.	若是覺得棋盤太小，可直接去sever與client的程式碼改size變數的大小，我們可以直接變動。 

