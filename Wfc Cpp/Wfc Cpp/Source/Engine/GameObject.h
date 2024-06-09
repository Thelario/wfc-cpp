#pragma once

#include <glm/glm.hpp>
#include <string>
#include <SDL.h>
#include <unordered_map>

#include "TexturesManager.h"

namespace Satellite
{
	enum ColliderTag { NONE, PLAYER, BULLET, OBSTACLE, ENEMY, HEALTH_POWERUP };

	class GameObject
	{
	public:
		bool enabled = true;
		bool renderable = true;
		bool collidable = false;

	protected:

		// Transform data

		glm::vec2 position;
		glm::vec2 scale;
		double rotation;

		// Sprite data

		std::string texture_id;
		int width;
		int height;
		int z_index;
		int tile_id;
		bool flip_x;
		bool center_aligned;
		SDL_Color color;

		// Collider data

		glm::vec2 size;
		glm::vec2 offset;
		SDL_Color collider_color;
		ColliderTag tag;
		std::unordered_map<GameObject*, bool> collision_info;

	public:
		GameObject(glm::vec2 position, glm::vec2 scale, double rotation, const std::string& texture_id, int width, int height,
			bool flip_x, int tile_id = -1, bool center_aligned = true, int z_index = 0, SDL_Color color = { 255, 255, 255, 255 },
			bool enabled = true, bool renderable = true, bool collidable = false, glm::vec2 size = glm::vec2(0),
			glm::vec2 offset = glm::vec2(0), ColliderTag tag = ColliderTag::NONE);

		virtual void Start();
		virtual void Update();
		virtual void Render();
		void RenderCollider();

		void RestartCollisionData(GameObject* other);
		void HandleCollisionEvent(GameObject* other);
		virtual void OnCollisionEnter(GameObject* other);
		virtual void OnCollisionStay(GameObject* other);
		virtual void OnCollisionExit(GameObject* other);

		void Enable(bool enabled);
		void Renderable(bool renderable);
		void SetColor(SDL_Color color);
		void SetColliderColor(SDL_Color color);
		void SetPosition(glm::vec2 position);
		void SetRotation(double rotation);

		bool CompareTag(ColliderTag tag);
		ColliderTag GetTag();
		glm::vec2 GetPosition();
		glm::vec2 GetSize();
		glm::vec2 GetOffset();
	};
}