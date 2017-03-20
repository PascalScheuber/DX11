#pragma once
#include "..\Types.h"
#include <vector>

namespace Engine
{
	namespace PrimitiveType
	{
		class iPrimitiv
		{
		#pragma region Variables
		public:

		protected:
			std::vector<std::vector<Shader::S_Vertex>> m_DebugVertices;

		private:

		#pragma endregion

		#pragma region Methods
		public:

			virtual std::vector<std::vector<Shader::S_Vertex>> GetDebugVertices() =0;

		private:

		#pragma endregion
		};
	}
}
