//=======================================================================================
//
//
//    �Q�[�����[�v�e���v���[�g

//=======================================================================================


//----- �C���N���[�h�t�@�C�� -----
#include <revolution.h>
#include <revolution/gx.h> 	// OSFatal���g�p����ꍇinclude���K�v
#include <revolution/kpad.h>

#define DEMO_USE_MEMLIB	// DEMO ���C�u������MEM���W���[���g�p�錾

#include <stdio.h>		// sprintf�Ȃǂ��g�p�ł��܂�
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <demo.h>
#include <math.h>
#include <time.h>

#include "primitive.h"
#include "sprite.h"
#include "mem2allocator.h"

//----- �v���g�^�C�v�錾 -----
void title(void);
void game(void);
void end(void);
void gameover(void);
BOOL atari(float ax, float ay, float ar, float bx, float by, float br);

//----- �萔�}�N�� -----
#define	SCREEN_WIDTH	(640)// �� 4:3
//#define SCREEN_WIDTH	(854)//�� 16:9
#define SCREEN_HEIGHT   (480)//���@4:3

//----- �֐���` -----
//�e�N�X�`��
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



//----- �\���̐錾 -----
//���p�`����邽�߂̍\����
Vec2 pri[]=
{
{100,100},
{150,150},
{250,250},
{150,350},
{100,250}	
};


//�O���[�o���ϐ�
static TPLPalettePtr texpal;//�e�N�X�`���p���b�g�I�u�W�F�N�g
static GXTexObj texObj[TEXTURE_NUM_MAX];//�e�N�X�`���I�u�W�F�N�g�ۑ��p�z��
static KPADStatus kpadStatus;
///////////////�����ō�������///////////////////////////////////
static float px,py,x,y;//�Z���T�[�o�[�ړ�
/*
static float size=30.0f;
*/

static int nflag=0;	//�^�C�g���˃Q�[���v���C�˃Q�[���I�[�o�[�˃^�C�g��
//�s���N�܂�
static float ataripinkx=100;//�摜�̍��Wx//pink
static float ataripinky=100;//�摜�̍��Wy//pink
static int bHitpink;//�����蔻��悤�t���O
static float idoupinkmigix = 400;//�E�ړ�
static float idoupinkhidarix = 400;//���ړ�
static BOOL gazoupink;//�摜�̕\���E��\��
//�܂�
static float atariaox=200;//�摜�̍��Wx//ao
static float atariaoy=200;//�摜�̍��Wy//ao
static int bHitao;//�����蔻��悤�t���O
static float idouaomigix = 200;//�E�ړ�
static float idouaohidarix = 200;//���ړ�
static BOOL gazouao;//�摜�̕\���E��\��
//������܂�
static float atarikirox=500;//�摜�̍��Wx//kiro
static float atarikiroy=100;//�摜�̍��Wy//kiro
static int bHitkiro;//�����蔻��悤�t���O
static float idoukirositay = 200;//���ړ�
static float idoukirouey = 200;//��ړ�
static BOOL gazoukiro;//�摜�̕\���E��\��
//�Ԃ܂�
static float atariakax=100;//�摜�̍��Wx//aka
static float atariakay=300;//�摜�̍��Wy//aka
static int bHitaka;//�����蔻��悤�t���O
static float idouakamigix = 200;//�E�ړ�
static float idouakahidarix = 200;//���ړ�
static BOOL gazouaka;//�摜�̕\���E��\��
//���܂�
static float atarisirox=300;//�摜�̍��Wx//aka
static float atarisiroy=400;//�摜�̍��Wy//aka
static int bHitsiro;//�����蔻��悤�t���O
static float idousirositay = 400;//���ړ�
static float idousirouey = 400;//��ړ�
static BOOL gazousiro;//�摜�̕\���E��\��

