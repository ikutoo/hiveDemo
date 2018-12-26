#version 430 core

uniform mat4 hive_ModelMatrix;
uniform mat4 hive_ViewMatrix;
uniform mat4 hive_ProjectionMatrix;
uniform mat4 hive_NormalMatrix;

layout (location = 0) in vec3 _inVertexPosition;
layout (location = 1) in vec3 _inVertexNormal;

out vec3 _PositionE;
out vec3 _NormalE;

void main()
{
	_PositionE = (hive_ViewMatrix * hive_ModelMatrix * vec4(_inVertexPosition, 1.0)).xyz;
	_NormalE = normalize(mat3(hive_NormalMatrix) * _inVertexNormal);
	gl_Position = hive_ProjectionMatrix * vec4(_PositionE, 1.0);
}