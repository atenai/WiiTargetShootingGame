//=======================================================================================
//
//    [ sprite.c ] スプライト描画モジュール
//
//		このファイルへ関数を作成する
//=======================================================================================


//----- インクルードファイル -----

#include "sprite.h"


//----- グローバル変数定義 -----

static u8 spriteR = 255; // スプライトの色
static u8 spriteG = 255;
static u8 spriteB = 255;
static u8 spriteA = 255;
	/*
	int Color1=0;
	int Color2=0;
	int Color3=0;
	int Plus=0;
	int Plus2=0;
	int Minus=0;
	int Minus2=0;
	int Minus3=0;
	int Yuru=4;	 
*/

//----- 関数定義 -----

//=======================================================================================
// スプライト描画準備関数
//
// SpriteのDraw関数を呼ぶ前にコールする
//
// ※他のSetup関数が呼ばれた後、SpriteのDraw関数を呼ぶ場合には再度コールすること
//=======================================================================================
void SpriteSetup(void)
{
		GXClearVtxDesc();
		GXSetVtxDesc(GX_VA_POS,GX_DIRECT);
		GXSetVtxDesc(GX_VA_CLR0,GX_DIRECT);
		GXSetVtxDesc(GX_VA_TEX0,GX_DIRECT);
		
		
		GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_POS,GX_POS_XYZ,GX_F32,0);
		GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_CLR0,GX_CLR_RGB,GX_RGBA8,0);
		GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_TEX0,GX_TEX_ST,GX_F32,0);//αなしカラー

		//======Wiiに色を使う設定を行う（詳細後日）

		// 使用するTEVステージ数の設定
		GXSetNumTevStages(1); // 1つ
		    
		// カラーチャンネル数の設定
		GXSetNumChans(1); // 1つ
		    
		// 利用可能にするテクスチャ座標数の設定
	   	GXSetNumTexGens(1); 
			
		// TEVが使用するテクスチャーカラーとラスタライズカラーの設定
		GXSetTevOrder(GX_TEVSTAGE0,     // TEVステージ0の設定
	    	    	  GX_TEXCOORD0, // テクスチャ座標は使わない
	    	          GX_TEXMAP0, 	// テクスチャは使用しない
	    	          GX_COLOR0A0);		// カラーチャンネル0・アルファチャンネル0を使用
	    	          
	    	          
	  	//TEVが上の要素をどのように合成するかを設定する
	  	GXSetTevOp(GX_TEVSTAGE0,GX_MODULATE);	//TEVステージ0を設定である
	  											//テクスチャカラーとテクスチャアルファを出力
	  	//ハードウェア設定追加
	  	GXSetBlendMode(GX_BM_BLEND,GX_BL_SRCALPHA,GX_BL_INVSRCALPHA,GX_LO_CLEAR);

}


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
void SpriteSetColor(u8 r, u8 g, u8 b, u8 a) 
{
	spriteR = r;
	spriteG = g;
	spriteB = b;
	spriteA = a;
}


