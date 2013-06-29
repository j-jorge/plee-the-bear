/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::frame_play_story class.
 * \author Sébastien Angibaud
 */
#include "ptb/frame/frame_play_story.hpp"

#include "ptb/defines.hpp"
#include "ptb/level_information.hpp"
#include "ptb/frame/frame_start_menu.hpp"
#include "ptb/frame/theme_colors.hpp"
#include "ptb/layer/windows_layer.hpp"
#include "ptb/game_variables.hpp"

#include "engine/resource_pool.hpp"
#include "engine/game.hpp"
#include "engine/game_local_client.hpp"
#include "engine/level.hpp"
#include "engine/level_globals.hpp"
#include "engine/variable/variable_list_reader.hpp"
#include "engine/variable/var_map.hpp"

#include "gui/button.hpp"
#include "gui/callback_function.hpp"

#include "visual/scene_writing.hpp"
#include "visual/scene_element.hpp"
#include "visual/scene_sprite.hpp"

#include <libintl.h>
#include <boost/bind.hpp>
#include <claw/logger.hpp>
#include <claw/configuration_file.hpp>
#include <claw/graph.hpp>
#include <claw/graph_algorithm.hpp>

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param owning_layer The layer onwing the window.
 */
ptb::frame_play_story::frame_play_story
( windows_layer* owning_layer )
  : frame(owning_layer, gettext("Level selection")), m_index(0)
{
  load_and_sort_level_names();
  create_controls();

  for ( unsigned int i=0; i != m_levels.size(); ++i)
    CLAW_PRECOND( m_levels[i].is_valid() );

  m_index = m_levels.size() - 1;

  update_controls();
} // frame_play_story::frame_play_story()

/*----------------------------------------------------------------------------*/
/**
 * \brief Method called when the frame is displayed.
 */
void ptb::frame_play_story::on_focus()
{
  frame::on_focus();

  update_controls();
} // frame_play_story::on_focus()

/*----------------------------------------------------------------------------*/
/**
 * \brief Delete mini-game.
 */
void ptb::frame_play_story::delete_levels()
{
  m_levels.resize(0);
} // frame_play_story::delete_levels()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the static text components.
 */
void ptb::frame_play_story::create_controls()
{
  m_thumb = new bear::gui::picture( get_default_thumb() );
  m_name_text = new bear::gui::scene_element();
  m_status_picture = new bear::gui::picture( get_status_picture() );

  get_content().insert( m_thumb );
  get_content().insert( m_name_text );
  get_content().insert( m_status_picture );

  m_second_player_status.energy = new horizontal_gauge
    ( get_layer().get_level().get_globals(), 100, "bar (light blue)",
      "bar (red)", "heart", true );

  m_first_player_status.energy = new horizontal_gauge
    ( get_layer().get_level().get_globals(), 100, "bar (green)",
      "bar (red)", "heart", true );

  create_player_component(m_first_player_status);
  create_player_component(m_second_player_status);
  create_bonus_component();

  bear::gui::visual_component* ok = create_ok_button();
  bear::gui::visual_component* back = create_back_button();
  bear::gui::visual_component* previous = create_previous_button();
  bear::gui::visual_component* next = create_next_button();

  position_controls( ok->top() + get_margin() );

  bear::gui::size_type sum_w
    ( 3 * get_margin() + ok->width() + back->width() + previous->width()
      + next->width() );

  const bear::gui::size_type w
    ( (m_bonus->width() + m_thumb->width() + 2*get_margin() - sum_w) / 3);

  back->set_left( ok->right() + w );
  previous->set_left( back->right() + w );
  next->set_right( m_status_picture->right() );

  ok->set_focus();

  fit( get_margin() );
} // frame_play_story::create_controls()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load level names and sort them in the story order.
 )*/
