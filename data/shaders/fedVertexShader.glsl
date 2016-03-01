#version 120

/*
 * Values that stay constant for the whole mesh.
 * (see glGetUniformLocation() & glUniform()
 */
uniform mat4 modelViewProjection;
uniform float sinVar;

/*
 * Input vertex data, different for all executions of this shader.
 * (see glGetAttribLocation() & glGenBuffer() & glBindBuffer()...
 */
attribute vec3 modelVertex;
attribute vec3 vertexColor;


/*
 * sent this variable to the fragment shader!!!
 */
varying vec3 fragmentColor;
varying float forwardSin;


void main() {

	// Output position of the vertex, in clip space : MVP * position
	gl_Position =  modelViewProjection * vec4(modelVertex ,1);

	fragmentColor = vertexColor;
	forwardSin = sinVar;
	//fragmentColor = vec3(sinVar, sinVar, 0);
}

