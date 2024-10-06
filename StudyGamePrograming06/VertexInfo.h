#pragma once
class VertexInfo
{
public:
	VertexInfo(const float* verts, unsigned int numVerts,
		const unsigned int* indices, unsigned int numIndices);
	~VertexInfo();

	// ���̒��_�z����A�N�e�B�u�ɂ���i�`��ł���悤�ɂ���j
	void SetActive();

	unsigned int GetNumIndices() const { return mNumIndices; }
	unsigned int GetNumVerts() const { return mNumVerts; }
private:
	unsigned int mNumVerts;		// ���_�o�b�t�@�ɂ��钸�_�̐�
	unsigned int mNumIndices;	// �C���f�b�N�X�o�b�t�@�ɂ���C���f�b�N�X�̐�
	unsigned int mVertexBuffer;	// ���_�o�b�t�@��OpenGL ID
	unsigned int mIndexBuffer;	// �C���f�b�N�X�o�b�t�@��OpenGL ID
	unsigned int mVertexArray;	// ���_�z��I�u�W�F�N�g��OpenGL ID
};

