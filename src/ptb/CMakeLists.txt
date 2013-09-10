cmake_minimum_required(VERSION 2.6)
project(plee-the-bear-library)

set( LIBPTB_TARGET_NAME plee_the_bear )

include_directories( ..
  ${BEAR_ENGINE_INCLUDE_DIRECTORY}
  ${BEAR_GENERIC_ITEMS_INCLUDE_DIRECTORY}
  )

#-------------------------------------------------------------------------------
set( LIBPTB_SOURCE_FILES
  code/config_file.cpp
  code/controller_config.cpp
  code/controller_layout.cpp
  code/end.cpp
  code/game_variables.cpp
  code/gauge.cpp
  code/gui_command.cpp
  code/init.cpp
  code/level_information.cpp
  code/mini_game_information.cpp
  code/level_variables.cpp
  code/playability_type.cpp
  code/player.cpp
  code/player_action.cpp
  code/player_proxy.cpp
  code/player_pending_action.cpp
  code/score_table.cpp
 
  frame/code/frame.cpp
  frame/code/frame_audio.cpp
  frame/code/frame_choose_player_mode.cpp
  frame/code/frame_configure.cpp
  frame/code/frame_game_options.cpp
  frame/code/frame_level_score.cpp
  frame/code/frame_main_menu.cpp
  frame/code/frame_pause.cpp
  frame/code/frame_password.cpp
  frame/code/frame_play_mini_game.cpp
  frame/code/frame_play_story.cpp
  frame/code/frame_player_controls.cpp
  frame/code/frame_profiles.cpp
  frame/code/frame_profile_name.cpp
  frame/code/frame_screen.cpp
  frame/code/frame_start_menu.cpp
  frame/code/frame_talk.cpp
  frame/code/menu_frame.cpp
  frame/code/message_box.cpp

  gui/code/horizontal_gauge.cpp
  gui/code/key_edit.cpp
  gui/code/notification_widget.cpp
  gui/code/vertical_gauge.cpp

  item/bonus_points/code/bonus_all_dead.cpp
  item/bonus_points/code/bonus_all_dead_by_category.cpp
  item/bonus_points/code/bonus_boss.cpp
  item/bonus_points/code/bonus_carnage.cpp
  item/bonus_points/code/bonus_cooperation.cpp
  item/bonus_points/code/bonus_exits.cpp
  item/bonus_points/code/bonus_max_energy.cpp
  item/bonus_points/code/bonus_mini_game.cpp
  item/bonus_points/code/bonus_points.cpp
  item/bonus_points/code/bonus_time.cpp
  item/bonus_points/code/bonus_time_record.cpp
  
  item/expr/code/bool_level_variable_getter_creator.cpp
  
  item/castle/code/armor.cpp
  item/castle/code/axe.cpp
  item/castle/code/catapult.cpp
  item/castle/code/friend_ghost.cpp
  item/castle/code/friend_block.cpp
  item/castle/code/ghost.cpp
  item/castle/code/reverse_ghost.cpp
  item/castle/code/rolling_ball.cpp
  item/castle/code/spider.cpp
  item/castle/code/spider_venom.cpp
  item/castle/code/thief_ghost.cpp

  item/code/action_file_recorder.cpp
  item/code/add_ingame_layers.cpp
  item/code/add_players_camera.cpp
  item/code/add_main_menu_layer.cpp
  item/code/air_bubble.cpp
  item/code/air_bubble_generator.cpp
  item/code/authorize_action_toggle.cpp
  item/code/bonus_box.cpp
  item/code/bonus_manager.cpp
  item/code/checkpoint.cpp
  item/code/clingable.cpp
  item/code/corrupting_bonus.cpp
  item/code/corrupting_bonus_attractor.cpp
  item/code/corrupting_item.cpp
  item/code/demo_level_loader.cpp
  item/code/floating_score.cpp
  item/code/free_bonus.cpp
  item/code/game_settings.cpp
  item/code/god.cpp
  item/code/gossipy_item.cpp
  item/code/hazelnut.cpp
  item/code/headstone.cpp
  item/code/hideout_bonus_item.cpp
  item/code/hideout_revealing.cpp
  item/code/honeypot.cpp
#  item/code/invincibility_effect.cpp
  item/code/kicker.cpp
  item/code/layer_border.cpp
  item/code/level_exit.cpp
  item/code/level_pusher.cpp
  item/code/level_popper.cpp
  item/code/level_score_record.cpp
  item/code/level_settings.cpp
  item/code/little_plee.cpp
  item/code/link_on_players.cpp
  item/code/mini_game_unlock_item.cpp
  item/code/notification_toggle.cpp
  item/code/on_players_activator.cpp
  item/code/one_or_two_players_toggle.cpp
  item/code/owl.cpp
  item/code/passive_enemy.cpp
  item/code/player_action_sender.cpp
  item/code/player_killer.cpp
  item/code/player_killer_toggle.cpp
  item/code/players_detector.cpp
  item/code/players_present.cpp
  item/code/player_settings.cpp
  item/code/player_speaker_zone.cpp
  item/code/player_start_position.cpp
  item/code/player_stop_block.cpp
  item/code/power_drop_restriction_zone.cpp
  item/code/power_effect.cpp
  item/code/power_filter_door.cpp
  item/code/projectile_enemy.cpp
  item/code/projectile_enemy_zone.cpp
  item/code/save_player_position.cpp
  item/code/script_actor_player.cpp
  item/code/script_director.cpp
  item/code/shared_camera.cpp
  item/code/small_honeypot.cpp
  item/code/soul.cpp
  item/code/stone_tracer.cpp
  item/code/timer_kill_players.cpp
  item/code/two_players_only.cpp

  item/mini-game/code/sequencer.cpp
  item/mini-game/code/sequencer_control.cpp
  item/mini-game/code/stone_target.cpp

  item/player/code/plee.cpp
  item/player/code/ray.cpp
  
  item/stone/code/air_fire_stone.cpp
  item/stone/code/air_fire_water_stone.cpp
  item/stone/code/air_water_stone.cpp
  item/stone/code/air_stone.cpp
  item/stone/code/fire_stone.cpp
  item/stone/code/stone.cpp
  item/stone/code/water_fire_stone.cpp
  item/stone/code/water_stone.cpp

  item/forest/code/big_rabbit.cpp
  item/forest/code/carrot_monster.cpp
  item/forest/code/frog.cpp
  item/forest/code/gorilla.cpp
  item/forest/code/sting.cpp
  item/forest/code/rabbit.cpp
  item/forest/code/wasp.cpp
  item/forest/code/woodpecker.cpp

  item_brick/code/activate_on_players.cpp
  item_brick/code/boss.cpp
  item_brick/code/base_bonus.cpp
  item_brick/code/monster.cpp
  item_brick/code/sniffable.cpp
  item_brick/code/with_attack_point.cpp
 
  layer/code/ingame_menu_layer.cpp
  layer/code/main_menu_layer.cpp
  layer/code/misc_layer.cpp 
  layer/code/player_arrows_layer.cpp  
  layer/code/status_layer.cpp
  layer/code/windows_layer.cpp

  layer/status/code/accelerated_time_component.cpp
  layer/status/code/boss_component.cpp
  layer/status/code/cold_gauge_component.cpp
  layer/status/code/corrupting_bonus_component.cpp
  layer/status/code/energy_component.cpp
  layer/status/code/floating_bonus.cpp
  layer/status/code/floating_corrupting_bonus.cpp
  layer/status/code/gauge_component.cpp
  layer/status/code/hazelnut_component.cpp
  layer/status/code/heat_gauge_component.cpp
  layer/status/code/honeypots_component.cpp
  layer/status/code/lives_component.cpp
  layer/status/code/oxygen_gauge_component.cpp
  layer/status/code/score_component.cpp
  layer/status/code/status_component.cpp
  layer/status/code/throwable_item_component.cpp
  layer/status/code/time_component.cpp

  message/code/get_player_instance.cpp
  message/code/score_message.cpp
  message/code/status_layer_boss_message.cpp
  message/code/status_layer_notification_message.cpp

  network/message/code/player_action_message.cpp

  player_state/code/state_captive.cpp  
  player_state/code/state_cling.cpp
  player_state/code/state_clung_jump.cpp
  player_state/code/state_crouch.cpp
  player_state/code/state_dead.cpp
  player_state/code/state_fall.cpp
  player_state/code/state_float.cpp
  player_state/code/state_hang.cpp
  player_state/code/state_game_over.cpp
  player_state/code/state_idle.cpp
  player_state/code/state_injured.cpp
  player_state/code/state_jump.cpp
  player_state/code/state_look_upward.cpp
  player_state/code/state_maintain.cpp
  player_state/code/state_paralyze.cpp
  player_state/code/state_player.cpp
  player_state/code/state_roar.cpp 
  player_state/code/state_run.cpp
  player_state/code/state_slap.cpp
  player_state/code/state_start_cling.cpp
  player_state/code/state_start_hang.cpp
  player_state/code/state_start_jump.cpp
  player_state/code/state_throw.cpp
  player_state/code/state_sink.cpp
  player_state/code/state_swimming.cpp
  player_state/code/state_vertical_jump.cpp
  player_state/code/state_wait.cpp
  player_state/code/state_walk.cpp

  reference_point/code/attack_point_reference_point.cpp

  throwable_item/code/air_honeypot_throwable_item.cpp
  throwable_item/code/corrupting_item_throwable_item.cpp
  throwable_item/code/fire_honeypot_throwable_item.cpp
  throwable_item/code/hazelnut_throwable_item.cpp
  throwable_item/code/throwable_item.cpp
  throwable_item/code/throwable_items_container.cpp
  throwable_item/code/stone_throwable_item.cpp
  throwable_item/code/water_honeypot_throwable_item.cpp

  transition_effect/code/contest_result_effect.cpp
  transition_effect/code/game_over_effect.cpp
  transition_effect/code/invincibility_effect.cpp
  transition_effect/code/level_ending_effect.cpp
  transition_effect/code/level_starting_effect.cpp

  util/code/level_util.cpp
  util/code/player_util.cpp
)

