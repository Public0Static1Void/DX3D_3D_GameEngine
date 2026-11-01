struct VSInput
{
    float3 position : POSITION0;
    float4 color : COLOR0;
};
struct VSOutput
{
    float4 position : SV_Position; 
    float4 color : COLOR0;
};
cbuffer TransformBuffer : register(b0)
{
    row_major float4x4 worldViewProj;
}

VSOutput VSMain(VSInput input)
{
    VSOutput output;
    //output.position = float4(input.position.xyz, 1);
    output.position = mul(float4(input.position.xyz, 1), worldViewProj);
    output.color = input.color;
    return output;
}
float4 PSMain(VSOutput output) : SV_Target
{
    return output.color;
}