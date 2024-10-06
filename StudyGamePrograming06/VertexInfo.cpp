#include "VertexInfo.h"
#include <glew.h>

VertexInfo::VertexInfo(const float* verts, unsigned int numVerts,
	const unsigned int* indices, unsigned int numIndices)
	: mNumVerts(numVerts)
	, mNumIndices(numIndices)
{
	// �o�[�e�b�N�X�z��I�u�W�F�N�g��OpenGL�ɐ������A����ID�������o�[�ϐ�mVertexArray�ɕۑ�����
	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);

	// �C���f�b�N�X�o�b�t�@��OpenGL�ɐ������A����ID�������o�[�ϐ�mIndexBuffer�ɕۑ�����
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,				// �C���f�b�N�X�o�b�t�@�̎w��
		mNumIndices * sizeof(unsigned int),		// �f�[�^�̃T�C�Y
		indices,								// �R�s�[���̔z��
		GL_STATIC_DRAW							// ���̃f�[�^��1�񂾂����[�h���Ă��̌�p�ɂɎg��
	);

	// ���_���o�b�t�@���쐬
	unsigned int cnt = 8;					//�v�f��	
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferData(
		GL_ARRAY_BUFFER,						// �o�b�t�@�̎��
		cnt * mNumVerts * sizeof(float),		// �R�s�[����o�C�g��
		verts,									// �R�s�[���̔z��
		GL_STATIC_DRAW							// ���̃f�[�^��1�񂾂����[�h���Ă��̌�p�ɂɎg��
	);

	// ���_�������w�肷��B
	// ���C�A�E�g0 �́@���_���W(Vector3)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,										// �����C���f�b�N�X�i�P�ڂ̓[���j
		3,										// �v�f���i�����ł�3�j
		GL_FLOAT,								// �v�f�̌^
		GL_FALSE,								// �����^��True�B
		sizeof(float) * cnt,					// �X�g���C�h�i�ʏ�͒��_���̃T�C�Y�j
		0										// ���_�f�[�^�̊J�n�ʒu���炱�̑����܂ł̃I�t�Z�b�g
	);
	// ���C�A�E�g1 �́@�@���x�N�g��(Vector3)
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,											// ���_�����C���f�b�N�X
		3,											// �����̐�
		GL_FLOAT,									// �e�����̌^
		GL_FALSE,									// �����^��True�B
		sizeof(float) * cnt,							// �X�g���C�h�i�ʏ�͒��_���̃T�C�Y�j
		reinterpret_cast<void*>(sizeof(float) * 3)	// �I�t�Z�b�g�|�C���^
	);
	// ���C�A�E�g2 �́@�e�N�X�`�����W(Vector2)
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(
		2,											// ���_�����C���f�b�N�X
		2,											// �����̐�
		GL_FLOAT,									// �e�����̌^
		GL_FALSE,									// �����^��True�B
		sizeof(float) * cnt,							// �X�g���C�h�i�ʏ�͊e���_�̃T�C�Y�j
		reinterpret_cast<void*>(sizeof(float) * 6)	// �I�t�Z�b�g�|�C���^
	);
}

VertexInfo::~VertexInfo()
{
	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mIndexBuffer);
	glDeleteVertexArrays(1, &mVertexArray);
}

void VertexInfo::SetActive()
{
	glBindVertexArray(mVertexArray);
}
