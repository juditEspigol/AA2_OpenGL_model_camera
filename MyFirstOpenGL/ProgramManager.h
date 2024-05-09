#pragma once
#include <GL/glew.h>
#include <vector>

#define PROGRAM_MANAGER ProgramManager::Instance()

class ProgramManager {
private:

	ProgramManager() = default;

	ProgramManager(const ProgramManager&) = delete;
	ProgramManager& operator =(const ProgramManager&) = delete;

public:

	inline static ProgramManager& Instance()
	{
		static ProgramManager programManager;
		return programManager;
	}

	std::vector<GLuint> compiledPrograms;

	inline void DeleteAllPrograms()
	{
		for (int i = 0; i < compiledPrograms.size(); i++)
			glDeleteProgram(compiledPrograms[i]);
	}
};