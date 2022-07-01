#include "Shader.hpp"

namespace cyx {
    Shader::Shader(const char* filepath)
    {
        if (filepath == NULL) {
            set_default(ShaderType::VERTEX);
            set_default(ShaderType::FRAGMENT);
        }
        else {
            std::ifstream shaderfile(filepath);
            std::string line;

            ShaderType interpret_source_as = ShaderType::NONE;
            // Stream to add our vertex
            std::stringstream vertex, fragment;
            assert(shaderfile && "Coundt open shader file somehow");

            bool found_pragma_vertex = false, found_pragma_fragment = false;
            
            while (std::getline(shaderfile, line)) {
            
                if (line.find("#pragma") != std::string::npos) {
                    if  (line.find("vertex") != std::string::npos) {
                        // add to vertex string
                        interpret_source_as = ShaderType::VERTEX;
                        continue;
                    }
                    else if ((line.find("fragment") != std::string::npos)) {
                        // add to fragment string
                        interpret_source_as = ShaderType::FRAGMENT;
                        continue;
                    }
                }

                // Adding to the actual string
                switch (interpret_source_as)
                {
                    case cyx::ShaderType::VERTEX: {
                        vertex << line << "\n";
                        break;
                    }
                    case cyx::ShaderType::FRAGMENT: {

                        fragment << line << "\n";
                        break;
                    }
                    case cyx::ShaderType::NONE: {
                        // Nothing should be added
                        break;
                    }
                    default: {

                        assert(0 && "unreachable"); 
                    }
                }
            }
            _vertex_source   = vertex.str();
            _fragment_source = fragment.str();        }
    
    }

    Shader::Shader(const char* vertex_src, const char* frag_src)
        :_vertex_source(vertex_src),
         _fragment_source(frag_src)
    {
        if (vertex_src == NULL) {
            set_default(ShaderType::VERTEX);
            std::cout << "[Shader] Vertex Source in NULL \n";
        }    
        if (frag_src == NULL) {
            set_default(ShaderType::FRAGMENT);
            std::cout << "[Shader] Fragment Source in NULL \n";
        }
    }

    Shader::~Shader()
    {
       glDeleteProgram(_programID);
    }

    auto Shader::compile() -> void {
        if (create_program(this->_vertex_source.c_str(), this->_fragment_source.c_str())) {
            std::cout << "[Shader] PROGRAM SUCESSFULLY CREATED\n";
        }
    }


    auto Shader::bind() -> void
    {
        _isbound = true;
        glUseProgram(_programID);
    }

    auto Shader::unbind() -> void
    {
        _isbound = true;
        glUseProgram(0);
    }

    auto Shader::src(ShaderType type) -> const char*
    {
	    return nullptr;
    }

    auto Shader::compile_shader(u32 type, const char* src) -> u32 {
        u32 shader;
        switch (type)
        {
            case GL_VERTEX_SHADER: {
                shader = glCreateShader(GL_VERTEX_SHADER);
                break;
            }

            case GL_FRAGMENT_SHADER: {
                shader = glCreateShader(GL_FRAGMENT_SHADER);
                break;
            }

            default: {
                std::cout << "others shaders are not supported" "\n";
                return false;
            }
        }

        glShaderSource(shader, 1, &src, NULL);
        glCompileShader(shader);
        // check for error
        i32 sucess;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &sucess);
        if (sucess != GL_TRUE) {
            char info[512];
            glGetShaderInfoLog(shader, 512, NULL, info);
            std::cout << "[ERROR]: " << info << "\n";
            assert(0 && "look at console");
            return false;
        }
    
        return shader;
    }

    auto Shader::set_default(ShaderType type) -> void {
        if (type == ShaderType::VERTEX) {
            _vertex_source = R"(
                #version 330  core
                in  vec4 position;
                out  vec4 pos;
                void main() {
                    // builtin variable for positions
                    gl_Position = vec4(position.x, position.y, position.z, position.w);
                    pos = vec4(position.x, position.y, position.z, position.w);
                }
            )";
        }
        if (type == ShaderType::FRAGMENT) {
            _fragment_source = R"(
                #version 330  core
                // fragment shader must have 1 'out', thats the color
                out vec4 color;
                in vec4 pos;

                void main() {
                    //color = vec4(1.0, 0.0, 0.0, 1.0);
                    color = vec4(pos.z+pos.x, pos.z+pos.y, pos.z+pos.x, 1.0);
                }
            )";

        }
    }
    auto Shader::create_program(const char* vertex_shader_src, const char* frag_shader_src) -> bool {
        _programID = glCreateProgram();

        u32 vertex_shader    = compile_shader(GL_VERTEX_SHADER, vertex_shader_src);
        u32 frag_shader      = compile_shader(GL_FRAGMENT_SHADER, frag_shader_src);

        glAttachShader(_programID, vertex_shader);
        glAttachShader(_programID, frag_shader);

    
        glLinkProgram(_programID);

        valid(*this);
        // check for error
        i32 sucess;
        glGetProgramiv(_programID, GL_LINK_STATUS, &sucess);
        if (sucess != GL_TRUE) {
            glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &sucess);
            char info[512];
            glGetProgramInfoLog(_programID, 512, NULL, info);
            std::cout << "[ERROR]: couldnt link programID: " << _programID << info << "\n";
            assert(0 && "look at console");
            return false;
        }   
        //glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &sucess);
        //if (sucess != GL_TRUE) {
        //    char info[512];
        //    glGetProgramInfoLog(_programID, 512, NULL, info);
        //    std::cout << "[ERROR]: GL_INFO_LOG_LENGT link programID: " << _programID << info << "\n";
        //    assert(0 && "look at console");
        //    return false;
        //}
        glDeleteShader(vertex_shader);
        glDeleteShader(frag_shader);
        return true;
    }

    auto Shader::valid(GLuint id) -> bool {
        glValidateProgram(id);
        // check for error
        i32 sucess;
        glGetProgramiv(id, GL_VALIDATE_STATUS, &sucess);
        if (sucess != GL_TRUE) {
            glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &sucess);
            char info[512];
            glGetProgramInfoLog(_programID, 512, NULL, info);
            std::cout << "[ERROR]: couldnt link programID: " << _programID << info << "\n";
            assert(0 && "look at console");
            return false;
        }   
        return true;
    }

    auto Shader::uniform_float4(const char* var, f32* values) -> void {
        GLint location = glGetUniformLocation(_programID, var);
        assert(location != -1 && "BAD uniform Location");
        glUniform4f(location, values[0], values[1], values[2], values[4]);
    }
    auto Shader::uniform_float4(const char* var, float* values) -> void
    {
    }
    auto Shader::uniform_float3(const char* var, f32* values) -> void {
        GLint location = glGetUniformLocation(_programID, var);
        assert(location != -1 && "BAD uniform Location");
        glUniform3f(location, values[0], values[1], values[2]);
    }

    auto Shader::uniform_float2(const char* var, f32* values) -> void {
        GLint location = glGetUniformLocation(_programID, var);
        assert(location != -1 && "BAD Get unifor Locatioin");
        glUniform2f(location, values[0], values[1]);
    }

    auto Shader::uniform_float(const char* var, f32 value) -> void {
        i32 location = glGetUniformLocation(_programID, var);
        assert(location != -1 && "BAD Get unifor Locatioin");
        glUniform1f(location, value);
    }


    
}