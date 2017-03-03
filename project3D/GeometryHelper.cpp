#include "GeometryHelper.h"
#include <gl_core_4_4.h>
#include <glm\glm.hpp>
#include "RenderData.h"

namespace GeometryHelper
{

	RenderData* CreateGrid(unsigned int rows, unsigned int cols, float width, float height, glm::vec4 colour)
	{
		simpleVertex* vertices = new simpleVertex[rows * cols];
		
		float rowSpacing = width / (cols - 1);
		float colSpacing = height / (rows - 1);

		for (unsigned int r = 0; r < rows; ++r)
		{
			for (unsigned int c = 0; c < cols; ++c)
			{
				simpleVertex& vert = vertices[r * cols + c];
				vert.position = glm::vec4(
					-(width / 2) + (colSpacing * c), 
					0.0f,
					-(height / 2) + (rowSpacing * r),
					1.0f);

				vert.colour = colour;
			}
		}

		unsigned int* indices = new unsigned[(rows - 1) * (cols - 1) * 6];
		unsigned int index = 0;
		for (unsigned int r = 0; r < (rows - 1); ++r)
		{
			for (unsigned int c = 0; c < (cols - 1); ++c)
			{
				// Triangle
				indices[index++] = r * cols + c;
				indices[index++] = (r + 1) * cols + c;
				indices[index++] = (r + 1) * cols + (c + 1);

				// Triangle 2

				indices[index++] = r * cols + c;
				indices[index++] = (r + 1) * cols + (c + 1);
				indices[index++] = r * cols + (c + 1);
			}
		}

		unsigned int numberOfIndices = (rows - 1) * (cols - 1) * 6;

		RenderData* renderData = new RenderData();
		renderData->GenerateBuffers();
		renderData->Bind();
		glBufferData(GL_ARRAY_BUFFER,
			(rows * cols) * sizeof(simpleVertex), vertices, GL_STATIC_DRAW);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			numberOfIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);


		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0,4,GL_FLOAT,false,sizeof(simpleVertex),(char*)offsetof(simpleVertex, position));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(simpleVertex), (char*)offsetof(simpleVertex, colour));

		renderData->setNumberOfIndicies(numberOfIndices);
		renderData->Unbind();

		delete[] vertices;
		delete[] indices;

		return renderData;
	}

	RenderData * CreateQuad(float width, float height, glm::vec3 facingDirection)
	{
		return nullptr;
	}

}
