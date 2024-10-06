#pragma once
class VertexInfo
{
public:
	VertexInfo(const float* verts, unsigned int numVerts,
		const unsigned int* indices, unsigned int numIndices);
	~VertexInfo();

	// この頂点配列をアクティブにする（描画できるようにする）
	void SetActive();

	unsigned int GetNumIndices() const { return mNumIndices; }
	unsigned int GetNumVerts() const { return mNumVerts; }
private:
	unsigned int mNumVerts;		// 頂点バッファにある頂点の数
	unsigned int mNumIndices;	// インデックスバッファにあるインデックスの数
	unsigned int mVertexBuffer;	// 頂点バッファのOpenGL ID
	unsigned int mIndexBuffer;	// インデックスバッファのOpenGL ID
	unsigned int mVertexArray;	// 頂点配列オブジェクトのOpenGL ID
};

