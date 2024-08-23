#include "Loader.h"

Mesh LoadOBJ(const char* filepath)
{
	std::vector<unsigned int> vIndices;
	std::vector<unsigned int> tIndices;
	std::vector<unsigned int> nIndices;
	std::ifstream file(filepath);
	if (!file)
	{
		char result[255];
		std::cout << "Failed to load OBJ: " << filepath << std::endl;
		throw std::runtime_error("");
	}
	Mesh m;
	std::string line;
	while (std::getline(file, line))
	{

		std::stringstream ss(line);
		std::string token;
		ss >> token;
		if (token == "v") 
		{
			for (int i = 0; i < 3; i++) 
			{
				ss >> token;			
				m.vertices.push_back(std::stof(token));
			}
		}
		if (token == "vt")
		{
			for (int i = 0; i < 2; i++)
			{
				ss >> token;
				m.texCoords.push_back(std::stof(token));
			}
		}
		if (token == "vn")
		{
			for (int i = 0; i < 3; i++)
			{
				ss >> token;
				m.normals.push_back(std::stof(token));
			}
		}
		if (token == "f")
		{
			while (ss >> token) {
				std::stringstream tokenStream(token);
				std::string indexStr;
				int vertexIndex, textureIndex, normalIndex;

				std::getline(tokenStream, indexStr, '/');
				vertexIndex = std::stoi(indexStr) - 1;
				vIndices.push_back(vertexIndex);

				std::getline(tokenStream, indexStr, '/');
				textureIndex = std::stoi(indexStr) - 1;
				tIndices.push_back(textureIndex);

				std::getline(tokenStream, indexStr, '/');
				normalIndex = std::stoi(indexStr) - 1;
				nIndices.push_back(normalIndex);
			}
		}		
	}
	m.numIdxVert = vIndices.size();
	m.numIdxTex = tIndices.size();
	m.numIdxNorm = nIndices.size();

	m.indices = vIndices;
	m.indices.insert(m.indices.end(), tIndices.begin(), tIndices.end());
	m.indices.insert(m.indices.end(), nIndices.begin(), nIndices.end());
	file.close();
	return m;
}

void QuadsToTris(Mesh &m)
{
	std::cout << "Converting vertex indices from Quads to Triangles\n";
	std::vector<unsigned int> newIdx;
	for (int i = 0; i < m.indices.size(); i += 4) {
		newIdx.push_back(m.indices[i]);
		newIdx.push_back(m.indices[i+1]);
		newIdx.push_back(m.indices[i+2]);
		newIdx.push_back(m.indices[i]);
		newIdx.push_back(m.indices[i+2]);
		newIdx.push_back(m.indices[i+3]);
	}
	m.indices = newIdx;
}


void PrintMesh(Mesh m)
{
	/*
		std::vector<float> vertices;
		std::vector<float> texCoords;
		std::vector<float> normals;
		std::vector<unsigned int> indices;

	*/
	std::cout << "\nVertices - " << sizeof(*m.vertices.data())*m.vertices.size() << " Bytes - " << m.vertices.size() << " floats\n--------------\n\n";
	for (int i = 0; i < m.vertices.size(); i += 3)
		std::cout << m.vertices[i] << ", " << m.vertices[i + 1] << ", " << m.vertices[i + 2] << "\n";
	
	std::cout << "\nTexture Coords - " << sizeof(*m.texCoords.data()) * m.texCoords.size() << " Bytes - " << m.texCoords.size() << " floats\n--------------\n\n";
	for (int i = 0; i < m.texCoords.size(); i += 2)
		std::cout << m.texCoords[i] << ", " << m.texCoords[i + 1] << "\n";
	
	std::cout << "\nNormals - " << sizeof(*m.normals.data()) * m.normals.size() << " Bytes - " << m.normals.size() << " floats\n--------------\n\n";
	for (int i = 0; i < m.normals.size(); i += 3)
		std::cout << m.normals[i] << ", " << m.normals[i + 1] << ", " << m.normals[i + 2] << "\n";
	
	std::cout << "\nVertex Indices - " << sizeof(*m.indices.data()) * m.indices.size() << " Bytes - " << m.indices.size() << " unsigned ints\n--------------\n\n";
	for (int i = 0; i < m.indices.size(); i++) std::cout << m.indices[i] << " ";
	std::cout << "\n\nTexture Indices - " << sizeof(*m.indices.data()) * m.indices.size() << " Bytes - " << m.indices.size() << " unsigned ints\n--------------\n\n";
	
	std::cout << "\nNormal Indices - " << sizeof(*m.indices.data()) * m.indices.size() << " Bytes - " << m.indices.size() << " unsigned ints\n--------------\n\n";
}