add_library( ${LIBPTB_TARGET_NAME} SHARED ${LIBPTB_SOURCE_FILES} )

set_target_properties(
  ${LIBPTB_TARGET_NAME}
  PROPERTIES
  INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${PTB_INSTALL_CUSTOM_LIBRARY_DIR}"
  )

if( NOT WIN32 )
  set_target_properties(
    ${LIBPTB_TARGET_NAME}
    PROPERTIES
    COMPILE_DEFINITIONS "PTB_TEXT_DOMAIN_PATH=${CMAKE_INSTALL_PREFIX}/${TRANSLATIONS_INSTALL_DIR}"
    )
endif( NOT WIN32 )

if( PTB_CAN_RESTART_LEVEL )
  set_target_properties(
    ${LIBPTB_TARGET_NAME}
    PROPERTIES
    COMPILE_DEFINITIONS "PTB_CAN_RESTART_LEVEL=1"
    )
endif( PTB_CAN_RESTART_LEVEL )

install(
  TARGETS ${LIBPTB_TARGET_NAME}
  DESTINATION ${PTB_INSTALL_CUSTOM_LIBRARY_DIR}
  )

set(
  LIBPTB_LINK_LIBRARIES
  bear_engine
  bear_generic_items
  bear_gui
  ${CLAW_CONFIGURATION_FILE_LIBRARIES}
  ${Boost_SIGNALS_LIBRARY}
  )

if(WIN32 OR APPLE)
  set(
    LIBPTB_LINK_LIBRARIES
    ${LIBPTB_LINK_LIBRARIES}
    intl )
endif(WIN32 OR APPLE)

target_link_libraries(
  ${LIBPTB_TARGET_NAME}
  ${LIBPTB_LINK_LIBRARIES}
  )
