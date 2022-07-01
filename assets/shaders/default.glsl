#pragma vertex
#version 330  core


in  vec4 position;
out vec4 pos;

void main() {
	// builtin variable for positions
	gl_Position = vec4(position.x, position.y, position.z, position.w);
	pos = vec4(position.x, position.y, position.z, position.w);
}



#pragma fragment
#version 330  core
// fragment shader must have 1 'out', thats the color
out vec4 color;
in vec4 pos;
uniform vec4 u_color;

void main() {
	color = vec4(u_color.x+0.1, u_color.y+0.1,u_color.z+0.1,1.0);
	//color = vec4(pos.x, pos.y, pos.z, 1.0);
	//color = vec4(u_color.x,u_color.y,u_color.z,1.0);
	//gl_FragColor = vec4( , 1.0);
}
