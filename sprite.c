//=======================================================================================
//
//    [ sprite.c ] �X�v���C�g�`�惂�W���[��
//
//		���̃t�@�C���֊֐����쐬����
//=======================================================================================


//----- �C���N���[�h�t�@�C�� -----

#include "sprite.h"


//----- �O���[�o���ϐ���` -----

static u8 spriteR = 255; // �X�v���C�g�̐F
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

//----- �֐���` -----

//=======================================================================================
// �X�v���C�g�`�揀���֐�
//
// Sprite��Draw�֐����ĂԑO�ɃR�[������
//
// ������Setup�֐����Ă΂ꂽ��ASprite��Draw�֐����Ăԏꍇ�ɂ͍ēx�R�[�����邱��
//=======================================================================================
void SpriteSetup(void)
{
		GXClearVtxDesc();
		GXSetVtxDesc(GX_VA_POS,GX_DIRECT);
		GXSetVtxDesc(GX_VA_CLR0,GX_DIRECT);
		GXSetVtxDesc(GX_VA_TEX0,GX_DIRECT);
		
		
		GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_POS,GX_POS_XYZ,GX_F32,0);
		GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_CLR0,GX_CLR_RGB,GX_RGBA8,0);
		GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_TEX0,GX_TEX_ST,GX_F32,0);//���Ȃ��J���[

		//======Wii�ɐF���g���ݒ���s���i�ڍ׌���j

		// �g�p����TEV�X�e�[�W���̐ݒ�
		GXSetNumTevStages(1); // 1��
		    
		// �J���[�`�����l�����̐ݒ�
		GXSetNumChans(1); // 1��
		    
		// ���p�\�ɂ���e�N�X�`�����W���̐ݒ�
	   	GXSetNumTexGens(1); 
			
		// TEV���g�p����e�N�X�`���[�J���[�ƃ��X�^���C�Y�J���[�̐ݒ�
		GXSetTevOrder(GX_TEVSTAGE0,     // TEV�X�e�[�W0�̐ݒ�
	    	    	  GX_TEXCOORD0, // �e�N�X�`�����W�͎g��Ȃ�
	    	          GX_TEXMAP0, 	// �e�N�X�`���͎g�p���Ȃ�
	    	          GX_COLOR0A0);		// �J���[�`�����l��0�E�A���t�@�`�����l��0���g�p
	    	          
	    	          
	  	//TEV����̗v�f���ǂ̂悤�ɍ������邩��ݒ肷��
	  	GXSetTevOp(GX_TEVSTAGE0,GX_MODULATE);	//TEV�X�e�[�W0��ݒ�ł���
	  											//�e�N�X�`���J���[�ƃe�N�X�`���A���t�@���o��
	  	//�n�[�h�E�F�A�ݒ�ǉ�
	  	GXSetBlendMode(GX_BM_BLEND,GX_BL_SRCALPHA,GX_BL_INVSRCALPHA,GX_LO_CLEAR);

}


//=======================================================================================
// �X�v���C�g�F�ݒ�֐�
//
// �X�v���C�g�F���w�肷��
// ���̊֐����Ă΂ꂽ��̃X�v���C�g�摜�͂��ׂĂ����Ŏw�肵���F�Ƃ̏�Z�����ɂȂ�
//
// r ... �ԗv�f(0-255)
// g ... �Ηv�f(0-255)
// b ... �v�f(0-255)
//=======================================================================================
void SpriteSetColor(u8 r, u8 g, u8 b, u8 a) 
{
	spriteR = r;
	spriteG = g;
	spriteB = b;
	spriteA = a;
}


