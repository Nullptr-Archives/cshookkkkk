#pragma once
#include "../../Utils/globals.hpp"
#include <unordered_map>
#include <vector>

namespace features
{
    class aimbot
    {
        private:
            struct aim_target
            {
                int target_id;
                int target_hitbox_id;

                bool operator==(const aim_target& other) const
                {
                    return (this->target_id == other.target_id) && (this->target_hitbox_id == other.target_hitbox_id);
                }

                bool operator!=(const aim_target& other) const
                {
                    return !(*this == other);
                }
            };

            struct fov_result 
            {
                float fov;
                float real_distance;
            };

        private:
            aimbot()
            {
                this->enabled = false;
                this->team = false;
                this->silent = false;
                this->fov_enabled = false;
                this->fov_max = 360.0f;
                this->smooth_enabled = false;
                this->smooth_speed = 7.0f;

                this->delay = 0;
                this->next_fire = -1;

                this->on_key = false;
                this->key = -1;
            }
        
        public:
            static aimbot& instance()
            {
                static aimbot aa;
                return aa;
            }

            void create_move(float frametime, usercmd_t *cmd, int active);
            void show_menu();

        private:
            aim_target find_best_target(const math::vec3& origin, const math::vec3& angles);
            fov_result get_fov_to_target(const math::vec3& angles, const math::vec3& target_angles, float distance);

        private:
            bool enabled;
            bool team;
            bool silent;

            bool fov_enabled;
            float fov_max;
            bool smooth_enabled;
            float smooth_speed;

            int64_t delay;
            int64_t next_fire;

            bool on_key;
            int key;

            bool all_hitboxes;
            std::unordered_map<int, bool> target_hitboxes;
    };
}