//=======================================================================================
//
//
//    ゲームループテンプレート

//=======================================================================================


//----- インクルードファイル -----
#include <revolution.h>
#include <revolution/gx.h> 	// OSFatalを使用する場合includeが必要
#include <revolution/kpad.h>

#define DEMO_USE_MEMLIB	// DEMO ライブラリのMEMモジュール使用宣言

#include <stdio.h>		// sprintfなども使用できます
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <demo.h>
#include <math.h>
#include <time.h>

#include "primitive.h"
#include "sprite.h"
#include "mem2allocator.h"

//----- プロトタイプ宣言 -----
void title(void);
void game(void);
void end(void);
void gameover(void);
BOOL atari(float ax, float ay, float ar, float bx, float by, float br);

//----- 定数マクロ -----
#define	SCREEN_WIDTH	(640)// 横 4:3
//#define SCREEN_WIDTH	(854)//横 16:9
#define SCREEN_HEIGHT   (480)//横　4:3

//----- 関数定義 -----
//テクスチャ
enum
{
	TEXTURE_TEXT_mazuru,//GX_TEXMAP0
	TEXTURE_TEXT_rirodo,//GX_TEXMAP1
	TEXTURE_TEXT_Ca,//GX_TEXMAP2
	TEXTURE_TEXT_tama,//GX_TEXMAP3
	TEXTURE_TEXT_rock,//GX_TEXMAP4
	TEXTURE_TEXT_mato_kiro,//GX_TEXMAP5
	TEXTURE_TEXT_mato_ao,//GX_TEXMAP6
	TEXTURE_TEXT_mato_pink,//GX_TEXMAP7
	TEXTURE_TEXT_title,//GX_TEXMAP8
	TEXTURE_TEXT_end,//GX_TEXMAP9
	TEXTURE_TEXT_gameover,//GX_TEXMAP10
	TEXTURE_TEXT_mato_aka,//GX_TEXMAP11
	TEXTURE_TEXT_mato_siro,//GX_TEXMAP12
	TEXTURE_NUM_MAX
};



//----- 構造体宣言 -----
//多角形を作るための構造体
Vec2 pri[]=
{
{100,100},
{150,150},
{250,250},
{150,350},
{100,250}	
};


//グローバル変数
static TPLPalettePtr texpal;//テクスチャパレットオブジェクト
static GXTexObj texObj[TEXTURE_NUM_MAX];//テクスチャオブジェクト保存用配列
static KPADStatus kpadStatus;
///////////////自分で作ったやつ///////////////////////////////////
static float px,py,x,y;//センサーバー移動
/*
static float size=30.0f;
*/

static int nflag=0;	//タイトル⇒ゲームプレイ⇒ゲームオーバー⇒タイトル
//ピンクまと
static float ataripinkx=100;//画像の座標x//pink
static float ataripinky=100;//画像の座標y//pink
static int bHitpink;//あたり判定ようフラグ
static float idoupinkmigix = 400;//右移動
static float idoupinkhidarix = 400;//左移動
static BOOL gazoupink;//画像の表示・非表示
//青まと
static float atariaox=200;//画像の座標x//ao
static float atariaoy=200;//画像の座標y//ao
static int bHitao;//あたり判定ようフラグ
static float idouaomigix = 200;//右移動
static float idouaohidarix = 200;//左移動
static BOOL gazouao;//画像の表示・非表示
//きいろまと
static float atarikirox=500;//画像の座標x//kiro
static float atarikiroy=100;//画像の座標y//kiro
static int bHitkiro;//あたり判定ようフラグ
static float idoukirositay = 200;//下移動
static float idoukirouey = 200;//上移動
static BOOL gazoukiro;//画像の表示・非表示
//赤まと
static float atariakax=100;//画像の座標x//aka
static float atariakay=300;//画像の座標y//aka
static int bHitaka;//あたり判定ようフラグ
static float idouakamigix = 200;//右移動
static float idouakahidarix = 200;//左移動
static BOOL gazouaka;//画像の表示・非表示
//白まと
static float atarisirox=300;//画像の座標x//aka
static float atarisiroy=400;//画像の座標y//aka
static int bHitsiro;//あたり判定ようフラグ
static float idousirositay = 400;//下移動
static float idousirouey = 400;//上移動
static BOOL gazousiro;//画像の表示・非表示

