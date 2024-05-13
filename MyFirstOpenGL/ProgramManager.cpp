#include "ProgramManager.h"

void ProgramManager::InitShader(std::string vShader, std::string gShader, std::string fShader)
{
	ShaderProgram program = ShaderProgram(vShader, gShader, fShader);
	compiledPrograms.push_back(CreateProgram(program));
}

void ProgramManager::DeleteAllPrograms()
{
	for (int i = 0; i < compiledPrograms.size(); i++)
		glDeleteProgram(compiledPrograms[i]);
}
