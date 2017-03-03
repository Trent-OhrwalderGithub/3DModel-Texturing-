#pragma once

class RenderData
{

public:

	RenderData();
	~RenderData();

	RenderData(const RenderData& other) = delete;
	RenderData(RenderData&& other);

	RenderData& operator=(const RenderData& other) = delete;

	void GenerateBuffers(bool generateIndexBuffer = true);
	void Render() const;
	void Bind() const;
	void Unbind() const;

	void setNumberOfIndicies(unsigned int numIndicies) { m_numberOfIndicies = numIndicies; }

	unsigned int getNumberOfIndicies() const { return m_numberOfIndicies; }

	unsigned int& getVAO() { return m_VAO; }
	unsigned int& getVBO() { return m_VBO; }
	unsigned int& getIBO() { return m_IBO; }



protected:

private:

	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;

	unsigned int m_numberOfIndicies;

	bool hasIndexBuffer;
};