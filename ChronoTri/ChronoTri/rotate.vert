#version 330 core

in vec4 aPos;
in vec4 aColor;

out vec4 vColor;

uniform float uTheta;

void main(void) {
	gl_Position.x = aPos.x * cos(uTheta) - aPos.y * sin(uTheta);
	gl_Position.y = aPos.x * sin(uTheta) + aPos.y * cos(uTheta);
	gl_Position.zw = aPos.zw;

	vColor = aColor;
}