//=======================================================================================
// スプライト描画関数
//
// pTex   ... テクスチャオブジェクトの先頭アドレス
// dx, dy ... スプライトの左上座標
// dw, dh ... スプライトの幅と高さ(テクスチャの切り取り幅と高さ)
// tx, ty ... テクスチャの切り取り左上座標（切り取り開始地点）
//=======================================================================================
//tw 元のテクスチャの幅
//th 元のテクスチャの高さ
//tcx 
//=======================================================================================
void SpriteDraw(GXTexObj* pTex, float dx, float dy, int dw, int dh, int tx, int ty)
{
		
	u16 tw=GXGetTexObjWidth(pTex);//テクスチャの幅をいじる//pTex=元の画像の幅を調べ、取得する
	u16 th=GXGetTexObjHeight(pTex);//テクスチャの高さをいじる//pTex=元の画像の幅を調べ、取得する
//	float tcx=tx/(float)tw;
//	float tcy=ty/(float)th;
	float tcx=tx/(float)tw;//0÷テクスチャ幅=テクスチャのx表示開始位置
	float tcy=ty/(float)th;//0÷テクスチャ高さ=テクスチャのy表示開始位置
	
	//float tlx=(tx+(float)dw)/(float)tw;
//	float tlx=(tx+(float)500)/(float)tw;
	float tlx=(tx+(float)tw)/(float)tw;//(テクスチャのx切り取り開始場所+テクスチャ幅)÷テクスチャ幅
	//float tly=(ty+(float)dh)/(float)th;
//	float tly=(ty+(float)500)/(float)th;
	float tly=(ty+(float)th)/(float)th;//(テクスチャのy切り取り開始場所+テクスチャ高さ)÷テクスチャ高さ
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	
	
	
			

	
	   	 //テクスチャマップ0番にテクスチャを設定
	  	//※「boy」テクスチャをセット
	  	//テクスチャ(テクスチャの幅と高さを取得,テクスチャの何番目を使うか指定)
	  	GXLoadTexObj(pTex,GX_TEXMAP0); 
	  	/*                   
		if(Color1<=255&&Minus==0)
		{
			Color1=Color1+20;
		}
		if(Color1>255&&Minus==0)
		{
			Color1=255;
			Plus=1;
		}		
		
		if(Color2<=255&&Minus==0&&Plus==1)
		{
			Color2=Color2+30;
		}
		if(Color2>255&&Minus==0)
		{
			Color2=255;
			Plus2=1;
		}		
		
		if(Color3<=255&&Minus==0&&Plus2==1)
		{
			Color3=Color3+40;
		}
		if(Color3>255&&Minus==0)
		{
			Color3=255;
			Minus=1;
		}		
		if(Color1>=100&&Minus==1)
		{
			Color1=Color1-40;
		}			
		if(Color1<100&&Minus==1)
		{
			Color1=100;
			Minus2=1;
		}
		if(Color2>=100&&Minus2==1)
		{
			Color2=Color2-30;
		}		
		if(Color2<100&&Minus==1)
		{
			Color2=100;
			Minus3=1;
		}		
		if(Color3>=100&&Minus3==1)
		{
			Color3=Color3-20;
		}
		if(Color3<100&&Minus==1)
		{
			Color3=100;
			Minus=0;
		}
		Yuru=Yuru*-1;
		*/
		//プリミティプ頂点情報登録開始
			GXBegin(GX_TRIANGLEFAN,GX_VTXFMT0,4);//点を描画
				//点1
				GXPosition3f32(dx,dy,0.0f);//座標
				GXColor4u8(255,255,255,255);//色
				GXTexCoord2f32(tcx,tcy);
				//点2
				GXPosition3f32(dx+dw,dy,0.0f);//座標
				GXColor4u8(255,255,255,255);//色
				GXTexCoord2f32(tlx,tcy);
				//点3
				GXPosition3f32(dx+dw,dy+dh,0.0f);//座標
				GXColor4u8(255,255,255,255);//色
				GXTexCoord2f32(tlx,tly);
				//点4
				GXPosition3f32(dx,dy+dh,0.0f);//座標	
				GXColor4u8(255,255,255,255);//色
				GXTexCoord2f32(tcx,tly);

			//プリミティプ頂点情報登録終了
			GXEnd();
////////////////////////////////////////////////////////////////////////////////////////////////////			
			
					//※「りんご」テクスチャをセット
					//テクスチャ(テクスチャの幅と高さを取得,テクスチャの何番目を使うか指定)
					GXLoadTexObj(pTex,GX_TEXMAP3); 
	  
		//プリミティプ頂点情報登録開始
			GXBegin(GX_TRIANGLEFAN,GX_VTXFMT0,4);//点を描画
				//点1
				GXPosition3f32(dx,dy,0.0f);//座標
				GXColor4u8(255,255,255,255);//色
				GXTexCoord2f32(tcx,tcy);
				//点2
				GXPosition3f32(dx+dw,dy,0.0f);//座標
				GXColor4u8(255,255,255,255);//色
				GXTexCoord2f32(tlx,tcy);
				//点3
				GXPosition3f32(dx+dw,dy+dh,0.0f);//座標
				GXColor4u8(255,255,255,255);//色
				GXTexCoord2f32(tlx,tly);
				//点4
				GXPosition3f32(dx,dy+dh,0.0f);//座標	
				GXColor4u8(255,255,255,255);//色
				GXTexCoord2f32(tcx,tly);

			//プリミティプ頂点情報登録終了
			GXEnd();
			
////////////////////////////////////////////////////////////////////////////////////////////////////////			
				//※「背景」テクスチャをセット
					//テクスチャ(テクスチャの幅と高さを取得,テクスチャの何番目を使うか指定)
					GXLoadTexObj(pTex,GX_TEXMAP2); 
						//プリミティブ頂点情報登録終了
	//	GXEnd();

}


	
	  /*
		//プリミティプ頂点情報登録開始
			GXBegin(GX_TRIANGLEFAN,GX_VTXFMT0,4);//点を描画
				//点1
				GXPosition3f32(dx,dy,0.0f);//座標
				GXColor4u8(255,255,255,255);//色
				GXTexCoord2f32(tcx,tcy);//(左上の点)
				//点2
				GXPosition3f32(dx+dw,dy,0.0f);//座標
				GXColor4u8(255,255,255,255);//色
				GXTexCoord2f32(tlx,tcy);//(右上の点)
				//点3
				GXPosition3f32(dx+dw,dy+dh,0.0f);//座標
				GXColor4u8(255,255,255,255);//色
				GXTexCoord2f32(tlx,tly);//(右下の点)
				//点4
				GXPosition3f32(dx,dy+dh,0.0f);//座標	
				GXColor4u8(255,255,255,255);//色
				GXTexCoord2f32(tcx,tly);//(左下の点)

			//プリミティプ頂点情報登録終了
			GXEnd();
		
				//プリミティブ頂点情報登録開始
		//プリミティブタイプと頂点フォーマットと頂点数に注意
	GXBegin(GX_QUADS,GX_VTXFMT0,4);
	//プリミティブ頂点セット開始
	GXPosition3f32(0.0f,0.0f,0.0f);//頂点座標　頂点が先　　　　　　//位置
	GXColor4u8(255,255,255,255); //頂点カラー
	GXTexCoord2f32(0.0f,0.0f);//テクスチャ座標　テクスチャ座標は後
	
	GXPosition3f32(900.0f,0.0f,0.0f);//頂点座標
	GXColor4u8(255,255,255,255); //頂点カラー
	GXTexCoord2f32(1.0f,0.0f);//テクスチャ座標
	//画面のY座標は480が限界
	GXPosition3f32(900.0f,480.0f,0.0f);//頂点座標　頂点が先
	GXColor4u8(255,255,255,255); //頂点カラー
	GXTexCoord2f32(1.0f,1.0f);//テクスチャ座標　テクスチャ座標は後
	
	GXPosition3f32(000.0f,480.0f,0.0f);//頂点座標
	GXColor4u8(255,255,255,255); //頂点カラー
	GXTexCoord2f32(0.0f,1.0f);//テクスチャ座標
	
	
	*/