static float yokomaku = 255;
static float zikan = 0;//�Q�[���I�[�o�[�p���l
static float mota = 0;//���[�^�[�p���l
static int tama = 5;//�����[�h�V�X�e��
static int riro = 0;//�����[�h�V�X�e��
static BOOL yaki;//���
static float yakizikan = 0;//���
static BOOL dankon;//�e��
//=======================================================================================
//    main�֐�
//=======================================================================================
void main()
{
	//�e�N�X�`���I�u�W�F�N�g�̎��o���p����
	int i=0;

	//�w�i�̐F
	GXColor BG_COLOR = {64, 96, 192};

	//Wii�̏�����
	DEMOInit(NULL);
	
	WPADRegisterAllocator(Mem2Alloc32,Mem2Free32);//�������Ǘ��v���O�������w��
	KPADInit();//������
	
	
	//TPL�t�@�C���̃��[�h
	TPLGetPalette(&texpal,"sample.tpl");
	
	//���[�h�`�F�b�N
	ASSERTMSG(TEXTURE_NUM_MAX==texpal->numDescriptors,"\ntpl���̉摜��������������!\n (numDescriptors=%d)=(TEXTURE_NUM_MAX=%d)",
				texpal->numDescriptors,TEXTURE_NUM_MAX); 
				
	//�e�N�X�`���I�u�W�F�N�g�̎��o��
	for(i=0;i<texpal->numDescriptors;i++)
	{
		TPLGetGXTexObjFromPalette(texpal,&texObj[i],i);
	}
	
	//�摜�̏����� TRUE=(�\��) FALSE=(��\��)
	gazoupink = TRUE;//�s���N
	gazouao = TRUE;//��
	gazoukiro = TRUE;//������
	gazouaka = TRUE;//��
	gazousiro = TRUE;//��
	
	//======================
	//�Q�[�����[�v
	//======================
	while(1)
	{
		//�v���W�F�N�V�����s��
		Mtx44 projMatrix;
		
		
		//�v���W�F�N�V�����s��=���ˉe�s����쐬
		MTXOrtho( projMatrix, 0,SCREEN_HEIGHT, 0, SCREEN_WIDTH, 0.0f, 1.0f);
					
					
		//Wii�ɍs����Z�b�g
		GXSetProjection(projMatrix,GX_ORTHOGRAPHIC);
		
		
		//��ʂ̃N���A
		GXSetCopyClear(BG_COLOR, GX_MAX_Z24);
		
		
		//�����R���ǂݍ���
		KPADRead(WPAD_CHAN0,&kpadStatus,1);
		
		
		
////////////////////////////////////�R���g���[������//////////////////	
		px=kpadStatus.pos.x;//�����R���Z���T�[�o�[�ɂ��ړ��̏���
		py=kpadStatus.pos.y;//�����R���Z���T�[�o�[�ɂ��ړ��̏���
		x=px*(SCREEN_WIDTH/2)+(SCREEN_WIDTH/2);//�����R���Z���T�[�o�[�ɂ��ړ��̏���
		y=py*(SCREEN_HEIGHT/2)+(SCREEN_HEIGHT/2);//�����R���Z���T�[�o�[�ɂ��ړ��̏���
////////////////////////////////////////////////////////////////////////////////////
	/*
		//A�{�^������������//�f�o�b�O�p
		if(kpadStatus.trig&KPAD_BUTTON_A)
		{
			//�^�C�g���˃Q�[���v���C�˃Q�[���I�[�o�[�˃^�C�g��
			nflag = 1;
		}
	*/		

		
		//�`��J�n
		DEMOBeforeRender();
		GXClearVtxDesc();
		GXSetVtxDesc(GX_VA_POS,GX_DIRECT);
		GXSetVtxDesc(GX_VA_CLR0,GX_DIRECT);
		GXSetVtxDesc(GX_VA_TEX0,GX_DIRECT);
		
		
		GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_POS,GX_POS_XYZ,GX_F32,0);
		GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_CLR0,GX_CLR_RGB,GX_RGBA8,0);
		GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_TEX0,GX_TEX_ST,GX_F32,0);//���Ȃ��J���[

		//======Wii�ɐF���g���ݒ���s���i�ڍ׌���j


	  
	  	
		//�X�v���C�g�`��
		SpriteSetup();
		SpriteSetColor(255,255,255,255);
	//	PrimitiveSetup();//�ǂ���������v���~�e�B�u�����炵��
	//	PrimitiveSetColor(255,255,255);
		
		//�^�C�g���˃Q�[���v���C�˃Q�[���I�[�o�[�˃^�C�g��
	 	if(nflag==0)
		{
	  		//�^�C�g�����
			title();
	 	}

		if(nflag==1)
		{
			//�Q�[���J�n
			game();	

		}
	
		if(nflag==2)
		{
			//�Q�[���I��
			end();
		//A�{�^������������
		if(kpadStatus.trig&KPAD_BUTTON_A)
			{
				nflag = 0;
			}
		}
		
		//�^�C�g����ʂɖ߂鏈��
		if(nflag==3)
		{
			//�Q�[���I�[�o�[
			gameover();
		//A�{�^������������
		if(kpadStatus.trig&KPAD_BUTTON_A)
			{
				nflag = 0;
			}
		}
		
		
		//�`��I��
		DEMODoneRender();
	}
	OSHalt("End of Sample");	//�I��
}



