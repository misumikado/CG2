#include<windows.h>
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#include<vector>
#include<string>
#include<d3dcompiler.h>
#include<DirectXMath.h>
#include<dinput.h>

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

using namespace DirectX;

class Model
{
public:
	Model();
	~Model();
	void Update(ID3D12Device* device, XMFLOAT3 vertices[3], uint16_t indices[3]);
	void Draw(ID3D12GraphicsCommandList* commandList, ID3D12Resource* constBuffMaterial);

public:
	HRESULT result;

	//���_�f�[�^�̑S�̂̃T�C�Y = ���_�f�[�^����̃T�C�Y * ���_�f�[�^�̗v�f��
	UINT sizeVB;

	//���_�o�b�t�@�̐ݒ�
	D3D12_HEAP_PROPERTIES heapProp{};        //�q�[�v�ݒ�

	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC resDesc{};

	//���_�o�b�t�@�̍쐬
	ID3D12Resource* vertBuff;

	//���_�o�b�t�@�r���[�̍쐬
	D3D12_VERTEX_BUFFER_VIEW vbView{};

	//GPU��̃o�b�t�@�ɑΉ��������z������(���C����������)���擾
	XMFLOAT3* vertMap;



	//�C���f�b�N�X�f�[�^�̑S�̃T�C�Y
	UINT sizeIB;

	//�C���f�b�N�X�o�b�t�@�̐���
	ID3D12Resource* indexBuff;

	//�C���f�b�N�X�o�b�t�@���}�b�s���O
	uint16_t* indexMap;

	//�C���f�b�N�X�o�b�t�@�r���[�̍쐬
	D3D12_INDEX_BUFFER_VIEW ibView{};


	//���_�f�[�^
	XMFLOAT3 vertices[3];

	//�C���f�b�N�X�f�[�^
	uint16_t indices[3];
};

