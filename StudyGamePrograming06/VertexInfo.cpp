#include "VertexInfo.h"
#include <glew.h>

VertexInfo::VertexInfo(const float* verts, unsigned int numVerts,
	const unsigned int* indices, unsigned int numIndices)
	: mNumVerts(numVerts)
	, mNumIndices(numIndices)
{
	// バーテックス配列オブジェクトをOpenGLに生成し、そのIDをメンバー変数mVertexArrayに保存する
	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);

	// インデックスバッファをOpenGLに生成し、そのIDをメンバー変数mIndexBufferに保存する
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,				// インデックスバッファの指定
		mNumIndices * sizeof(unsigned int),		// データのサイズ
		indices,								// コピー元の配列
		GL_STATIC_DRAW							// このデータを1回だけロードしてその後頻繁に使う
	);

	// 頂点情報バッファを作成
	unsigned int cnt = 8;					//要素数	
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferData(
		GL_ARRAY_BUFFER,						// バッファの種類
		cnt * mNumVerts * sizeof(float),		// コピーするバイト数
		verts,									// コピー元の配列
		GL_STATIC_DRAW							// このデータを1回だけロードしてその後頻繁に使う
	);

	// 頂点属性を指定する。
	// レイアウト0 は　頂点座標(Vector3)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,										// 属性インデックス（１つ目はゼロ）
		3,										// 要素数（ここでは3）
		GL_FLOAT,								// 要素の型
		GL_FALSE,								// 整数型はTrue。
		sizeof(float) * cnt,					// ストライド（通常は頂点情報のサイズ）
		0										// 頂点データの開始位置からこの属性までのオフセット
	);
	// レイアウト1 は　法線ベクトル(Vector3)
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,											// 頂点属性インデックス
		3,											// 成分の数
		GL_FLOAT,									// 各成分の型
		GL_FALSE,									// 整数型はTrue。
		sizeof(float) * cnt,							// ストライド（通常は頂点情報のサイズ）
		reinterpret_cast<void*>(sizeof(float) * 3)	// オフセットポインタ
	);
	// レイアウト2 は　テクスチャ座標(Vector2)
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(
		2,											// 頂点属性インデックス
		2,											// 成分の数
		GL_FLOAT,									// 各成分の型
		GL_FALSE,									// 整数型はTrue。
		sizeof(float) * cnt,							// ストライド（通常は各頂点のサイズ）
		reinterpret_cast<void*>(sizeof(float) * 6)	// オフセットポインタ
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
