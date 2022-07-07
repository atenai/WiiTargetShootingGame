//=======================================================================================
//
//    [ primitive.c ] 図形描画モジュール
//
//	このファイルに関数を作成する
//=======================================================================================


//----- インクルードファイル -----

#include "primitive.h"
#include <math.h>


//----- 定数定義 -----

#define PI (3.141592654f) // π


//----- グローバル変数定義 -----

static u8 primitiveR = 255; // 図形の色
static u8 primitiveG = 255;
static u8 primitiveB = 255;


//----- 関数定義 -----

//=======================================================================================
// 図形描画準備関数
//
// PrimitiveのDraw関数を呼ぶ前にコールする
//
// ※他のSetup関数が呼ばれた後、PrimitiveのDraw関数を呼ぶ場合には再度コールすること
//=======================================================================================
void PrimitiveSetup(void) 
{
		GXClearVtxDesc();
		GXSetVtxDesc(GX_VA_POS,GX_DIRECT);
		GXSetVtxDesc(GX_VA_CLR0,GX_DIRECT);//カラー
		
		GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_POS,GX_POS_XYZ,GX_F32,0);	
		GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_CLR0,GX_CLR_RGB,GX_RGB8,0);//カラー
	//======Wiiに色を使う設定を行う（詳細後日）

	// 使用するTEVステージ数の設定
	GXSetNumTevStages(1); // 1つ
	    
	// カラーチャンネル数の設定
	GXSetNumChans(1); // 1つ
	    
	// 利用可能にするテクスチャ座標数の設定
    	GXSetNumTexGens(0); // つかわない
		
	// TEVで使用するテクスチャーカラーとラスタライズカラーの設定
	GXSetTevOrder(GX_TEVSTAGE0,     // TEVステージ0の設定
    	    	  GX_TEXCOORD_NULL, // テクスチャ座標は使わない
    	          GX_TEX_DISABLE, 	// テクスチャは使用しない
    	          GX_COLOR0A0);		// カラーチャンネル0・アルファチャンネル0を使用
  
  	// TEVの簡易カラー合成設定
    	GXSetTevOp(GX_TEVSTAGE0, // TEVステージ0の設定 
    	           GX_PASSCLR);  // 前ステージのカラーとアルファを出力
    	                         // ※前ステージが存在しないのでラスタライズカラー（ポリゴンカラー）が使用される

}


//=======================================================================================
// 図形色設定関数
//
// 図形色を指定する
// この関数が呼ばれた後の図形はすべてここで指定した色になる
//
// r ... 赤要素(0-255)
// g ... 緑要素(0-255)
// b ... 青要素(0-255)
//=======================================================================================
void PrimitiveSetColor(u8 r, u8 g, u8 b) 
{
	primitiveR = r;
	primitiveG = g;
	primitiveB = b;
}



//=======================================================================================
// 点の描画
//
// x, y ... 点の描画座標
//=======================================================================================
void PrimitiveDrawPoint(float x, float y)
{
/*
	GXBegin(GX_POINTS, GX_VTXFMT0, 1);
	GXPosition3f32(x, y, 0.0f);
	GXColor3u8(primitiveR, primitiveG, primitiveB); 
	GXEnd();
	*/
	
		//プリミティブ頂点情報登録開始
		GXBegin(GX_POINTS,GX_VTXFMT0,1);//点を描画(1つ)
		//例
		//GXPosition3f32(x軸,y軸);
		//点1
		GXPosition3f32(x,y,0.0f);
		//GXColor3u8(赤,緑,青);//カラー
		GXColor3u8(255,0,0);//カラー
		GXEnd();//表示終了
}


//=======================================================================================
// 線の描画
//
// x0, y0 ... 線の始点座標
// x1, y1 ... 線の終点座標
//=======================================================================================
void PrimitiveDrawLine(float x0, float y0, float x1, float y1)
{
/*
	GXBegin(GX_LINES, GX_VTXFMT0, 2);
	GXPosition3f32(x0, y0, 0.0f);
	GXColor3u8(primitiveR, primitiveG, primitiveB); 
	GXPosition3f32(x1, y1, 0.0f);
	GXColor3u8(primitiveR, primitiveG, primitiveB); 
	GXEnd();
*/
//プリミティブ頂点情報登録開始
		GXBegin(GX_LINES,GX_VTXFMT0,2);//線を描画(1本分)
		//線その1(始点)
			GXPosition3f32(x0,y0,0.0f);//座標
			//例
			//GXColor3u8(赤,緑,青);//カラー
		GXColor3u8(255,0,255);//カラー
		//線その1(終点)
			GXPosition3f32(x1,y1,0.0f);//座標
			//例
			//GXColor3u8(赤,緑,青);//カラー
	GXColor3u8(255,0,255);//カラー

		GXEnd();
}




