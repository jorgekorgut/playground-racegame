#pragma once
#include <scene/GameObject.h>
#include <Engine.h>
#include <math/Noise.h>
#include <scene/ModelLine.h>
#include "math/Noise.h"

class Terrain {
public:
	Terrain()
	{

		float amplitude = 1.0f;

		const siv::PerlinNoise::seed_type seed = 123456u;
		const siv::PerlinNoise perlin{ seed };

		int chunkYSize = 150;
		int chunkXSize = 150;

		float distanceX = 1.0f / (chunkXSize - 1);
		float distanceY = 1.0f / (chunkYSize - 1);

		std::unique_ptr<ModelPlane> modelPlane = std::make_unique<ModelPlane>(chunkXSize - 1, chunkYSize - 1);
		std::shared_ptr<Transform> transformPlane = std::make_shared<Transform>(nullptr, glm::vec3(0), glm::vec3(90, 0, 0), glm::vec3(1));

		for (int iy = 0; iy < chunkYSize; iy++)
		{
			for (int ix = 0; ix < chunkXSize; ix++)
			{
				float x = -0.5f + ix * distanceX;
				float y = -0.5f + iy * distanceY;

				const float z = (float)perlin.octave2D_01((ix * 0.01), (iy * 0.01), 4) * amplitude;
				int vertexIndex = ix + iy * chunkXSize;
				glm::vec3 position = glm::vec3(x, y, z);

				modelPlane->meshes[0]->vertices[vertexIndex].Position = position;

				// Calculate normals using the surrounding vertices
				glm::vec3 eUp = glm::vec3(x, y + distanceY, (float)perlin.octave2D_01((ix * 0.01), ((iy + 1) * 0.01), 4) * amplitude);
				glm::vec3 eRight = glm::vec3(x + distanceX, y, (float)perlin.octave2D_01(((ix + 1) * 0.01), ((iy + 1) * 0.01), 4) * amplitude);
				glm::vec3 eDown = glm::vec3(x, y - distanceY, (float)perlin.octave2D_01((ix * 0.01), ((iy - 1) * 0.01), 4) * amplitude);
				glm::vec3 eLeft = glm::vec3(x - distanceX, y, (float)perlin.octave2D_01(((ix - 1) * 0.01), ((iy + 1) * 0.01), 4) * amplitude);

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
		GameObject terrainObject(transformPlane, glm::vec3(0.5, 0.5, 0.5), std::move(modelPlane));
		Engine::GetInstance().sceneManager.objects.emplace_back(terrainObject);
	}

private :
	std::vector<GameObject> terrains;
};