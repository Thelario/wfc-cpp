#include "GameObject.h"

#include "Engine.h"
#include "LoggerManager.h"

namespace Satellite
{
	GameObject::GameObject(glm::vec2 position, glm::vec2 scale, double rotation, const std::string& texture_id, int width, int height,
		bool flip_x, int tile_id, bool center_aligned, int z_index, SDL_Color color, bool enabled, bool renderable, bool collidable,
		glm::vec2 size, glm::vec2 offset, ColliderTag tag)
		: position(position), scale(scale), rotation(rotation), texture_id(texture_id), width(width), height(height), flip_x(flip_x),
		tile_id(tile_id), center_aligned(center_aligned), z_index(z_index), color(color), enabled(enabled), renderable(renderable),
		collidable(collidable), size(size), offset(offset), collider_color({0, 255, 0, 255}), tag(tag)
	{ }

	void GameObject::Start() {
		SetColor(color);
	}

	void GameObject::Update() { }

	void GameObject::Render()
	{
		// Generate source rect with the given texture.

		Texture* texture = TexturesManager::Instance()->GetTexture(texture_id);
		SDL_Rect src;
		src = (tile_id == -1) ? (texture->GetSourceRect()) : (texture->GetTileSourceRect(tile_id));

		// Calculate real width and height based on scale.

		float real_width = width * scale.x;
		float real_height = height * scale.y;

		// Calculate correct position based on center alignment.

		int pos_x = (center_aligned) ? (static_cast<int>(position.x - (real_width / 2))) : (position.x);
		int pos_y = (center_aligned) ? (static_cast<int>(position.y - (real_height / 2))) : (position.y);

		// Creating the destination rectangle.

		SDL_Rect dest = {
			static_cast<int>(pos_x),
			static_cast<int>(pos_y),
			static_cast<int>(real_width),
			static_cast<int>(real_height)
		};

		// Rendering based on the flip and rotation provided.

		SDL_RendererFlip flip = flip_x ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
		SDL_RenderCopyEx(Engine::Instance()->GetRenderer(), texture->GetTexture(), &src, &dest, rotation, NULL, flip);

		// Render collider

		if (collidable && Engine::Instance()->Debugging()) {
			RenderCollider();
		}
	}

	void GameObject::RenderCollider()
	{
		float pos_x = position.x - (size.x / 2);
		float pos_y = position.y - (size.y / 2);

		SDL_Rect outline_rect = {
			static_cast<int>(pos_x + offset.x),
			static_cast<int>(pos_y + offset.y),
			static_cast<int>(size.x),
			static_cast<int>(size.y)
		};

		SDL_SetRenderDrawColor(Engine::Instance()->GetRenderer(), collider_color.r, collider_color.g, collider_color.b, collider_color.a);
		SDL_RenderDrawRect(Engine::Instance()->GetRenderer(), &outline_rect);
	}

	void GameObject::RestartCollisionData(GameObject* other)
	{
		auto it = collision_info.find(other);

		if (it == collision_info.end())
		{
			// We were not colliding with an object with are also not colliding now, so do nothing

			return;
		}

		// We stopped colliding with an object we were colliding with

		collision_info.erase(other);
		OnCollisionExit(other);
	}

	void GameObject::HandleCollisionEvent(GameObject* other)
	{
		auto it = collision_info.find(other);

		if (it == collision_info.end())
		{
			// We are not colliding with an object we were not colliding with

			collision_info.emplace(other, true);
			OnCollisionEnter(other);
		}
		else
		{
			// We are colliding again with an object we were colliding before

			OnCollisionStay(other);
		}
	}

	void GameObject::OnCollisionEnter(GameObject* other) { }

	void GameObject::OnCollisionStay(GameObject* other) { }

	void GameObject::OnCollisionExit(GameObject* other) { }

	void GameObject::SetColor(SDL_Color color)
	{
		if (renderable == false) {
			return;
		}

		Texture* texture = TexturesManager::Instance()->GetTexture(texture_id);
		if (SDL_SetTextureColorMod(texture->GetTexture(), color.r, color.g, color.b) != 0) {
			LoggerManager::Error("A problem occured when setting the color for " + texture_id, SDL_GetError());
		}
	}

	void GameObject::SetColliderColor(SDL_Color color) { collider_color = color; }
	void GameObject::Renderable(bool renderable) { this->renderable = renderable; }
	void GameObject::Enable(bool enabled) { this->enabled = enabled; }
	void GameObject::SetPosition(glm::vec2 position) { this->position = position; }
	void GameObject::SetRotation(double rotation) { this->rotation = rotation; }

	bool GameObject::CompareTag(ColliderTag tag) { return this->tag == tag; }
	ColliderTag GameObject::GetTag() { return tag; }
	glm::vec2 GameObject::GetPosition() { return position; }
	glm::vec2 GameObject::GetSize() { return size; }
	glm::vec2 GameObject::GetOffset() { return offset; }
}