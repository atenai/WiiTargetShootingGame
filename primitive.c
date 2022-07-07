//=======================================================================================
//
//    [ primitive.c ] �}�`�`�惂�W���[��
//
//	���̃t�@�C���Ɋ֐����쐬����
//=======================================================================================


//----- �C���N���[�h�t�@�C�� -----

#include "primitive.h"
#include <math.h>


//----- �萔��` -----

#define PI (3.141592654f) // ��


//----- �O���[�o���ϐ���` -----

static u8 primitiveR = 255; // �}�`�̐F
static u8 primitiveG = 255;
static u8 primitiveB = 255;


//----- �֐���` -----

//=======================================================================================
// �}�`�`�揀���֐�
//
// Primitive��Draw�֐����ĂԑO�ɃR�[������
//
// ������Setup�֐����Ă΂ꂽ��APrimitive��Draw�֐����Ăԏꍇ�ɂ͍ēx�R�[�����邱��
//=======================================================================================
void PrimitiveSetup(void) 
{
		GXClearVtxDesc();
		GXSetVtxDesc(GX_VA_POS,GX_DIRECT);
		GXSetVtxDesc(GX_VA_CLR0,GX_DIRECT);//�J���[
		
		GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_POS,GX_POS_XYZ,GX_F32,0);	
		GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_CLR0,GX_CLR_RGB,GX_RGB8,0);//�J���[
	//======Wii�ɐF���g���ݒ���s���i�ڍ׌���j

	// �g�p����TEV�X�e�[�W���̐ݒ�
	GXSetNumTevStages(1); // 1��
	    
	// �J���[�`�����l�����̐ݒ�
	GXSetNumChans(1); // 1��
	    
	// ���p�\�ɂ���e�N�X�`�����W���̐ݒ�
    	GXSetNumTexGens(0); // ����Ȃ�
		
	// TEV�Ŏg�p����e�N�X�`���[�J���[�ƃ��X�^���C�Y�J���[�̐ݒ�
	GXSetTevOrder(GX_TEVSTAGE0,     // TEV�X�e�[�W0�̐ݒ�
    	    	  GX_TEXCOORD_NULL, // �e�N�X�`�����W�͎g��Ȃ�
    	          GX_TEX_DISABLE, 	// �e�N�X�`���͎g�p���Ȃ�
    	          GX_COLOR0A0);		// �J���[�`�����l��0�E�A���t�@�`�����l��0���g�p
  
  	// TEV�̊ȈՃJ���[�����ݒ�
    	GXSetTevOp(GX_TEVSTAGE0, // TEV�X�e�[�W0�̐ݒ� 
    	           GX_PASSCLR);  // �O�X�e�[�W�̃J���[�ƃA���t�@���o��
    	                         // ���O�X�e�[�W�����݂��Ȃ��̂Ń��X�^���C�Y�J���[�i�|���S���J���[�j���g�p�����

}


//=======================================================================================
// �}�`�F�ݒ�֐�
//
// �}�`�F���w�肷��
// ���̊֐����Ă΂ꂽ��̐}�`�͂��ׂĂ����Ŏw�肵���F�ɂȂ�
//
// r ... �ԗv�f(0-255)
// g ... �Ηv�f(0-255)
// b ... �v�f(0-255)
//=======================================================================================
void PrimitiveSetColor(u8 r, u8 g, u8 b) 
{
	primitiveR = r;
	primitiveG = g;
	primitiveB = b;
}



//=======================================================================================
// �_�̕`��
//
// x, y ... �_�̕`����W
//=======================================================================================
void PrimitiveDrawPoint(float x, float y)
{
/*
	GXBegin(GX_POINTS, GX_VTXFMT0, 1);
	GXPosition3f32(x, y, 0.0f);
	GXColor3u8(primitiveR, primitiveG, primitiveB); 
	GXEnd();
	*/
	
		//�v���~�e�B�u���_���o�^�J�n
		GXBegin(GX_POINTS,GX_VTXFMT0,1);//�_��`��(1��)
		//��
		//GXPosition3f32(x��,y��);
		//�_1
		GXPosition3f32(x,y,0.0f);
		//GXColor3u8(��,��,��);//�J���[
		GXColor3u8(255,0,0);//�J���[
		GXEnd();//�\���I��
}


//=======================================================================================
// ���̕`��
//
// x0, y0 ... ���̎n�_���W
// x1, y1 ... ���̏I�_���W
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
//�v���~�e�B�u���_���o�^�J�n
		GXBegin(GX_LINES,GX_VTXFMT0,2);//����`��(1�{��)
		//������1(�n�_)
			GXPosition3f32(x0,y0,0.0f);//���W
			//��
			//GXColor3u8(��,��,��);//�J���[
		GXColor3u8(255,0,255);//�J���[
		//������1(�I�_)
			GXPosition3f32(x1,y1,0.0f);//���W
			//��
			//GXColor3u8(��,��,��);//�J���[
	GXColor3u8(255,0,255);//�J���[

		GXEnd();
}