//=======================================================================================
// �X�v���C�g�`��֐�
//
// pTex   ... �e�N�X�`���I�u�W�F�N�g�̐擪�A�h���X
// dx, dy ... �X�v���C�g�̍�����W
// dw, dh ... �X�v���C�g�̕��ƍ���(�e�N�X�`���̐؂��蕝�ƍ���)
// tx, ty ... �e�N�X�`���̐؂��荶����W�i�؂���J�n�n�_�j
//=======================================================================================
//tw ���̃e�N�X�`���̕�
//th ���̃e�N�X�`���̍���
//tcx 
//=======================================================================================
void SpriteDraw(GXTexObj* pTex, float dx, float dy, int dw, int dh, int tx, int ty)
{
		
	u16 tw=GXGetTexObjWidth(pTex);//�e�N�X�`���̕���������//pTex=���̉摜�̕��𒲂ׁA�擾����
	u16 th=GXGetTexObjHeight(pTex);//�e�N�X�`���̍�����������//pTex=���̉摜�̕��𒲂ׁA�擾����
//	float tcx=tx/(float)tw;
//	float tcy=ty/(float)th;
	float tcx=tx/(float)tw;//0���e�N�X�`����=�e�N�X�`����x�\���J�n�ʒu
	float tcy=ty/(float)th;//0���e�N�X�`������=�e�N�X�`����y�\���J�n�ʒu
	
	//float tlx=(tx+(float)dw)/(float)tw;
//	float tlx=(tx+(float)500)/(float)tw;
	float tlx=(tx+(float)tw)/(float)tw;//(�e�N�X�`����x�؂���J�n�ꏊ+�e�N�X�`����)���e�N�X�`����
	//float tly=(ty+(float)dh)/(float)th;
//	float tly=(ty+(float)500)/(float)th;
	float tly=(ty+(float)th)/(float)th;//(�e�N�X�`����y�؂���J�n�ꏊ+�e�N�X�`������)���e�N�X�`������
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	
	
	
			

	
	   	 //�e�N�X�`���}�b�v0�ԂɃe�N�X�`����ݒ�
	  	//���uboy�v�e�N�X�`�����Z�b�g
	  	//�e�N�X�`��(�e�N�X�`���̕��ƍ������擾,�e�N�X�`���̉��Ԗڂ��g�����w��)
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
		//�v���~�e�B�v���_���o�^�J�n
			GXBegin(GX_TRIANGLEFAN,GX_VTXFMT0,4);//�_��`��
				//�_1
				GXPosition3f32(dx,dy,0.0f);//���W
				GXColor4u8(255,255,255,255);//�F
				GXTexCoord2f32(tcx,tcy);
				//�_2
				GXPosition3f32(dx+dw,dy,0.0f);//���W
				GXColor4u8(255,255,255,255);//�F
				GXTexCoord2f32(tlx,tcy);
				//�_3
				GXPosition3f32(dx+dw,dy+dh,0.0f);//���W
				GXColor4u8(255,255,255,255);//�F
				GXTexCoord2f32(tlx,tly);
				//�_4
				GXPosition3f32(dx,dy+dh,0.0f);//���W	
				GXColor4u8(255,255,255,255);//�F
				GXTexCoord2f32(tcx,tly);

			//�v���~�e�B�v���_���o�^�I��
			GXEnd();
////////////////////////////////////////////////////////////////////////////////////////////////////			
			
					//���u��񂲁v�e�N�X�`�����Z�b�g
					//�e�N�X�`��(�e�N�X�`���̕��ƍ������擾,�e�N�X�`���̉��Ԗڂ��g�����w��)
					GXLoadTexObj(pTex,GX_TEXMAP3); 
	  
		//�v���~�e�B�v���_���o�^�J�n
			GXBegin(GX_TRIANGLEFAN,GX_VTXFMT0,4);//�_��`��
				//�_1
				GXPosition3f32(dx,dy,0.0f);//���W
				GXColor4u8(255,255,255,255);//�F
				GXTexCoord2f32(tcx,tcy);
				//�_2
				GXPosition3f32(dx+dw,dy,0.0f);//���W
				GXColor4u8(255,255,255,255);//�F
				GXTexCoord2f32(tlx,tcy);
				//�_3
				GXPosition3f32(dx+dw,dy+dh,0.0f);//���W
				GXColor4u8(255,255,255,255);//�F
				GXTexCoord2f32(tlx,tly);
				//�_4
				GXPosition3f32(dx,dy+dh,0.0f);//���W	
				GXColor4u8(255,255,255,255);//�F
				GXTexCoord2f32(tcx,tly);

			//�v���~�e�B�v���_���o�^�I��
			GXEnd();
			
////////////////////////////////////////////////////////////////////////////////////////////////////////			
				//���u�w�i�v�e�N�X�`�����Z�b�g
					//�e�N�X�`��(�e�N�X�`���̕��ƍ������擾,�e�N�X�`���̉��Ԗڂ��g�����w��)
					GXLoadTexObj(pTex,GX_TEXMAP2); 
						//�v���~�e�B�u���_���o�^�I��
	//	GXEnd();

}


	
	  /*
		//�v���~�e�B�v���_���o�^�J�n
			GXBegin(GX_TRIANGLEFAN,GX_VTXFMT0,4);//�_��`��
				//�_1
				GXPosition3f32(dx,dy,0.0f);//���W
				GXColor4u8(255,255,255,255);//�F
				GXTexCoord2f32(tcx,tcy);//(����̓_)
				//�_2
				GXPosition3f32(dx+dw,dy,0.0f);//���W
				GXColor4u8(255,255,255,255);//�F
				GXTexCoord2f32(tlx,tcy);//(�E��̓_)
				//�_3
				GXPosition3f32(dx+dw,dy+dh,0.0f);//���W
				GXColor4u8(255,255,255,255);//�F
				GXTexCoord2f32(tlx,tly);//(�E���̓_)
				//�_4
				GXPosition3f32(dx,dy+dh,0.0f);//���W	
				GXColor4u8(255,255,255,255);//�F
				GXTexCoord2f32(tcx,tly);//(�����̓_)

			//�v���~�e�B�v���_���o�^�I��
			GXEnd();
		
				//�v���~�e�B�u���_���o�^�J�n
		//�v���~�e�B�u�^�C�v�ƒ��_�t�H�[�}�b�g�ƒ��_���ɒ���
	GXBegin(GX_QUADS,GX_VTXFMT0,4);
	//�v���~�e�B�u���_�Z�b�g�J�n
	GXPosition3f32(0.0f,0.0f,0.0f);//���_���W�@���_����@�@�@�@�@�@//�ʒu
	GXColor4u8(255,255,255,255); //���_�J���[
	GXTexCoord2f32(0.0f,0.0f);//�e�N�X�`�����W�@�e�N�X�`�����W�͌�
	
	GXPosition3f32(900.0f,0.0f,0.0f);//���_���W
	GXColor4u8(255,255,255,255); //���_�J���[
	GXTexCoord2f32(1.0f,0.0f);//�e�N�X�`�����W
	//��ʂ�Y���W��480�����E
	GXPosition3f32(900.0f,480.0f,0.0f);//���_���W�@���_����
	GXColor4u8(255,255,255,255); //���_�J���[
	GXTexCoord2f32(1.0f,1.0f);//�e�N�X�`�����W�@�e�N�X�`�����W�͌�
	
	GXPosition3f32(000.0f,480.0f,0.0f);//���_���W
	GXColor4u8(255,255,255,255); //���_�J���[
	GXTexCoord2f32(0.0f,1.0f);//�e�N�X�`�����W
	
	
	*/

