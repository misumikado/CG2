cbuffer ConstBufferDataMaterial:register(b0)
{
	float4 color;//色(RGBA)
}

//3D変換行列
cbuffer ConstBufferDataTransform:register(b1)
{
	matrix mat;//3D変換行列
};

struct VSOutput
{
	float4 svpos : SV_POSITION;
	float2 uv :TEXCOORD;
};