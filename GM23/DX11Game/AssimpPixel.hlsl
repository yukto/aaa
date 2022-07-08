// Assimp�p�s�N�Z���V�F�[�_ (AssimpPixel.hlsl)

// �O���[�o��
cbuffer global : register(b0) {
	matrix	g_mtxWVP;			// ���[���h�~�r���[�~�ˉe�s��
	matrix	g_mtxWorld;			// ���[���h�s��
	matrix	g_mtxTexture;		// �e�N�X�`���s��
	float4	g_vCameraPos;		// ���_���W(���[���h���)
	float4	g_vLightDir;		// ��������(���[���h���)
	float4	g_vLightAmbient;	// ����
	float4	g_vLightDiffuse;	// �g�U��
	float4	g_vLightSpecular;	// ���ʔ��ˌ�
};

// �}�e���A��
cbuffer global2 : register(b1) {
	float4	g_Ambient;			// ���F
	float4	g_Diffuse;			// �g�U�F+�A���t�@
	float4	g_Specular;			// ���ʔ��ːF+���x
	float4	g_Emissive;			// �����F
	float4	g_Flags;			// �g�U�F�e�N�X�`���L��, �����F�e�N�X�`���L��, ���߃e�N�X�`���L��
};

Texture2D    g_texture			: register(t0);	// �e�N�X�`��
Texture2D    g_texEmissive		: register(t1);	// �����e�N�X�`��
Texture2D    g_texTransparent	: register(t2);	// ���߃e�N�X�`��
Texture2D    g_texSpecular		: register(t3);	// ���ʔ��˃e�N�X�`��
SamplerState g_sampler			: register(s0);	// �T���v��

// �p�����[�^
struct VS_OUTPUT {
	float4	Pos			: SV_Position;
	float2	Tex			: TEXCOORD0;
	float3	Normal		: TEXCOORD1;
	float3	PosForPS	: TEXCOORD2;
};

//
// �s�N�Z���V�F�[�_
//
float4 main(VS_OUTPUT input) : SV_Target0
{
	float3 Diff = g_Diffuse.rgb;
	float Alpha = g_Diffuse.a;
	if (g_Flags.x != 0.0f) {		// �e�N�X�`���L��
		float4 TexDiff = g_texture.Sample(g_sampler, input.Tex);
		Diff *= TexDiff.rgb;
		Alpha *= TexDiff.a;
	}
	if (g_Flags.z != 0.0f) {		// �e�N�X�`���L��
		float4 TexTran = g_texTransparent.Sample(g_sampler, input.Tex);
		Alpha *= (TexTran.r * TexTran.g * TexTran.b * TexTran.a);
	}
	if (Alpha <= 0.0f) discard;		// ���S�����Ȃ�`�悵�Ȃ�
	float3 Spec = g_Specular.rgb;
	if (g_Flags.w != 0.0f) {		// �e�N�X�`���L��
		float4 TexSpec = g_texSpecular.Sample(g_sampler, input.Tex);
		Spec *= TexSpec.rgb;
	}

	if (g_vLightDir.x != 0.0f || g_vLightDir.y != 0.0f || g_vLightDir.z != 0.0f) {
		float3 L = normalize(-g_vLightDir.xyz);					// �����ւ̃x�N�g��
		float3 N = normalize(input.Normal);						// �@���x�N�g��
		float3 V = normalize(g_vCameraPos.xyz - input.PosForPS);// ���_�ւ̃x�N�g��
		float3 H = normalize(L + V);							// �n�[�t�x�N�g��
		Diff = g_vLightAmbient.rgb * g_Ambient.rgb +
			g_vLightDiffuse.rgb * Diff * saturate(dot(L, N));	// �g�U�F + ���F
		Spec = Spec * g_vLightSpecular.rgb *
			pow(saturate(dot(N, H)), g_Specular.a);				// ���ʔ��ːF
		Diff += Spec;
	}

	float3 Emis = g_Emissive.rgb;
	if (g_Flags.y != 0.0f) {		// �e�N�X�`���L��
		float4 TexEmis = g_texEmissive.Sample(g_sampler, input.Tex);
		Emis *= (TexEmis.rgb * TexEmis.a);
	}
	Diff += Emis;

	return float4(Diff, Alpha);
}