//=======================================================================================
// �l�p�̕`��
//
// x, y ... �l�p�̍�����W
// w, h ... �l�p�̕��ƍ���
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
			//�v���e�B�v���_���o�^�J�n
			GXBegin(GX_TRIANGLEFAN,GX_VTXFMT0,360);//�_��`��
		while(count>0)
		{
				GXPosition3f32(x+r*cosf(count),y-r*sinf(count),0.0f);//���W
				GXColor3u8(255, 0, 0);
				count--;			
		}					
		//�v���e�B�v���_���o�^�I��
		GXEnd();
		*/
	//�v���~�e�B�u���_���o�^�J�n
		GXBegin(GX_LINESTRIP,GX_VTXFMT0,5);//
			//�_����1
			GXPosition3f32(x,y,0.0f);//���W
			//GXColor3u8(��,��,��);//�J���[
		GXColor3u8(255,0,255);//�J���[
			//�_����2
			GXPosition3f32(x+w,y,0.0f);//���W
			//GXColor3u8(��,��,��);//�J���[
		GXColor3u8(255,0,255);//�J���[
			//�_����3
			GXPosition3f32(x+w,y+h,0.0f);//���W
			//GXColor3u8(��,��,��);//�J���[
		GXColor3u8(255,0,255);//�J���[
			//�_����4
			GXPosition3f32(x,y+h,0.0f);//���W
			//GXColor3u8(��,��,��);//�J���[
		GXColor3u8(255,0,255);//�J���[
		//�_����5
			GXPosition3f32(x,y,0.0f);//���W
			//GXColor3u8(��,��,��);//�J���[
		GXColor3u8(255,0,255);//�J���[
		GXEnd();
	

}
//=======================================================================================
// �h��Ԃ��ꂽ���p�`�̕`��
//
// ���W���������o�^���Ă��̍��W�𒸓_�Ƃ��鑽�p�`��`�悷��
//
// v   ... ���W�z��̐擪�A�h���X
// num ... ���W�̐�
//=======================================================================================
void PrimitiveDrawPolygon(Vec2 v[], u16 num)
{
/*
int icount=0;
 			//�v���e�B�v���_���o�^�J�n
			GXBegin(GX_TRIANGLEFAN,GX_VTXFMT0,num);//�_��`��
			for(icount;icount<num;icount++)
			{
			
				GXPosition3f32(v[icount].x,v[icount].y,0.0f);//���W
				GXColor3u8(primitiveR, primitiveG, primitiveB);		
			}
		
			
		//�v���e�B�v���_���o�^�I��
		GXEnd();	
*/
int cnt =1;
		
		
	//�v���~�e�B�u���_���o�^�J�n
		GXBegin(GX_TRIANGLEFAN,GX_VTXFMT0,num);//
		
			//�_����0
			GXPosition3f32(v[0].x,v[0].y,0.0f);//���W
			//GXColor3u8(��,��,��);//�J���[
			GXColor3u8(255,0,255);//�J���[
			
	
			
		for(cnt =1;cnt<num;cnt++){//num��5�Ȃ̂�4�񃋁[�v����
				
			//�_����1�`4
			GXPosition3f32(v[cnt].x,v[cnt].y,0.0f);//���W
			//GXColor3u8(��,��,��);//�J���[
			GXColor3u8(255,0,255);//�J���[
			
			}
			
		GXEnd();
}


//=======================================================================================
// �h��Ԃ��l�p�̕`��
//
// x, y ... �l�p�̍�����W
// w, h ... �l�p�̕��ƍ���
//======================================================================================
void PrimitiveDrawFillRectangle(float x, float y, float w, float h)
{
	/*
			//�v���e�B�v���_���o�^�J�n
			GXBegin(GX_TRIANGLEFAN,GX_VTXFMT0,4);//�_��`��
			//�_1
			GXPosition3f32(x,y,0.0f);//���W
			GXColor3u8(primitiveR, primitiveG, primitiveB);
			//�_2
			GXPosition3f32(x+w,y,0.0f);//���W
			GXColor3u8(primitiveR, primitiveG, primitiveB);
			//�_3
			GXPosition3f32(x+w,y+h,0.0f);//���W
			GXColor3u8(primitiveR, primitiveG, primitiveB);
			//�_4
			GXPosition3f32(x,y+h,0.0f);//���W
			GXColor3u8(primitiveR, primitiveG, primitiveB);			
			
		//�v���e�B�v���_���o�^�I��
		GXEnd();
	*/
	//�v���~�e�B�u���_���o�^�J�n
		GXBegin(GX_TRIANGLEFAN,GX_VTXFMT0,4);//
			//�_����1
			GXPosition3f32(x,y,0.0f);//���W
			//GXColor3u8(��,��,��);//�J���[
		GXColor3u8(255,0,255);//�J���[
			//�_����2
			GXPosition3f32(x+w,y,0.0f);//���W
			//GXColor3u8(��,��,��);//�J���[
		GXColor3u8(255,0,255);//�J���[
			//�_����3
			GXPosition3f32(x+w,y+h,0.0f);//���W
			//GXColor3u8(��,��,��);//�J���[
		GXColor3u8(255,0,255);//�J���[
			//�_����4
			GXPosition3f32(x,y+h,0.0f);//���W
			//GXColor3u8(��,��,��);//�J���[
		GXColor3u8(255,0,255);//�J���[
		GXEnd();


}
