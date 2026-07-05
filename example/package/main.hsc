<?xml version="1.0" encoding="UTF-8"?>
<Level>
    <Player object_id_="Player1" transform="transform:0.051852,-0.950000,0.000000;0.000000,0.000000,0.000000;1.000000,1.000000,1.000000" _physics_mode="3" _physics_auto_sleep="false" _physics_gravity_scale="2.0" _movement_apply_gravity="true" _movement_max_fall_vel="1000.0" _movement_jump_force="10.0" _movement_max_x_vel="5.0" life="100">
        <light_comp object_id_="" relative_transform="transform:10.000000,10.000000,10.000000;0.000000,0.000000,0.000000;1.000000,1.000000,1.000000" color_="vec3:1.000000,1.000000,1.000000" attenuation_="0.02" intensity_="5.0"/>
        <cam_comp object_id_="" relative_transform="transform:0.000000,-0.200000,15.000000;0.000000,270.000000,-0.600000;1.000000,1.000000,1.000000" fov_ortho_height="37.200001"/>
        <sprite_comp object_id_="" relative_transform="transform:0.000000,0.000000,0.000000;0.000000,0.000000,0.000000;4.000000,4.000000,4.000000" material="S:/Horizon/game_engine/3.0/example/package/mat.mat"/>
        <capsule_comp object_id_="" _physics_capsule_height="2.1" _physics_capsule_radius="0.6" _physics_density="1.0" _physics_friction="1.0" _physics_bounciness="0.0" _physics_enable_events="true"/>
    </Player>
    <Box object_id_="Box1" transform="transform:0.000000,-3.600000,0.000000;0.000000,0.000000,0.000000;1.000000,1.000000,1.000000" _physics_mode="1" _physics_auto_sleep="true" _physics_gravity_scale="1.0">
        <box_comp object_id_="" _physics_box_size="vec2:9.200000,1.000000" _physics_density="1.0" _physics_friction="1.0" _physics_bounciness="0.0" _physics_enable_events="true"/>
        <sprite_comp object_id_="" relative_transform="transform:0.000000,0.000000,0.000000;0.000000,0.000000,0.000000;1.000000,1.000000,1.000000" material="S:/Horizon/game_engine/3.0/example/package/mat.mat"/>
    </Box>
    <Box object_id_="Box2" transform="transform:2.600000,-3.600000,0.000000;0.000000,0.000000,0.000000;1.000000,1.000000,1.000000" _physics_mode="1" _physics_auto_sleep="true" _physics_gravity_scale="1.0">
        <box_comp object_id_="" _physics_box_size="vec2:1.000000,1.000000" _physics_density="1.0" _physics_friction="1.0" _physics_bounciness="0.0" _physics_enable_events="true"/>
        <sprite_comp object_id_="" relative_transform="transform:0.000000,0.000000,0.000000;0.000000,0.000000,0.000000;1.000000,1.000000,1.000000" material="S:/Horizon/game_engine/3.0/example/package/mat.mat"/>
    </Box>
    <Box object_id_="Box3" transform="transform:-2.400000,-2.800000,0.000000;0.000000,0.000000,0.000000;1.000000,1.000000,1.000000" _physics_mode="1" _physics_auto_sleep="true" _physics_gravity_scale="1.0">
        <box_comp object_id_="" _physics_box_size="vec2:1.000000,1.800000" _physics_density="1.0" _physics_friction="1.0" _physics_bounciness="0.0" _physics_enable_events="true"/>
        <sprite_comp object_id_="" relative_transform="transform:0.000000,0.000000,0.000000;0.000000,0.000000,0.000000;1.000000,1.000000,1.000000" material="S:/Horizon/game_engine/3.0/example/package/mat.mat"/>
    </Box>
</Level>