void ptb::frame_play_story::load_and_sort_level_names()
{
  std::list<std::string> level_names;

  bear::engine::var_map vars;
  bear::engine::game::get_instance().get_game_variables
    ( vars, ".*continues_with" );

  sort_level_names(level_names, vars);

  std::list<std::string>::iterator it;
  for (it = level_names.begin(); it != level_names.end(); ++it  )
    {
      std::string name = game_variables::get_level_name(*it);

      if ( !name.empty() )
        m_levels.push_back(level_information(*it, name));
    }
} // frame_play_story::load_level_names()

/*----------------------------------------------------------------------------*/
/**
 * \brief Sort level's names.
 * \param level_names The list of sorted level's name.
 * \param vars The list of game variables that define level order;
 */
void ptb::frame_play_story::sort_level_names
(std::list<std::string>& level_names, bear::engine::var_map vars)
{
  typedef claw::graph<std::string> graph_type;

  graph_type g;

  bear::engine::var_map::iterator<std::string>::type it;
  for ( it=vars.begin<std::string>();
        it!=vars.end<std::string>(); ++it )
    {
      std::string prefix(PTB_PERSISTENT_PREFIX);
      std::string var(it->first);
      std::string c1;
      std::string c2;
      c1 = var.erase(0, prefix.size());

      size_t pos = c1.find("/continues_with");
      if (pos != std::string::npos)
        c2 = c1.erase(pos, c1.size()-pos);

      g.add_vertex(c2);
      g.add_vertex(it->second);
      g.add_edge(c2, it->second);
    }

  claw::topological_sort<graph_type> sort;
  sort(g);

  level_names = std::list<std::string>(sort.begin(), sort.end());
} // frame_play_story::sort_level_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the "Play!" button.
 */
bear::gui::visual_component* ptb::frame_play_story::create_ok_button()
{
  bear::gui::button* result =
    new bear::gui::button
    ( get_font(), gettext("Play!"),
      bear::gui::callback_function_maker
      ( boost::bind( &frame_play_story::on_ok, this ) ) );

  result->set_margin( get_margin() / 2 );
  set_borders_up( *result );
  insert_control( *result );

  return result;
} // frame_play_story::create_ok_button()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the "Back" button.
 */
bear::gui::visual_component* ptb::frame_play_story::create_back_button()
{
  bear::gui::button* result =
    new bear::gui::button
    ( get_font(), gettext("Back"),
      bear::gui::callback_function_maker
      ( boost::bind( &frame_play_story::close_window, this ) ) );

  result->set_margin( get_margin() / 2 );
  set_borders_up( *result );
  insert_control( *result );

  return result;
} // frame_play_story::create_back_button()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the "Previous" button.
 */
bear::gui::visual_component* ptb::frame_play_story::create_previous_button()
{
  bear::gui::button* result =
    new bear::gui::button
    ( get_font(), gettext("Previous"),
      bear::gui::callback_function_maker
      ( boost::bind( &frame_play_story::on_previous, this ) ) );

  result->set_margin( get_margin() / 2 );
  set_borders_up( *result );
  insert_control( *result );

  return result;
} // frame_play_story::create_previous_button()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the "Next" button.
 */
bear::gui::visual_component* ptb::frame_play_story::create_next_button()
{
  bear::gui::button* result =
    new bear::gui::button
    ( get_font(), gettext("Next"),
      bear::gui::callback_function_maker
      ( boost::bind( &frame_play_story::on_next, this ) ) );

  result->set_margin( get_margin() / 2 );
  set_borders_up( *result );
  insert_control( *result );

  return result;
} // frame_play_story::create_next_button()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create all bonus components.
 */
void ptb::frame_play_story::create_bonus_component()
{
  m_bonus =
    new bear::gui::horizontal_flow(3, 3, bear::visual::color_type("e50f0f"));
  get_content().insert( m_bonus );

  m_bonus->set_background_color(PTB_THEME_FACE);
  set_borders_down(*m_bonus);
  insert_control( *m_bonus );

  m_bonus_text = new bear::gui::static_text(get_font());
  insert( m_bonus_text );
  m_bonus_text->set_background_color(PTB_THEME_FACE);
  set_borders_down(*m_bonus_text);
} // frame_play_story::create_bonus_component()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create component for display player's informations.
 * \param p The object containing all player's information controls.
 */
