#pragma vertex
#version 330  core


layout(location = 0) in  vec2 position;
layout(location = 1) in  vec2 tex_coord;
uniform mat4 u_MVP;

out vec2 v_tex_coord;

void main() {
	// builtin variable for positions
	gl_Position = u_MVP * vec4(position.x,position.y,0.0,1.0);
	v_tex_coord = tex_coord;
}

#pragma fragment
#version 330  core

out vec4 color;
in  vec2 v_tex_coord;

uniform sampler2D u_texture;


void main() {
	vec4 tex_color = texture(u_texture, v_tex_coord);
	color = tex_color;
	//color = vec4(1.0,0.0,0.0,1.0);
}