//=============================================================================
// �^�C�g�����
//=============================================================================
void title(void)
{
	SpriteSetColor(255,255,255,yokomaku);
//	SpriteDraw(&texObj[TEXTURE_TEXT_halo1],0,0,700,480,0,0);
SpriteDraw(&texObj[TEXTURE_TEXT_title],0,0,900,480,0,0);
	yokomaku = yokomaku -5;

	//A�{�^������������
		if(kpadStatus.trig&KPAD_BUTTON_A)
			{
				nflag = 1;
				yokomaku = 255;//�悱�܂����Z�b�g
			}

}

//=============================================================================
// �Q�[���v���C
//=============================================================================
void game(void)
{
//////////////////////�Q�[�����e����///////////////////////////
//�s���N�F�܂ƈړ�����
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

//�F�܂ƈړ�����
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

//���F�܂ƈړ�����
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

//�ԐF�܂ƈړ�����
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

//���F�܂ƈړ�����
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

//�Q�[���I�[�o�[�p���l
zikan++;
//���[�^�[�U���p���l
mota++;
//���[�^�~�߂�p////////////////////
if(mota == 10 )
{
	//�U�����[�^�[OFF
	WPADStopMotor(WPAD_CHAN0);
}	
//���[�^�~�߂�p////////////////////


///////////////�e�N�X�`��///////////////////////
//SpriteDraw(&texObj[TEXTURE�̖��O],�\�����W��,�\�����W��,�\���������e�N�X�`���̕�,�\���������e�N�X�`���̍���,�؂���ꏊ��,�؂���ꏊ��);
	 SpriteDraw(&texObj[TEXTURE_TEXT_Ca],0,0,900,480,0,0);//�w�i�摜
	

if(gazoupink)//����TRUE�Ȃ牺�̓��e�����s����//�s���N
{
	 SpriteDraw(&texObj[TEXTURE_TEXT_mato_pink],ataripinkx,ataripinky,52,141,0,0);
}
	 
if(gazouao)//����TRUE�Ȃ牺�̓��e�����s����//��
{
	SpriteDraw(&texObj[TEXTURE_TEXT_mato_ao],atariaox,atariaoy,52,141,0,0);
}
	  
if(gazoukiro)//����TRUE�Ȃ牺�̓��e�����s����//���F
{
	SpriteDraw(&texObj[TEXTURE_TEXT_mato_kiro],atarikirox,atarikiroy,52,141,0,0);
}
if(gazouaka)//����TRUE�Ȃ牺�̓��e�����s����//��
{
	SpriteDraw(&texObj[TEXTURE_TEXT_mato_aka],atariakax,atariakay,52,141,0,0);
}
if(gazousiro)//����TRUE�Ȃ牺�̓��e�����s����//��
{
	SpriteDraw(&texObj[TEXTURE_TEXT_mato_siro],atarisirox,atarisiroy,52,141,0,0);
}
	  
	  SpriteDraw(&texObj[TEXTURE_TEXT_rock],x,y,42,42,0,0);
///////////////�e�N�X�`��///////////////////////	  
		
	//	PrimitiveDrawPoint(10, 10);	
	//	PrimitiveDrawFillRectangle(200.f, 30.f, 200.f, 30.f);
//////////////////////////////////////////////�R���g���[���[//////////////////////////////
	
	
		//�\���L�[�����������
		if(kpadStatus.hold==KPAD_BUTTON_UP)
		{

		}
		//�\���L�[������������
		if(kpadStatus.hold==KPAD_BUTTON_DOWN)
		{
	
		}
		//�\���L�[�E����������
		if(kpadStatus.hold==KPAD_BUTTON_RIGHT)
		{

		}
		//�\���L�[������������
		if(kpadStatus.hold==KPAD_BUTTON_LEFT)
		{
	
		}
		//�z�[���{�^������������
		if(kpadStatus.hold&KPAD_BUTTON_HOME)
		{
			//���Z�b�g//�f�o�b�O�p
			gazoupink = TRUE;//�s���N�F�܂�
			gazouao = TRUE;//�F�܂�
			gazoukiro = TRUE;//���F�܂�
			gazouaka = TRUE;//�ԐF�܂�
			gazousiro = TRUE;//���F�܂�
		//	 size=30.0f;
		}
		
		//�v���X�{�^������������
		if(kpadStatus.hold&KPAD_BUTTON_PLUS)
		{
			//�g��
		//	size+=1.0f;
		}
		//�}�C�i�X�{�^������������
		if(kpadStatus.hold&KPAD_BUTTON_MINUS)
		{
			//�k��
		//	size-=1.0f;
		//	if(size<1.0f)
		//	{
		//		size=1.0f;	
		//	}
		}
			//1�{�^������������
		if(kpadStatus.hold&KPAD_BUTTON_1)
		{
				//�U�����[�^�[ON
			WPADStartMotor(WPAD_CHAN0);
			
		}
		//2�{�^������������
		if(kpadStatus.hold&KPAD_BUTTON_2)
		{
				//�U�����[�^�[OFF
			WPADStopMotor(WPAD_CHAN0);
		}
		//B�{�^������������
		if((kpadStatus.trig&KPAD_BUTTON_B)&&(tama != 0))
		{
			//�U�����[�^�[ON
			WPADStartMotor(WPAD_CHAN0);
			mota = 0;//���[�^�[
			tama = tama - 1;//�����[�h�V�X�e��
			yaki = TRUE;
			yakizikan = 0;
		}
//////////////////////////////////////////////�R���g���[���[//////////////////////////////		
/////�����蔻��///////////
	//B�{�^������������
	if((kpadStatus.trig&KPAD_BUTTON_B)&&(tama != 0))//(tama��0����Ȃ��Ƃ�)
	{
	//�s���N�܂�
	 bHitpink = atari(
	 			x, y,42,
				ataripinkx, ataripinky,0
				);
				if(bHitpink)
				{
				gazoupink = FALSE;//�摜��������
			//	dankon = TRUE; //���肩��
				}
		
		
			//�܂�	
				 bHitao = atari(
	 			x, y,42,
				atariaox, atariaoy,0
				);
				if(bHitao)
				{
				gazouao = FALSE;//�摜��������
				}
				
				//������܂�
				 bHitkiro = atari(
	 			x, y,42,
				atarikirox, atarikiroy,0
				);
				if(bHitkiro)
				{
			gazoukiro = FALSE;//�摜��������
				}
				
				//�Ԃ܂�	
				 bHitaka = atari(
	 			x, y,42,
				atariakax, atariakay,0
				);
				if(bHitaka)
				{
				gazouaka = FALSE;//�摜��������
				}
				
				//���܂�	
				 bHitsiro = atari(
	 			x, y,42,
				atarisirox, atarisiroy,0
				);
				if(bHitsiro)
				{
				gazousiro = FALSE;//�摜��������
				}
				
	}	
/////�����蔻��///////////	
//////////////////////////////////���U���g���////////////////////////
if((gazoukiro == FALSE && gazouao == FALSE && gazoupink == FALSE && gazouaka == FALSE && gazousiro == FALSE)&&(mota == 10))
{
	mota =0;
	//�U�����[�^�[OFF
	WPADStopMotor(WPAD_CHAN0);
	nflag =2;
	
	//�摜�̏����� TRUE=(�\��) FALSE=(��\��)//�f�o�b�O�p
	gazoupink = TRUE;//�s���N
	gazouao = TRUE;//��
	gazoukiro = TRUE;//������
	gazouaka = TRUE;//��
	gazousiro = TRUE;//��
	zikan = 0;

}
if(zikan == 400)
{
	mota =0;
	//�U�����[�^�[OFF
	WPADStopMotor(WPAD_CHAN0);
	nflag = 3;
	
	//�摜�̏����� TRUE=(�\��) FALSE=(��\��)//�f�o�b�O�p
	gazoupink = TRUE;//�s���N
	gazouao = TRUE;//��
	gazoukiro = TRUE;//������
	gazouaka = TRUE;//��
	gazousiro = TRUE;//��
	zikan = 0;
	
}
//////////////////////////////////���U���g���////////////////////////
//�����[�h�V�X�e��
if(tama == 0)
{
	
	SpriteDraw(&texObj[TEXTURE_TEXT_rirodo],x+36,y+36,30,30,0,0);//�����[�h���摜
	riro++;
	if(riro == 100)
	{
		tama = 5;//�e���Z�b�g
		riro = 0;
	}
}
//�����[�h�V�X�e��
//�c�i��/////////////
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
//�c�i��/////////////
////���////////
yakizikan++;
if(yaki)
{
	SpriteDraw(&texObj[TEXTURE_TEXT_mazuru],x-10,y-10,65,65,0,0);		
}

if(yakizikan == 10)
{
	yaki = FALSE;
}
////���////////
///�e��///////
/*��肩��
if(dankon)
{
	SpriteDraw(&texObj[TEXTURE_TEXT_dankon],ataripinkx,ataripinky,22,29,0,0);
}				
dankon = FALSE;
*/
///�e��///////
}