void ptb::frame_play_story::create_player_component(player_status& p)
{
  bear::engine::level_globals& glob = get_layer().get_level().get_globals();

  p.component = new bear::gui::visual_component();
  get_content().insert( p.component );
  p.component->set_background_color(PTB_THEME_FACE);
  set_borders_down(*p.component);

  p.component->insert( p.energy );

  p.score_text = new bear::gui::static_text(get_font());
  p.score_text->set_auto_size(false);
  p.component->insert( p.score_text );

  p.lives_text = new bear::gui::static_text(get_font());
  p.lives_text->set_auto_size(false);
  p.component->insert( p.lives_text );

  p.stone_text = new bear::gui::static_text(get_font());
  p.stone_text->set_auto_size(false);
  p.component->insert( p.stone_text );

  bear::visual::sprite spr
    (glob.auto_sprite("gfx/ui/status/status.png", "plee"));
  p.lives_picture = new bear::gui::picture(spr);
  p.component->insert( p.lives_picture );

  spr = glob.get_image("gfx/ui/air-power.png");
  p.air_power = new bear::gui::picture(spr);
  p.component->insert(p.air_power);

  spr = glob.get_image("gfx/ui/fire-power.png");
  p.fire_power = new bear::gui::picture(spr);
  p.component->insert(p.fire_power);

  spr = glob.get_image("gfx/ui/water-power.png");
  p.water_power = new bear::gui::picture(spr);
  p.component->insert(p.water_power);

  spr = glob.auto_sprite("gfx/stone/stone.png", "default stone");
  p.stone_picture = new bear::gui::picture(spr);
  p.component->insert(p.stone_picture);
} // frame_play_story::create_player_component()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set position of controls.
 * \param b The bottom position of the controls.
 */
void
ptb::frame_play_story::position_controls( bear::gui::coordinate_type b )
{
  bear::universe::coordinate_type width =
    (get_layer().get_size().x - 100 - get_margin() - m_thumb->width()) / 2;

  m_first_player_status.component->set_size( width, m_thumb->height() );
  player_status_position_controls(m_first_player_status);

  m_second_player_status.component->set_size( width, m_thumb->height() );
  player_status_position_controls(m_second_player_status);

  m_bonus_text->set_size
    ( get_layer().get_size().x -100 + get_margin(), 25 );
  m_bonus_text->set_bottom( b + get_margin());
  m_bonus_text->set_left( get_margin() );

  m_bonus->set_size
    ( 2*width + get_margin(), m_thumb->height() );
  m_bonus->set_bottom( m_bonus_text->top() );

  m_status_picture->set_bottom_left
    ( m_bonus->right() + get_margin(), m_bonus->bottom() );
  m_thumb->set_bottom( m_bonus->top() + get_margin() );

  m_first_player_status.component->set_bottom_left
    ( m_thumb->right() + get_margin(), m_thumb->bottom() );
  if ( m_second_player_status.component )
     m_second_player_status.component->set_bottom_left
       ( m_first_player_status.component->right() + get_margin(),
         m_thumb->bottom() );

  // The height of the font used for the name of the mini-game
  m_name_text->set_height(50);
  m_name_text->set_bottom( m_thumb->top() + get_margin() );
} // frame_play_story::position_controls()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set position of controls for player's informations.
 * \param p The object containing all player's information controls.
 */