static float yokomaku = 255;
static float zikan = 0;//ゲームオーバー用数値
static float mota = 0;//モーター用数値
static int tama = 5;//リロードシステム
static int riro = 0;//リロードシステム
static BOOL yaki;//薬莢
static float yakizikan = 0;//薬莢
static BOOL dankon;//弾痕
//=======================================================================================
//    main関数
//=======================================================================================
void main()
{
	//テクスチャオブジェクトの取り出し用引数
	int i=0;

	//背景の色
	GXColor BG_COLOR = {64, 96, 192};

	//Wiiの初期化
	DEMOInit(NULL);
	
	WPADRegisterAllocator(Mem2Alloc32,Mem2Free32);//メモリ管理プログラムを指定
	KPADInit();//初期化
	
	
	//TPLファイルのロード
	TPLGetPalette(&texpal,"sample.tpl");
	
	//ロードチェック
	ASSERTMSG(TEXTURE_NUM_MAX==texpal->numDescriptors,"\ntpl内の画像枚数がおかしい!\n (numDescriptors=%d)=(TEXTURE_NUM_MAX=%d)",
				texpal->numDescriptors,TEXTURE_NUM_MAX); 
				
	//テクスチャオブジェクトの取り出し
	for(i=0;i<texpal->numDescriptors;i++)
	{
		TPLGetGXTexObjFromPalette(texpal,&texObj[i],i);
	}
	
	//画像の初期化 TRUE=(表示) FALSE=(非表示)
	gazoupink = TRUE;//ピンク
	gazouao = TRUE;//青
	gazoukiro = TRUE;//きいろ
	gazouaka = TRUE;//赤
	gazousiro = TRUE;//白
	
	//======================
	//ゲームループ
	//======================
	while(1)
	{
		//プロジェクション行列
		Mtx44 projMatrix;
		
		
		//プロジェクション行列=正射影行列を作成
		MTXOrtho( projMatrix, 0,SCREEN_HEIGHT, 0, SCREEN_WIDTH, 0.0f, 1.0f);
					
					
		//Wiiに行列をセット
		GXSetProjection(projMatrix,GX_ORTHOGRAPHIC);
		
		
		//画面のクリア
		GXSetCopyClear(BG_COLOR, GX_MAX_Z24);
		
		
		//リモコン読み込む
		KPADRead(WPAD_CHAN0,&kpadStatus,1);
		
		
		
////////////////////////////////////コントロール処理//////////////////	
		px=kpadStatus.pos.x;//リモコンセンサーバーによる移動の処理
		py=kpadStatus.pos.y;//リモコンセンサーバーによる移動の処理
		x=px*(SCREEN_WIDTH/2)+(SCREEN_WIDTH/2);//リモコンセンサーバーによる移動の処理
		y=py*(SCREEN_HEIGHT/2)+(SCREEN_HEIGHT/2);//リモコンセンサーバーによる移動の処理
////////////////////////////////////////////////////////////////////////////////////
	/*
		//Aボタンを押したら//デバッグ用
		if(kpadStatus.trig&KPAD_BUTTON_A)
		{
			//タイトル⇒ゲームプレイ⇒ゲームオーバー⇒タイトル
			nflag = 1;
		}
	*/		

		
		//描画開始
		DEMOBeforeRender();
		GXClearVtxDesc();
		GXSetVtxDesc(GX_VA_POS,GX_DIRECT);
		GXSetVtxDesc(GX_VA_CLR0,GX_DIRECT);
		GXSetVtxDesc(GX_VA_TEX0,GX_DIRECT);
		
		
		GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_POS,GX_POS_XYZ,GX_F32,0);
		GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_CLR0,GX_CLR_RGB,GX_RGBA8,0);
		GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_TEX0,GX_TEX_ST,GX_F32,0);//αなしカラー

		//======Wiiに色を使う設定を行う（詳細後日）


	  
	  	
		//スプライト描画
		SpriteSetup();
		SpriteSetColor(255,255,255,255);
	//	PrimitiveSetup();//どうもこいつらプリミティブが問題らしい
	//	PrimitiveSetColor(255,255,255);
		
		//タイトル⇒ゲームプレイ⇒ゲームオーバー⇒タイトル
	 	if(nflag==0)
		{
	  		//タイトル画面
			title();
	 	}

		if(nflag==1)
		{
			//ゲーム開始
			game();	

		}
	
		if(nflag==2)
		{
			//ゲーム終了
			end();
		//Aボタンを押したら
		if(kpadStatus.trig&KPAD_BUTTON_A)
			{
				nflag = 0;
			}
		}
		
		//タイトル画面に戻る処理
		if(nflag==3)
		{
			//ゲームオーバー
			gameover();
		//Aボタンを押したら
		if(kpadStatus.trig&KPAD_BUTTON_A)
			{
				nflag = 0;
			}
		}
		
		
		//描画終了
		DEMODoneRender();
	}
	OSHalt("End of Sample");	//終了
}



