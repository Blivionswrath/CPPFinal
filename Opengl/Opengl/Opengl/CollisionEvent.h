#ifndef COLLISION_EVENT_H
#define COLLISION_EVENT_H

#include <glm/glm.hpp>




//Signifies what kind of object it is
enum class Collider { player, enemy, bullet, friendlyBullet, object, none };
//Signifies what part of the object has been hit
enum class ColliderFlag { top, bottom, left, right, none };

struct CollisionInfo {
	glm::vec3 position1;
	glm::vec3 scale1;
	glm::vec3 position2;
	glm::vec3 scale2;
	float speedX1;
	float speedY1;
	float speedX2;
	float speedY2;
	Collider colliderType1;
	Collider colliderType2;
};
class CollisionEvent {
public:
	Collider colliderType;
	//Default constructor of none. This should only be used by the background.
	CollisionEvent() {
		colliderType = Collider::none;
	}

	CollisionEvent(Collider colliderType) {
		this->colliderType = colliderType;
	}

	static ColliderFlag opposite(ColliderFlag flag) {
		if (flag == ColliderFlag::bottom) {
			return ColliderFlag::top;
		}
		if (flag == ColliderFlag::right || flag == ColliderFlag::left) {

			if (ColliderFlag::right == flag) { return ColliderFlag::left; }
			else { return ColliderFlag::right; }
			return ColliderFlag::top;
		}

	}


	static CollisionInfo clamp(CollisionInfo info, ColliderFlag side) {
		CollisionInfo ret = info;
		if (info.colliderType1 != Collider::object) {

			if (side == ColliderFlag::right) {
				float object1Right = 0.5f * info.scale1.x + info.position1.x;
				float object2Left = -0.5f * info.scale2.x + info.position2.x;
				float difference = object1Right - object2Left;
				ret.position1.x = info.position1.x - difference - 0.2f;
				ret.speedX1 = 0;
	
			}
			else if (side == ColliderFlag::left){
				float object1Left = -0.5 * info.scale1.x + info.position1.x;
				float object2Right = 0.5 * info.scale2.x + info.position2.x;
				float difference = object2Right - object1Left;
				ret.speedX1 = 0;
				ret.position1.x = info.position1.x + difference + 0.2f;
			}
			else if (side == ColliderFlag::bottom) {
				float object1Bottom = -0.5f * info.scale1.y + info.position1.y;
				float object2Top = 0.5f * info.scale2.y + info.position2.y;
				float difference = abs(object2Top - object1Bottom);
				ret.speedY1 = 0;
				ret.position1.y = info.position1.y + difference + 0.2f;
			}
			else if (side == ColliderFlag::top) {
				float object1Top = 0.5f * info.scale1.y + info.position1.y;
				float object2Bottom = -0.5f * info.scale2.y + info.position2.y;
				float difference = abs(object2Bottom - object1Top);
				ret.speedY1 = 0;
				ret.position1.y = info.position1.y - difference - 0.2f;
			}

		}
		else {
			CollisionInfo* info2 = new CollisionInfo;
			info2->position1 = info.position2;
			info2->position2 = info.position1;
			info2->scale1 = info.scale2;
			info2->scale2 = info.scale1;
			info2->speedX1 = info.speedX2;
			info2->speedX2 = info.speedX1;
			info2->speedY1 = info.speedY2;
			info2->speedY2 = info.speedY1;
			info2->colliderType1 = info.colliderType2;
			info2->colliderType2 = info.colliderType1;
			ret = clamp(*info2, side);

			info2->position1 = ret.position2;
			info2->position2 = ret.position1;
			info2->scale2 = ret.scale1;
			info2->speedX1 = ret.speedX2;
			info2->speedX2 = ret.speedX1;
			info2->speedY1 = ret.speedY2;
			info2->speedY2 = ret.speedY2;
			ret = *info2;
			delete info2;
		}
		return ret;
	}
};

#endif