//=============================================================================
// �G���h
//=============================================================================
void end(void)//�G���h
{
	SpriteDraw(&texObj[TEXTURE_TEXT_end],0,0,900,480,0,0);
	tama = 5;//�e���Z�b�g
}
void gameover(void)// �Q�[���I�[�o�[
{
	SpriteDraw(&texObj[TEXTURE_TEXT_gameover],0,0,900,480,0,0);
	tama = 5;//�e���Z�b�g
}
//====================
//�����蔻��
//====================
BOOL atari(float ax, float ay, float ar, float bx, float by, float br)
{		//(ax=a�̉~�̉����a,ay=a�̉~�̏c���a,ar=a�̉~�̎Εӂ̔��a,bx=b�̉~�̉����a,by=b�̉~�̏c���a,br=b�̉~�̎Εӂ̔��a,)
	float x = bx - ax;//b�̉��̔��a-a�̉��̔��a��l�̉��̒������o��
	float y = by - ay;//b�̏c�̔��a-a�̏c�̔��a��l�̏c�̒������o��

	float l = x*x + y*y;//�O�p�`�̒��(x)��2��ƑΕ�(y)��2��ŎΕ�(l)��2�悪�o��
	return l < (ar + br)*(ar + br);//�Εӂ̒�����a��b�̎Εӂ̔��a��2����ׂ�
}