void ptb::frame_play_story::player_status_position_controls
( player_status& p )
{
  bear::engine::level_globals& glob =
    get_layer().get_level().get_globals();

  p.energy->set_size
    (p.component->get_size().x - 2 * get_margin(),
     (p.component->get_size().y - 4*get_margin()) / 3);
  p.energy->set_bottom_left( get_margin(), get_margin());

  bear::visual::sprite s0(glob.auto_sprite("gfx/ui/status/status.png", "plee"));
  p.lives_picture->set_size(s0.get_size());
  p.lives_picture->set_bottom_left
    ( get_margin(), p.energy->top() + get_margin());

  p.lives_text->set_size
    (p.component->get_size().x / 2 - p.lives_picture->width() - get_margin(),
     (p.component->get_size().y - 4*get_margin()) / 3);
  p.lives_text->set_top_left
    (p.lives_picture->right() + get_margin(), p.lives_picture->top());

  p.score_text->set_size
    (p.component->get_size().x / 2,
     (p.component->get_size().y - 4*get_margin()) / 3);
  p.score_text->set_bottom_left
    ( get_margin(), p.lives_picture->top()+get_margin());

  bear::visual::sprite s1(glob.get_image("gfx/ui/air-power.png"));
  p.air_power->set_size(s1.get_size());

  p.air_power->set_top_left
    (p.score_text->right() + get_margin(), p.score_text->top());

  p.fire_power->set_size(s1.get_size());
  p.fire_power->set_top_left
    (p.air_power->right() + get_margin(), p.score_text->top());

  p.water_power->set_size(s1.get_size());
  p.water_power->set_top_left
    (p.fire_power->right() + get_margin(), p.score_text->top());

  bear::visual::sprite s2
    (glob.auto_sprite("gfx/stone/stone.png", "default stone"));
  p.stone_picture->set_size(s2.get_size());
  p.stone_picture->set_bottom_left
    (p.lives_text->right() + get_margin(), p.lives_text->bottom());

  p.stone_text->set_size
    (p.component->get_size().x / 2,
     (p.component->get_size().y - 4*get_margin()) / 3);
  p.stone_text->set_top_left
    ( p.stone_picture->right() + get_margin(), p.stone_picture->top());
} // frame_play_story::player_status_position_controls

/*----------------------------------------------------------------------------*/
/**
 * \brief Update controls.
 */
void ptb::frame_play_story::update_controls()
{
  if ( !m_levels.empty() )
    {
      update_level_name();
      update_all_players_status();
      update_bonus();
      m_thumb->set_picture(get_thumb());
      m_status_picture->set_picture(get_status_picture());
    }
} // frame_play_story::update_controls()

/*----------------------------------------------------------------------------*/
/**
 * \brief Update objects.
 */
void ptb::frame_play_story::update_bonus()
{
  bear::engine::level_globals& glob =
    get_layer().get_level().get_globals();
  const bear::visual::sprite background =
    glob.auto_sprite( "gfx/ui/bonus-icons/bonus-icons.png", "background" );

  m_bonus->clear();
  m_bonus_text->set_text("");
  level_information::bonus_list::const_iterator it;
  bool first(true);

  for ( it = m_levels[m_index].get_bonus().begin();
        it != m_levels[m_index].get_bonus().end(); ++it )
    {
      std::string filename
        ( game_variables::get_level_object_filename
          ( m_levels[m_index].get_filename(), *it ) );
      std::string name
        ( game_variables::get_level_object_name
          ( m_levels[m_index].get_filename(), *it) );

      if ( !filename.empty() && !name.empty() )
        {
          if ( first )
            {
              first = false;
              m_bonus_text->set_text(gettext(it->c_str()));
            }
          bear::visual::sprite s( glob.auto_sprite( filename, name ));
          bear::gui::visual_component* result =new bear::gui::visual_component;
          result->set_size( background.get_size() );
          result->insert( new bear::gui::picture(background) );

          if ( !game_variables::get_level_object_state
               (m_levels[m_index].get_filename(), *it) )
            s.set_intensity(0, 0, 0);

          result->insert( new bear::gui::picture(s) );
          result->add_focus_callback
            ( bear::gui::callback_function_maker
              ( boost::bind
                ( &frame_play_story::on_bonus_selected,
                  this, (*it) ) ) );
          m_bonus->insert( result );
        }
    }
} // frame_play_story::update_object()

