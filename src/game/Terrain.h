#pragma once
#include <scene/GameObject.h>
#include <Engine.h>
#include <math/Noise.h>
#include <scene/ModelLine.h>
#include "math/Noise.h"

class Terrain : public WidgetData {
public:
	float amplitude = 1.0;
	float oldAmplitude = amplitude;
	std::vector<std::shared_ptr<ModelPlane>> modelPlaneList;

	int chunkYVertexCount = 25;
	int chunkXVertexCount = 25;
	int chunksXCount = 20;
	int chunksYCount = 20;
	float chunkXSize = 1;
	float chunkYSize = 1;

	void UpdateData() override
	{
		ImGui::SliderFloat("Amplitude", &amplitude, 0.0f, 1.0f);

		if (oldAmplitude != amplitude)
		{
			GenerateChunks();
			oldAmplitude = amplitude;
		}
	}

	Terrain()
	{
		modelPlaneList.reserve((chunksXCount+1) * (chunksYCount+1));

		for (int j = -chunksXCount / 2; j < chunksXCount / 2; j++)
		{
			for (int i = -chunksYCount / 2; i < chunksYCount / 2; i++)
			{
				modelPlaneList.emplace_back(std::make_shared<ModelPlane>(chunkXVertexCount - 1, chunkYVertexCount - 1));
			}
		}
		

		GenerateChunks();

		for (std::shared_ptr<ModelPlane> currentModel : modelPlaneList)
		{
			std::shared_ptr<Transform> transformPlane = std::make_shared<Transform>(nullptr, glm::vec3(0, 0, 0), glm::vec3(90, 0, 0), glm::vec3(1));
			GameObject terrainObject(transformPlane, glm::vec3(0.5, 0.5, 0.5), currentModel);
			Engine::GetInstance().sceneManager.objects.emplace_back(terrainObject);
		}
	}

	void GenerateChunks()
	{
		for (int j = -chunksXCount / 2; j < chunksXCount / 2; j++)
		{
			for (int i = -chunksYCount / 2; i < chunksYCount / 2; i++)
			{
				int planeIndex = (j + chunksXCount / 2) * (chunksYCount / 2) * 2 + i + chunksYCount / 2;

				std::shared_ptr<ModelPlane> currentModel = modelPlaneList[planeIndex];

				float offsetX = chunkXSize * j;
				float offsetY = chunkYSize * i;

				GenerateMesh(currentModel, offsetX, offsetY);
			}
		}
	}

	void GenerateMesh(std::shared_ptr<ModelPlane> modelPlane, float offsetX, float offsetY)
	{
		const siv::PerlinNoise::seed_type seed = 123456u;
		const siv::PerlinNoise perlin{ seed };

		float distanceX = 1.0f / modelPlane->numCol;
		float distanceY = 1.0f / modelPlane->numRow;

		int chunkXVertexCount = modelPlane->numCol + 1;
		int chunkYVertexCount = modelPlane->numRow + 1;

		for (int iy = 0; iy < chunkYVertexCount; iy++)
		{
			for (int ix = 0; ix < chunkXVertexCount; ix++)
			{
				float x = -0.5f + ix * distanceX + offsetX;
				float y = -0.5f + iy * distanceY + offsetY;

				const float z = (float)perlin.octave2D_01(x, y, 4) * amplitude;
				int vertexIndex = ix + iy * chunkXVertexCount;
				glm::vec3 position = glm::vec3(x, y, z);

				modelPlane->meshes[0]->vertices[vertexIndex].Position = position;

				// Calculate normals using the surrounding vertices
				glm::vec3 eUp = glm::vec3(x, y + distanceY, (float)perlin.octave2D_01(x, y + distanceY, 4) * amplitude);
				glm::vec3 eRight = glm::vec3(x + distanceX, y, (float)perlin.octave2D_01(x + distanceX, y, 4) * amplitude);
				glm::vec3 eDown = glm::vec3(x, y - distanceY, (float)perlin.octave2D_01(x, y - distanceY, 4) * amplitude);
				glm::vec3 eLeft = glm::vec3(x - distanceX, y, (float)perlin.octave2D_01(x - distanceX, y , 4) * amplitude);

				// Compute cross products of consecutive edges (like making a fan)
				glm::vec3 n1 = cross(eUp - position, eLeft - position);
				glm::vec3 n2 = cross(eLeft - position, eDown - position);
				glm::vec3 n3 = cross(eDown - position, eRight - position);
				glm::vec3 n4 = cross(eRight - position, eUp - position);

				// Sum them
				glm::vec3 normal = n1 + n2 + n3 + n4;

				// Normalize
				normal = glm::normalize(normal);
				modelPlane->meshes[0]->vertices[vertexIndex].Normal = normal;

				//Point debugged normal in the correct direction e1(1,0,0)
				//std::unique_ptr<ModelLine> line = std::make_unique<ModelLine>();
				//std::shared_ptr<Transform> lineTransform = std::make_shared<Transform>();
				//lineTransform->parent = transformPlane;
				//lineTransform->position = position;
				//lineTransform->scale = glm::vec3(1.0f);

				//glm::vec3 from(1, 0, 0); 
				//glm::vec3 to = normal;
				//float angle = 0;
				//glm::vec3 axis = from;
				//glm::vec3 crossProd = glm::cross(from, to);
				//// If the vectors are nearly parallel, skip creating the line to avoid instability
				//if (glm::length(crossProd) > 0.0001f) {
				//	axis = glm::normalize(crossProd);
				//	angle = acos(glm::dot(to, from) / (glm::length(to) * glm::length(from)));
				//}
				//glm::quat q = glm::angleAxis(angle, axis);
				//glm::vec3 eulerDeg = glm::degrees(glm::eulerAngles(q));
				//lineTransform->rotation = eulerDeg;

				//lineTransform->position += glm::vec3(0, 0, 0);
				//lineTransform->scale = glm::vec3(0.1f);
				//
				//GameObject lineObject(lineTransform, glm::vec3(0, 1, 0), std::move(line));
				//Engine::GetInstance().sceneManager.debugObjects.emplace_back(lineObject);
			}
		}

		modelPlane->meshes[0]->UpdateMesh();
	}

};