//=============================================================================
// タイトル画面
//=============================================================================
void title(void)
{
	SpriteSetColor(255,255,255,yokomaku);
//	SpriteDraw(&texObj[TEXTURE_TEXT_halo1],0,0,700,480,0,0);
SpriteDraw(&texObj[TEXTURE_TEXT_title],0,0,900,480,0,0);
	yokomaku = yokomaku -5;

	//Aボタンを押したら
		if(kpadStatus.trig&KPAD_BUTTON_A)
			{
				nflag = 1;
				yokomaku = 255;//よこまくリセット
			}

}

//=============================================================================
// ゲームプレイ
//=============================================================================
void game(void)
{
//////////////////////ゲーム内容処理///////////////////////////
//ピンク色まと移動処理
if(idoupinkmigix>=100&&idoupinkmigix<=400)
{
idoupinkmigix = idoupinkmigix - 5;
ataripinkx = ataripinkx + 5;
}
else if(idoupinkhidarix >= 100 && idoupinkhidarix <= 400 && idoupinkmigix == 95)
{
 idoupinkhidarix = idoupinkhidarix - 5;
	ataripinkx = ataripinkx -5;
}
else if(idoupinkhidarix == 95 && idoupinkmigix == 95)
{
	idoupinkhidarix = 400;
	idoupinkmigix = 400;
}

//青色まと移動処理
if(idouaomigix >= 0 && idouaomigix <= 200)
{
idouaomigix = idouaomigix - 5;
atariaox = atariaox + 5;
}
else if(idouaohidarix >= 0 && idouaohidarix <= 200 && idouaomigix == -5)
{
 idouaohidarix = idouaohidarix - 5;
	atariaox = atariaox -5;
}
else if(idouaohidarix == -5 && idouaomigix == -5)
{
	idouaohidarix = 200;
	idouaomigix = 200;
}

//黄色まと移動処理
if(idoukirositay >= 0 && idoukirositay <= 200)
{
idoukirositay = idoukirositay - 5;
atarikiroy = atarikiroy + 5;
}
else if(idoukirouey >= 0 && idoukirouey <= 200 && idoukirositay == -5)
{
 idoukirouey = idoukirouey - 5;
	atarikiroy = atarikiroy -5;
}
else if(idoukirouey == -5 && idoukirositay == -5)
{
	idoukirouey = 200;
	idoukirositay = 200;
}

//赤色まと移動処理
if(idouakamigix >= 0 && idouakamigix <= 200)
{
idouakamigix = idouakamigix - 5;
atariakax = atariakax + 5;
}
else if(idouakahidarix >= 0 && idouakahidarix <= 200 && idouakamigix == -5)
{
 idouakahidarix = idouakahidarix - 5;
	atariakax = atariakax -5;
}
else if(idouakahidarix == -5 && idouakamigix == -5)
{
	idouakahidarix = 200;
	idouakamigix = 200;
}

//白色まと移動処理
if(idousirositay >= 0 && idousirositay <= 400)
{
idousirositay = idousirositay - 5;
atarisiroy = atarisiroy - 5;
}
else if(idousirouey >= 0 && idousirouey <= 400 && idousirositay == - 5)
{
 idousirouey = idousirouey - 5;
	atarisiroy = atarisiroy + 5;
}
else if(idousirouey == - 5 && idousirositay == - 5)
{
	idousirouey = 400;
	idousirositay = 400;
}

//ゲームオーバー用数値
zikan++;
//モーター振動用数値
mota++;
//モータ止める用////////////////////
if(mota == 10 )
{
	//振動モーターOFF
	WPADStopMotor(WPAD_CHAN0);
}	
//モータ止める用////////////////////


///////////////テクスチャ///////////////////////
//SpriteDraw(&texObj[TEXTUREの名前],表示座標ｘ,表示座標ｙ,表示したいテクスチャの幅,表示したいテクスチャの高さ,切り取り場所ｘ,切り取り場所ｙ);
	 SpriteDraw(&texObj[TEXTURE_TEXT_Ca],0,0,900,480,0,0);//背景画像
	

if(gazoupink)//もしTRUEなら下の内容を実行する//ピンク
{
	 SpriteDraw(&texObj[TEXTURE_TEXT_mato_pink],ataripinkx,ataripinky,52,141,0,0);
}
	 
if(gazouao)//もしTRUEなら下の内容を実行する//青
{
	SpriteDraw(&texObj[TEXTURE_TEXT_mato_ao],atariaox,atariaoy,52,141,0,0);
}
	  
if(gazoukiro)//もしTRUEなら下の内容を実行する//黄色
{
	SpriteDraw(&texObj[TEXTURE_TEXT_mato_kiro],atarikirox,atarikiroy,52,141,0,0);
}
if(gazouaka)//もしTRUEなら下の内容を実行する//赤
{
	SpriteDraw(&texObj[TEXTURE_TEXT_mato_aka],atariakax,atariakay,52,141,0,0);
}
if(gazousiro)//もしTRUEなら下の内容を実行する//白
{
	SpriteDraw(&texObj[TEXTURE_TEXT_mato_siro],atarisirox,atarisiroy,52,141,0,0);
}
	  
	  SpriteDraw(&texObj[TEXTURE_TEXT_rock],x,y,42,42,0,0);
///////////////テクスチャ///////////////////////	  
		
	//	PrimitiveDrawPoint(10, 10);	
	//	PrimitiveDrawFillRectangle(200.f, 30.f, 200.f, 30.f);
//////////////////////////////////////////////コントローラー//////////////////////////////
	
	
		//十字キー上を押したら
		if(kpadStatus.hold==KPAD_BUTTON_UP)
		{

		}
		//十字キー下を押したら
		if(kpadStatus.hold==KPAD_BUTTON_DOWN)
		{
	
		}
		//十字キー右を押したら
		if(kpadStatus.hold==KPAD_BUTTON_RIGHT)
		{

		}
		//十字キー左を押したら
		if(kpadStatus.hold==KPAD_BUTTON_LEFT)
		{
	
		}
		//ホームボタンを押したら
		if(kpadStatus.hold&KPAD_BUTTON_HOME)
		{
			//リセット//デバッグ用
			gazoupink = TRUE;//ピンク色まと
			gazouao = TRUE;//青色まと
			gazoukiro = TRUE;//黄色まと
			gazouaka = TRUE;//赤色まと
			gazousiro = TRUE;//白色まと
		//	 size=30.0f;
		}
		
		//プラスボタンを押したら
		if(kpadStatus.hold&KPAD_BUTTON_PLUS)
		{
			//拡大
		//	size+=1.0f;
		}
		//マイナスボタンを押したら
		if(kpadStatus.hold&KPAD_BUTTON_MINUS)
		{
			//縮小
		//	size-=1.0f;
		//	if(size<1.0f)
		//	{
		//		size=1.0f;	
		//	}
		}
			//1ボタンを押したら
		if(kpadStatus.hold&KPAD_BUTTON_1)
		{
				//振動モーターON
			WPADStartMotor(WPAD_CHAN0);
			
		}
		//2ボタンを押したら
		if(kpadStatus.hold&KPAD_BUTTON_2)
		{
				//振動モーターOFF
			WPADStopMotor(WPAD_CHAN0);
		}
		//Bボタンを押したら
		if((kpadStatus.trig&KPAD_BUTTON_B)&&(tama != 0))
		{
			//振動モーターON
			WPADStartMotor(WPAD_CHAN0);
			mota = 0;//モーター
			tama = tama - 1;//リロードシステム
			yaki = TRUE;
			yakizikan = 0;
		}
//////////////////////////////////////////////コントローラー//////////////////////////////		
/////あたり判定///////////
	//Bボタンを押したら
	if((kpadStatus.trig&KPAD_BUTTON_B)&&(tama != 0))//(tamaが0じゃないとき)
	{
	//ピンクまと
	 bHitpink = atari(
	 			x, y,42,
				ataripinkx, ataripinky,0
				);
				if(bHitpink)
				{
				gazoupink = FALSE;//画像が消える
			//	dankon = TRUE; //つくりかけ
				}
		
		
			//青まと	
				 bHitao = atari(
	 			x, y,42,
				atariaox, atariaoy,0
				);
				if(bHitao)
				{
				gazouao = FALSE;//画像が消える
				}
				
				//きいろまと
				 bHitkiro = atari(
	 			x, y,42,
				atarikirox, atarikiroy,0
				);
				if(bHitkiro)
				{
			gazoukiro = FALSE;//画像が消える
				}
				
				//赤まと	
				 bHitaka = atari(
	 			x, y,42,
				atariakax, atariakay,0
				);
				if(bHitaka)
				{
				gazouaka = FALSE;//画像が消える
				}
				
				//白まと	
				 bHitsiro = atari(
	 			x, y,42,
				atarisirox, atarisiroy,0
				);
				if(bHitsiro)
				{
				gazousiro = FALSE;//画像が消える
				}
				
	}	
/////あたり判定///////////	
//////////////////////////////////リザルト画面////////////////////////
if((gazoukiro == FALSE && gazouao == FALSE && gazoupink == FALSE && gazouaka == FALSE && gazousiro == FALSE)&&(mota == 10))
{
	mota =0;
	//振動モーターOFF
	WPADStopMotor(WPAD_CHAN0);
	nflag =2;
	
	//画像の初期化 TRUE=(表示) FALSE=(非表示)//デバッグ用
	gazoupink = TRUE;//ピンク
	gazouao = TRUE;//青
	gazoukiro = TRUE;//きいろ
	gazouaka = TRUE;//赤
	gazousiro = TRUE;//白
	zikan = 0;

}
if(zikan == 400)
{
	mota =0;
	//振動モーターOFF
	WPADStopMotor(WPAD_CHAN0);
	nflag = 3;
	
	//画像の初期化 TRUE=(表示) FALSE=(非表示)//デバッグ用
	gazoupink = TRUE;//ピンク
	gazouao = TRUE;//青
	gazoukiro = TRUE;//きいろ
	gazouaka = TRUE;//赤
	gazousiro = TRUE;//白
	zikan = 0;
	
}
//////////////////////////////////リザルト画面////////////////////////
//リロードシステム
if(tama == 0)
{
	
	SpriteDraw(&texObj[TEXTURE_TEXT_rirodo],x+36,y+36,30,30,0,0);//リロード中画像
	riro++;
	if(riro == 100)
	{
		tama = 5;//弾リセット
		riro = 0;
	}
}
//リロードシステム
//残段数/////////////
if(tama ==5)
{
	SpriteDraw(&texObj[TEXTURE_TEXT_tama],100,400,8,45,0,0);
}
if(tama >=4)
{
	SpriteDraw(&texObj[TEXTURE_TEXT_tama],110,400,8,45,0,0);
}
if(tama >=3)
{
	SpriteDraw(&texObj[TEXTURE_TEXT_tama],120,400,8,45,0,0);
}
if(tama >=2)
{
	SpriteDraw(&texObj[TEXTURE_TEXT_tama],130,400,8,45,0,0);
}
if(tama >=1)
{
	SpriteDraw(&texObj[TEXTURE_TEXT_tama],140,400,8,45,0,0);
}
//残段数/////////////
////薬莢////////
yakizikan++;
if(yaki)
{
	SpriteDraw(&texObj[TEXTURE_TEXT_mazuru],x-10,y-10,65,65,0,0);		
}

if(yakizikan == 10)
{
	yaki = FALSE;
}
////薬莢////////
///弾痕///////
/*作りかけ
if(dankon)
{
	SpriteDraw(&texObj[TEXTURE_TEXT_dankon],ataripinkx,ataripinky,22,29,0,0);
}				
dankon = FALSE;
*/
///弾痕///////
}

//=============================================================================
// エンド
//=============================================================================
void end(void)//エンド
{
	SpriteDraw(&texObj[TEXTURE_TEXT_end],0,0,900,480,0,0);
	tama = 5;//弾リセット
}
void gameover(void)// ゲームオーバー
{
	SpriteDraw(&texObj[TEXTURE_TEXT_gameover],0,0,900,480,0,0);
	tama = 5;//弾リセット
}
//====================
//あたり判定
//====================
BOOL atari(float ax, float ay, float ar, float bx, float by, float br)
{		//(ax=aの円の横半径,ay=aの円の縦半径,ar=aの円の斜辺の半径,bx=bの円の横半径,by=bの円の縦半径,br=bの円の斜辺の半径,)
	float x = bx - ax;//bの横の半径-aの横の半径でlの横の長さを出す
	float y = by - ay;//bの縦の半径-aの縦の半径でlの縦の長さを出す

	float l = x*x + y*y;//三角形の底辺(x)の2乗と対辺(y)の2乗で斜辺(l)の2乗が出る
	return l < (ar + br)*(ar + br);//斜辺の長さとaとbの斜辺の半径の2乗を比べる
}