/*----------------------------------------------------------------------------*/
/**
 * \brief Update level name.
 */
void ptb::frame_play_story::update_level_name()
{
  // Adjust the height of m_name_text in position_controls() to the height
  // of this font
  const bear::visual::writing w
    ( get_layer().get_level().get_globals().get_font
      ("font/level_name-42x50.fnt", 50),
      gettext(m_levels[m_index].get_id().c_str()) );

  m_name_text->set_size
    ( std::min(w.get_width(), get_content().width()), 50 );
  m_name_text->set_scene_element( bear::visual::scene_writing(0, 0, w) );
  m_name_text->set_position
    ( (get_content().width() - m_name_text->width()) / 2,
      m_thumb->top() + get_margin());
} // frame_play_story::update_level_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Update status of all players.
 */
void ptb::frame_play_story::update_all_players_status()
{
  update_player_status(1, m_first_player_status);

  if ( game_variables::get_players_count() == 2 )
    update_player_status(2, m_second_player_status);
  else
    {
      m_second_player_status.score_text->set_text( gettext("No player") );
      m_second_player_status.lives_text->set_text( "0" );
      m_second_player_status.stone_text->set_text( "0" );
      m_second_player_status.energy->set_length(100);
      m_second_player_status.energy->set_level(0);
      m_second_player_status.energy->set_max_level(100);

      update_power
        (false, "gfx/ui/air-power.png", m_second_player_status.air_power);
      update_power
        (false, "gfx/ui/fire-power.png", m_second_player_status.fire_power);
      update_power
        (false, "gfx/ui/water-power.png", m_second_player_status.water_power);
    }
} // frame_play_story::update_all_players_status()

/*----------------------------------------------------------------------------*/
/**
 * \brief Update status of a player.
 * \param index The  index of the player.
 * \param p Status of the player.
 */
void ptb::frame_play_story::update_player_status
(unsigned int index, player_status& p)
{
  std::ostringstream oss1;
  oss1 << gettext("Score:") << game_variables::get_persistent_score(index);
  p.score_text->set_text( oss1.str() );

  std::ostringstream oss2;
  oss2 << game_variables::get_persistent_lives_count(index);
  p.lives_text->set_text( oss2.str() );

  std::ostringstream oss3;
  oss3 << game_variables::get_persistent_stones_count(index);
  p.stone_text->set_text( oss3.str() );

  double energy(game_variables::get_max_energy(index));
  p.energy->set_length(energy);
  p.energy->set_level(energy);
  p.energy->set_max_level(energy);

  update_powers(index, p);
} // frame_play_story::update_player_status()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set power's pictures.
 * \param index The  index of the player.
 * \param p Status of the player.
 */
void ptb::frame_play_story::update_powers
(unsigned int index, player_status& p)
{
  update_power
    (game_variables::get_persistent_air_power(index),
     "gfx/ui/air-power.png", p.air_power);
  update_power
    (game_variables::get_persistent_fire_power(index),
     "gfx/ui/fire-power.png", p.fire_power);
  update_power
    (game_variables::get_persistent_water_power(index),
     "gfx/ui/water-power.png", p.water_power);
} // frame_play_story::update_powers()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a power picture.
 * \param power Indicates if the player has the power.
 * \param picture_name Name of the picture.
 * \param p The picture to set
 */
void ptb::frame_play_story::update_power
(bool power, const std::string& picture_name, bear::gui::picture* p)
{
  bear::engine::level_globals& glob =
    get_layer().get_level().get_globals();
  bear::visual::sprite s(glob.get_image( picture_name ));

  if ( power )
    s.set_intensity(1, 1, 1);
  else
    s.set_intensity(0.2, 0.2, 0.2);

  p->set_size(s.width(), s.height());
  p->set_picture(s);
} // frame_play_story::update_power()