//=======================================================================================
// 四角の描画
//
// x, y ... 四角の左上座標
// w, h ... 四角の幅と高さ
//=======================================================================================
void PrimitiveDrawRectangle(float x, float y, float w, float h)
{
/*
	float x0=x+w;
	float y0=y+h;
	GXBegin(GX_LINES, GX_VTXFMT0, 8);
	GXPosition3f32(x, y, 0.0f);
	GXColor3u8(primitiveR, primitiveG, primitiveB); 
	GXPosition3f32(x0, y, 0.0f);
	GXColor3u8(primitiveR, primitiveG, primitiveB); 
	GXPosition3f32(x0, y, 0.0f);
	GXColor3u8(primitiveR, primitiveG, primitiveB);
	GXPosition3f32(x0, y0, 0.0f);
	GXColor3u8(primitiveR, primitiveG, primitiveB); 
	GXPosition3f32(x0, y0, 0.0f);
	GXColor3u8(primitiveR, primitiveG, primitiveB); 
	GXPosition3f32(x, y0, 0.0f);
	GXColor3u8(primitiveR, primitiveG, primitiveB);
	GXPosition3f32(x, y0, 0.0f);
	GXColor3u8(primitiveR, primitiveG, primitiveB);
	GXPosition3f32(x, y, 0.0f);
	GXColor3u8(primitiveR, primitiveG, primitiveB);	
	GXEnd();

}

void PrimitiveDrawCircle(float x, float y, float r)
{
	float count=360.f;
			//プリティプ頂点情報登録開始
			GXBegin(GX_TRIANGLEFAN,GX_VTXFMT0,360);//点を描画
		while(count>0)
		{
				GXPosition3f32(x+r*cosf(count),y-r*sinf(count),0.0f);//座標
				GXColor3u8(255, 0, 0);
				count--;			
		}					
		//プリティプ頂点情報登録終了
		GXEnd();
		*/
	//プリミティブ頂点情報登録開始
		GXBegin(GX_LINESTRIP,GX_VTXFMT0,5);//
			//点その1
			GXPosition3f32(x,y,0.0f);//座標
			//GXColor3u8(赤,緑,青);//カラー
		GXColor3u8(255,0,255);//カラー
			//点その2
			GXPosition3f32(x+w,y,0.0f);//座標
			//GXColor3u8(赤,緑,青);//カラー
		GXColor3u8(255,0,255);//カラー
			//点その3
			GXPosition3f32(x+w,y+h,0.0f);//座標
			//GXColor3u8(赤,緑,青);//カラー
		GXColor3u8(255,0,255);//カラー
			//点その4
			GXPosition3f32(x,y+h,0.0f);//座標
			//GXColor3u8(赤,緑,青);//カラー
		GXColor3u8(255,0,255);//カラー
		//点その5
			GXPosition3f32(x,y,0.0f);//座標
			//GXColor3u8(赤,緑,青);//カラー
		GXColor3u8(255,0,255);//カラー
		GXEnd();
	

}
//=======================================================================================
// 塗りつぶされた多角形の描画
//
// 座標をいくつも登録してその座標を頂点とする多角形を描画する
//
// v   ... 座標配列の先頭アドレス
// num ... 座標の数
//=======================================================================================
void PrimitiveDrawPolygon(Vec2 v[], u16 num)
{
/*
int icount=0;
 			//プリティプ頂点情報登録開始
			GXBegin(GX_TRIANGLEFAN,GX_VTXFMT0,num);//点を描画
			for(icount;icount<num;icount++)
			{
			
				GXPosition3f32(v[icount].x,v[icount].y,0.0f);//座標
				GXColor3u8(primitiveR, primitiveG, primitiveB);		
			}
		
			
		//プリティプ頂点情報登録終了
		GXEnd();	
*/
int cnt =1;
		
		
	//プリミティブ頂点情報登録開始
		GXBegin(GX_TRIANGLEFAN,GX_VTXFMT0,num);//
		
			//点その0
			GXPosition3f32(v[0].x,v[0].y,0.0f);//座標
			//GXColor3u8(赤,緑,青);//カラー
			GXColor3u8(255,0,255);//カラー
			
	
			
		for(cnt =1;cnt<num;cnt++){//numが5なので4回ループする
				
			//点その1～4
			GXPosition3f32(v[cnt].x,v[cnt].y,0.0f);//座標
			//GXColor3u8(赤,緑,青);//カラー
			GXColor3u8(255,0,255);//カラー
			
			}
			
		GXEnd();
}


//=======================================================================================
// 塗りつぶし四角の描画
//
// x, y ... 四角の左上座標
// w, h ... 四角の幅と高さ
//======================================================================================
void PrimitiveDrawFillRectangle(float x, float y, float w, float h)
{
	/*
			//プリティプ頂点情報登録開始
			GXBegin(GX_TRIANGLEFAN,GX_VTXFMT0,4);//点を描画
			//点1
			GXPosition3f32(x,y,0.0f);//座標
			GXColor3u8(primitiveR, primitiveG, primitiveB);
			//点2
			GXPosition3f32(x+w,y,0.0f);//座標
			GXColor3u8(primitiveR, primitiveG, primitiveB);
			//点3
			GXPosition3f32(x+w,y+h,0.0f);//座標
			GXColor3u8(primitiveR, primitiveG, primitiveB);
			//点4
			GXPosition3f32(x,y+h,0.0f);//座標
			GXColor3u8(primitiveR, primitiveG, primitiveB);			
			
		//プリティプ頂点情報登録終了
		GXEnd();
	*/
	//プリミティブ頂点情報登録開始
		GXBegin(GX_TRIANGLEFAN,GX_VTXFMT0,4);//
			//点その1
			GXPosition3f32(x,y,0.0f);//座標
			//GXColor3u8(赤,緑,青);//カラー
		GXColor3u8(255,0,255);//カラー
			//点その2
			GXPosition3f32(x+w,y,0.0f);//座標
			//GXColor3u8(赤,緑,青);//カラー
		GXColor3u8(255,0,255);//カラー
			//点その3
			GXPosition3f32(x+w,y+h,0.0f);//座標
			//GXColor3u8(赤,緑,青);//カラー
		GXColor3u8(255,0,255);//カラー
			//点その4
			GXPosition3f32(x,y+h,0.0f);//座標
			//GXColor3u8(赤,緑,青);//カラー
		GXColor3u8(255,0,255);//カラー
		GXEnd();


}
