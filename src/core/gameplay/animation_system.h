#ifndef HGE_ANIMATION_SYSTEM_H
#define HGE_ANIMATION_SYSTEM_H

#include <unordered_map>
#include <string>
#include <vector>

#ifdef HGE_CLASSIC_ANIMATION_SYSTEM

//classic animation system (rule based animations)

namespace hge
{
	struct HAnimationSystem;

	struct HAnimation {

	};

	struct HBlendSpace1D {
	private:
		std::vector<HAnimation> anims_;

	public:

	};

	struct HAnimRule {
	private:
		std::string anim_a;
		std::string anim_b;
		float transition_time=0.f;

	public:
		HAnimRule(const char* a, const char* b);
		virtual ~HAnimRule()=default;

		void SetAnimA(const char* a);
		void SetAnimB(const char* b);
		void SetTransitionTime(float time);

		virtual void CanEnterTransition(const HAnimationSystem* system) const=0;
	};

	struct HAnimationSystem {
		HAnimationSystem();
		~HAnimationSystem();

		//anim type : classic animation, blend space, etc
		template<typename T>
		T* AddAnimation(const char* name)
		{

		}

		template<typename R>
		R* AddRule()
		{
			R* rule = new R();
			rules_.emplace_back(rule);
			return rule;
		}

		void PlayAnimation();

	private:
		float velocity_;
		std::unordered_map<std::string, HAnimation*> animations_;
		std::vector<HAnimRule*> rules_;

		std::string current_animation_;
	};
}

#endif

//modern animation system (property driven animations)
namespace hge
{
	struct HAnimCustomRule {
		const char* id;
		int& ref;
		int target_min;
		int target_max;
	};

	struct HAnimation {
		//x velocity
		float min_velocity_x;
		float max_velocity_x;  //0 means no maximum

		//y velocity
		float min_velocity_y;
		float max_velocity_y;  //0 means no maximum

		//relative distance to the ground
		float min_altitude;
		float max_altitude;  //0 means no maximum

		//direction
		//-1 means left, 1 means right, and 0 means neutral
		int facing;


	private:
		//custom rules partagées pour tout le système, pas une seule animation
	};

	struct HAnimationSystem {
		void AddAnimation(const char* name, const HAnimation& anim);

		void PlayAnimationMontage(const char* anim);

		//plus tard passer par un template ou un variant
		void AddCustomIntRule(const char* id, int& ref, int target_min, int target_max);

	private:
		std::unordered_map<std::string, HAnimation> anims_;

		std::vector<HAnimCustomRule> custom_rules_;
	};
}

#endif