/*----------------------------------------------------------------------------*/
/**
 * \brief Save the configuration.
 */
void ptb::frame_play_story::on_ok()
{
  if ( (m_index <= m_levels.size()) && ( !m_levels.empty()) )
    {
      std::string level_filename( m_levels[m_index].get_filename());
      std::string level(level_filename);

      size_t pos = level_filename.find("-1.cl");
      if (pos != std::string::npos)
        level = level.replace(pos, 5, "-intro.cl");

      game_variables::set_next_level_name( level );
      game_variables::set_corrupting_bonus_count
        ( game_variables::get_last_corrupting_bonus_count( level_filename ) );

      bear::engine::game::get_instance().set_waiting_level
        ( PTB_LOADING_LEVEL_NAME );
    }
  else
    {
      game_variables::set_next_level_name( "level/init.cl" );

      bear::engine::game::get_instance().set_waiting_level
        ( PTB_LOADING_LEVEL_NAME );
    }
} // frame_play_story::on_ok()

/*----------------------------------------------------------------------------*/
/**
 * \brief Last function called before closing the frame.
 */
bool ptb::frame_play_story::on_close()
{
  return true;
} // frame_play_story::on_close()

/*----------------------------------------------------------------------------*/
/**
 * \brief Choose the previous mini-game.
 */
void ptb::frame_play_story::on_previous()
{
  if ( m_levels.size() > 1 )
    {
      if ( m_index == 0 )
        m_index = m_levels.size() - 1;
      else
        --m_index;

      update_controls();
    }
} // frame_play_story::on_previous()

/*----------------------------------------------------------------------------*/
/**
 * \brief Choose the next mini-game.
 */
void ptb::frame_play_story::on_next()
{
  if ( m_levels.size() > 1 )
    {
      ++m_index;

      if ( m_index == m_levels.size() )
        m_index = 0;

      update_controls();
    }
} // frame_play_story::on_next()

/*----------------------------------------------------------------------------*/
/**
 * \brief Method called when a bonus is selected.
 */
void ptb::frame_play_story::on_bonus_selected(const std::string bonus_name)
{
  m_bonus_text->set_text(gettext(bonus_name.c_str()));
} // frame_play_story::on_bonus_selected()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the thumb of the mini-game.
 */
bear::visual::sprite ptb::frame_play_story::get_thumb() const
{
  bear::visual::sprite result;

  if ( !m_levels.empty() )
    {
      bear::engine::level_globals& glob =
        get_layer().get_level().get_globals();

      try
        {
          result = bear::visual::sprite
            ( glob.get_image( m_levels[m_index].get_thumb_filename() ) );
        }
      catch(...)
        { }
    }

  return result;
} // frame_play_story::get_thumb()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the default thumb of the mini-game.
 */
bear::visual::sprite ptb::frame_play_story::get_default_thumb() const
{
  bear::engine::level_globals& glob =
    get_layer().get_level().get_globals();
  const bear::visual::image& img = glob.get_image( "gfx/thumb/none.png" );

  return bear::visual::sprite( img );
} // frame_play_story::get_default_thumb()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the status picture of the mini-game.
 */
bear::visual::sprite ptb::frame_play_story::get_status_picture() const
{
  std::string medal("none");

  if ( !m_levels.empty() )
    medal = m_levels[m_index].get_medal_name();

  return get_layer().get_level().get_globals().auto_sprite
    ( "gfx/mini-game/medal.png", medal );
} // frame_play_story::get_thumb()

/*----------------------------------------------------------------------------*/
/**
 * \brief Close the current window (come back to the previous one).
 */
void ptb::frame_play_story::close_window() const
{
  super::close_window();
} // frame_play_story::close_window()
