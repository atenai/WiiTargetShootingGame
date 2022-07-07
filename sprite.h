//=======================================================================================
//
//    [ sprite.h ] スプライト描画モジュール
//
//	このファイルへ関数を追加する
//=======================================================================================

#ifndef _SPRITE_H_
#define _SPRITE_H_


//----- インクルードファイル -----

#include <revolution.h>


//----- プロトタイプ宣言 -----

//=======================================================================================
// スプライト描画準備関数
//
// SpriteのDraw関数を呼ぶ前にコールする
//
// ※他のSetup関数が呼ばれた後、SpriteのDraw関数を呼ぶ場合には再度コールすること
//=======================================================================================
void SpriteSetup(void);


//=======================================================================================
// スプライト色設定関数
//
// スプライト色を指定する
// この関数が呼ばれた後のスプライト画像はすべてここで指定した色との乗算合成になる
//
// r ... 赤要素(0-255)
// g ... 緑要素(0-255)
// b ... 青要素(0-255)
//=======================================================================================
void SpriteSetColor(u8 r, u8 g, u8 b, u8 a);


//=======================================================================================
// スプライト描画関数
//
// pTex   ... テクスチャオブジェクトの先頭アドレス
// dx, dy ... スプライトの左上座標
// dw, dh ... スプライトの幅と高さ(テクスチャの切り取り幅と高さ)
// tx, ty ... テクスチャの切り取り左上座標
//=======================================================================================
void SpriteDraw(GXTexObj* pTex, float dx, float dy, int dw, int dh, int tx, int ty);




#endif // _SPRITE_H_
