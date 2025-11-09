#version 330 core

in vec4 vColor;

out vec4 FragColor;

uniform float uTheta;

void main(void) {
	float w = 0.25F * cos(3.0F * uTheta) + 0.75F;
	FragColor = vColor * vec4(w, w, w, 1.0F);
}