#version 150

in vec4 aPosition;
in vec3 aNormal;
out vec3 color;
uniform mat4 uProjectionMatrix;
uniform mat4 uModelViewMatrix;

void main() {
    gl_Position = uProjectionMatrix *uModelViewMatrix* aPosition;
	color = aNormal;
	
}
