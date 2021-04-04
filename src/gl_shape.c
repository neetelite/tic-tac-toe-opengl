void
rec2_draw(struct Rec2 *rec, Vec4 color)
{
	struct GL_Program *program = gl_get_program(STR("quad.glsl"));
	gl_program_bind(program->handle);

	struct GL_Uniform *u_mvp = gl_program_get_uniform(program, STR("u_mvp"));
	gl_uniform_mat4(u_mvp->location, gl.projection_2d);

	struct GL_Uniform *u_color = gl_program_get_uniform(program, STR("u_color"));
	gl_uniform_vec4(u_color->location, color);

	u32 triangle_count = 2;
	glDrawArrays(GL_TRIANGLES, 0, triangle_count * 3);

	gl_program_unbind();
}

void
box2_draw(struct Box2 *box, f32 z, Vec4 color)
{
	struct GL_Program *program = gl_get_program(STR("quad.glsl"));
	gl_program_bind(program->handle);

	Vec3 pos = VEC3(box->pos.x, box->pos.y, z);
	Vec3 dim = VEC3(box->dim.x, box->dim.y, 0.0);
	Mat4 mvp = mat4_m(gl.projection_2d, mat4_transform3(pos, dim, VEC3_ZERO));

	struct GL_Uniform *u_mvp = gl_program_get_uniform(program, STR("u_mvp"));
	gl_uniform_mat4(u_mvp->location, mvp);

	struct GL_Uniform *u_color = gl_program_get_uniform(program, STR("u_color"));
	gl_uniform_vec4(u_color->location, color);

	u32 triangle_count = 2;
	glDrawArrays(GL_TRIANGLES, 0, triangle_count * 3);

	gl_program_unbind();
}