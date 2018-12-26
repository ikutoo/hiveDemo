#version 430 core

uniform vec3 uMaterialAmbient = vec3(0.3, 0.3, 0.3);
uniform vec3 uMaterialDiffuse = vec3(0.3, 1.0, 0.6);
uniform vec3 uMaterialSpecular = vec3(0.9, 0.9, 0.9);
uniform float uMaterialShinness = 10.0;

uniform vec3 uLightDirectionE = vec3(0, 0, -1);
uniform vec3 uLightAmbient = vec3(0.6, 0.6, 0.6);
uniform vec3 uLightDiffuse = vec3(0.9, 0.9, 0.9);
uniform vec3 uLightSpecular = vec3(0.9, 0.9, 0.9);

in vec3 _PositionE;
in vec3 _NormalE;

out vec4 _outFragColor;

vec4 computePhongShading4ParallelLight(vec3 vPositionE, vec3 vNormalE)
{
	vec4 Result;

	Result = vec4(uLightAmbient * uMaterialAmbient, 1.0);

	float t = dot(-normalize(uLightDirectionE), vNormalE);
	if (t > 0.0)
	{
		Result.xyz += uLightDiffuse * uMaterialDiffuse * t;
		Result.xyz += uLightSpecular * uMaterialSpecular * pow(max(dot(normalize(reflect(uLightDirectionE, vNormalE)), normalize(-vPositionE)), 0), uMaterialShinness);
	}

	return Result;
}

void main()
{
	_outFragColor = computePhongShading4ParallelLight(_PositionE, normalize(_NormalE));
}