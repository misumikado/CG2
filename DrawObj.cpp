#include"DrawObj.h"

Model::Model() {};

Model::~Model() {};

void Model::Update(ID3D12Device* device, XMFLOAT3 vertices[3], uint16_t indices[3])
{
	for (int i = 0; i < 3; i++)
	{
		this->vertices[i] = vertices[i];
		this->indices[i] = indices[i];
	}

	//���_�f�[�^�̑S�̂̃T�C�Y = ���_�f�[�^����̃T�C�Y * ���_�f�[�^�̗v�f��
	sizeVB = static_cast<UINT>(sizeof(XMFLOAT3) * _countof(this->vertices));

	//���_�o�b�t�@�̐ݒ�

	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;  //GPU�ւ̓]���p


	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeVB; //���_�f�[�^�S�̂̃T�C�Y
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//���_�o�b�t�@�̍쐬
	vertBuff = nullptr;
	result = device->CreateCommittedResource
	(
		&heapProp,  //�q�[�v�ݒ�
		D3D12_HEAP_FLAG_NONE,
		&resDesc,   //���\�[�X�ݒ�
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff)
	);
	assert(SUCCEEDED(result));

	//GPU��̃o�b�t�@�ɑΉ��������z������(���C����������)���擾
	vertMap = nullptr;
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	assert(SUCCEEDED(result));

	//�O���_�ɑ΂���
	for (int i = 0; i < _countof(this->vertices); i++)
	{
		vertMap[i] = vertices[i];   //���W���R�s�[
	}

	//�q���������
	vertBuff->Unmap(0, nullptr);

	//GPU���z�A�h���X
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	//���_�o�b�t�@�̃T�C�Y
	vbView.SizeInBytes = sizeVB;
	//���_����̃f�[�^�T�C�Y
	vbView.StrideInBytes = sizeof(XMFLOAT3);

	//�C���f�b�N�X�f�[�^�̑S�̃T�C�Y
	sizeIB = static_cast<UINT>(sizeof(uint16_t) * _countof(this->indices));

	//���\�[�X�ݒ�
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeIB; //���_�f�[�^�S�̂̃T�C�Y
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//�C���f�b�N�X�o�b�t�@�̐���
	indexBuff = nullptr;
	result = device->CreateCommittedResource
	(
		&heapProp,//�q�[�v�ݒ�
		D3D12_HEAP_FLAG_NONE,
		&resDesc,//���\�[�X�ݒ�
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&indexBuff)
	);

	//�C���f�b�N�X�o�b�t�@���}�b�s���O
	indexMap = nullptr;
	result = indexBuff->Map(0, nullptr, (void**)&indexMap);
	//�S�C���f�b�N�X�ɑ΂���
	for (int i = 0; i < _countof(this->indices); i++)
	{
		indexMap[i] = indices[i]; //�C���f�b�N�X���R�s�[
	}
	//�}�b�s���O����
	indexBuff->Unmap(0, nullptr);

	ibView.BufferLocation = indexBuff->GetGPUVirtualAddress();
	ibView.Format = DXGI_FORMAT_R16_UINT;
	ibView.SizeInBytes = sizeIB;

};

void Model::Draw(ID3D12GraphicsCommandList* commandList, ID3D12Resource* constBuffMaterial)
{
	//���_�o�b�t�@�r���[�̐ݒ�R�}���h
	commandList->IASetVertexBuffers(0, 1, &vbView);
	//�C���f�b�N�X�o�b�t�@�r���[�̐ݒ�R�}���h
	commandList->IASetIndexBuffer(&ibView);
	//�萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	commandList->SetGraphicsRootConstantBufferView(0, constBuffMaterial->GetGPUVirtualAddress());
	//�`��R�}���h
	commandList->DrawIndexedInstanced(_countof(this->indices), 1, 0, 0, 0);  //�S�Ă̒��_���g���ĕ`��
};