/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::spider class.
 * \author Sebastien Angibaud
 */
#include "ptb/item/castle/spider.hpp"
#include "ptb/item/castle/spider_venom.hpp"
#include "ptb/util/player_util.hpp"

#include "universe/forced_movement/forced_join.hpp"

#include "engine/world.hpp"
#include "engine/export.hpp"

#include <claw/assert.hpp>

BASE_ITEM_EXPORT( spider, ptb )

const unsigned int ptb::spider::s_soul_energy = 40;

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::spider::spider()
  : m_progress(NULL), m_max_walk_distance(200),
    m_spider_silk_length(300), m_silk_reference_item(NULL),
    m_link_visual(NULL), m_link(NULL)
{
  set_auto_mirror(true);
  set_mass(50);
  set_height(40);
  set_width(120);

  m_monster_type = monster::enemy_monster;
  m_energy = 20;
  m_offensive_phase = true;
  m_offensive_force = 10;
  m_offensive_coefficients[normal_attack] = 1;
  set_category("spider");
} // spider::spider()

/*----------------------------------------------------------------------------*/
/**
 * \brief Destructor.
 */
ptb::spider::~spider()
{
} // spider::~spider()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the media required by this class.
 */
void ptb::spider::pre_cache()
{
  get_level_globals().load_animation
    ("animation/forest/gorilla/gorilla_soul.canim");
  get_level_globals().load_model("model/castle/venom.cm");
  get_level_globals().load_model("model/castle/spider.cm");
  get_level_globals().load_model("model/headstone.cm");
} // spider::pre_cache()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialise the item.
 */
void ptb::spider::on_enters_layer()
{
  super::on_enters_layer();

  set_model_actor( get_level_globals().get_model("model/castle/spider.cm") );

  add_position_constraint_y();
  start_model_action("walk");
  m_progress = &spider::progress_walk;
  m_origin_position = get_center_of_mass();
  // TODO
  // set_counter_picture("gfx/castle/bonus-icons/bonus-icons.png","spider");
  create_silk_reference_item();
} // spider::on_enters_layer()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::spider::progress( bear::universe::time_type elapsed_time )
{
  super::progress( elapsed_time );

  if ( m_progress != NULL )
    (this->*m_progress)(elapsed_time);
} // spider::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type "real".
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::spider::set_real_field
( const std::string& name, double value )
{
  bool ok = true;

  if (name == "spider.max_walk_distance")
    m_max_walk_distance = value;
  else if (name == "spider.spider_silk_length")
    m_spider_silk_length = value;
  else
    ok = super::set_real_field(name, value);

  return ok;
} // spider::set_real_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform the item that he have no energy now.
 * \param attacker The attacker monster.
 */
void ptb::spider::inform_no_energy(const monster& attacker)
{
  m_is_injured = false;

  if ( get_current_action_name() != "dead" )
    {
      start_dead();
      die(attacker);

      const bear::engine::base_item* item =
        dynamic_cast<const bear::engine::base_item*>(&attacker);

      if ( item != NULL )
        {
          if ( item->get_center_of_mass().x < get_center_of_mass().x )
            add_internal_force( bear::universe::force_type(1000, 0) );
          else
            add_internal_force( bear::universe::force_type(-1000, 0) );
        }
    }
} // spider::inform_no_energy()
/*----------------------------------------------------------------------------*/
/**
 * \brief The monster is injure.
 * \param attacker The monster attacking me.
 * \param side The side on which I am attacked.
 * \param duration The duration of injure state.
 */
void ptb::spider::injure
( const monster& attacker, bear::universe::zone::position side,
  double duration )
{
  if ( ( get_current_action_name() == "walk"  ) ||
       ( get_current_action_name() == "throw_venom"  ) )
    {
      remove_position_constraint_y();
      add_position_constraint_x();
      start_model_action("dangle");
    }

  super::injure(attacker, side, duration);
} // ptb::spider::injure()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform the item tat he left the active region.
 */
void ptb::spider::leaves_active_region()
{
  super::leaves_active_region();

  if ( get_current_action_name() == "dead" )
    kill();
} // spider::leaves_active_region()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get picture filename for counted item class.
 */
std::string ptb::spider::get_picture_filename() const
{
  return "";
} // spider::get_picture_filename()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get picture name for counted item class.
 */
std::string ptb::spider::get_picture_name() const
{
  return "";
} // spider::get_picture_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get text for notification.
 */
std::string ptb::spider::get_notification_text() const
{
  return "spider carnage";
} // spider::get_notification_text()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the walk state.
 */
void ptb::spider::progress_walk( bear::universe::time_type elapsed_time )
{
  bool at_right = false;
  bool at_left = false;

  if ( scan(at_right, at_left) )
    start_model_action("throw_venom");
  else
    {
      if ( at_right )
        get_rendering_attributes().mirror(false);
      else if ( at_left )
        get_rendering_attributes().mirror(true);

      if ( get_center_of_mass().distance(m_origin_position) >
           m_max_walk_distance )
        get_rendering_attributes().mirror
          (get_center_of_mass().x > m_origin_position.x);

      if ( get_rendering_attributes().is_mirrored() )
        add_internal_force( bear::universe::force_type(-30000, 0) );
      else
        add_internal_force( bear::universe::force_type(30000, 0) );
    }
} // spider::progress_walk()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the throw_venom state.
 */
void ptb::spider::progress_throw_venom( bear::universe::time_type elapsed_time )
{
  bool at_right = false;
  bool at_left = false;

  if ( !scan(at_right, at_left) )
    {
      if ( at_right )
        get_rendering_attributes().mirror(false);
      else if ( at_left )
        get_rendering_attributes().mirror(true);

      if ( get_center_of_mass().distance(m_origin_position) >
           m_max_walk_distance )
        get_rendering_attributes().mirror
          (get_center_of_mass().x > m_origin_position.x);

      if ( get_rendering_attributes().is_mirrored() )
        add_internal_force( bear::universe::force_type(-5000, 0) );
      else
        add_internal_force( bear::universe::force_type(5000, 0) );
    }
} // spider::progress_throw_venom()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state dangle.
 */
void ptb::spider::progress_dangle( bear::universe::time_type elapsed_time )
{
  m_dangle_state = true;

  if ( m_go_up && ( !has_forced_movement() ) )
    {
      if ( m_link_visual != NULL )
        {
          m_link_visual->kill();
          m_link_visual = NULL;
        }

      remove_position_constraint_x();
      add_position_constraint_y();
      start_model_action("walk");
    }
} // spider::progress_dangle()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state dead.
 */
void ptb::spider::progress_dead( bear::universe::time_type elapsed_time )
{
  if (  has_bottom_contact() )
    {
      bear::visual::animation soul_anim
        ( get_level_globals().get_animation
          ("animation/forest/gorilla/gorilla_soul.canim") );
      create_headstone( get_bottom_middle(), soul_anim, s_soul_energy,
                        get_z_position() - 2 );
      kill();
    }
  else
    get_rendering_attributes().set_angle
      ( get_rendering_attributes().get_angle() - 0.03 );
} // spider::progress_dead()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to walk.
 */
void ptb::spider::start_walk()
{
  m_progress = &spider::progress_walk;
} // spider::start_walk()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start throw_venom state.
 */
void ptb::spider::start_throw_venom()
{
  set_speed(bear::universe::speed_type(0, 0));
  m_progress = &spider::progress_throw_venom;
} // spider::start_throw_venom()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start dangle state.
 */
void ptb::spider::start_dangle()
{
  m_progress = &spider::progress_dangle;
  create_silk_link(this);
  m_go_up = false;
  m_dangle_state = false;
} // spider::start_dangle()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start dead state.
 */
void ptb::spider::start_dead()
{
  if ( get_current_action_name() != "dead" )
    {
      if ( m_link != NULL )
        {
          remove_all_links();
          m_link = NULL;
        }

      if ( m_link_visual != NULL )
        {
          m_link_visual->kill();
          m_link_visual = NULL;
        }

      if ( m_dangle_state )
        {
          base_item * item(create_dead_reference_item());
          create_silk_link(item);
          create_link_visual(item);
          remove_position_constraint_x();
        }

      start_model_action("dead");
      m_progress = &spider::progress_dead;

      if ( has_forced_movement() )
        clear_forced_movement();
    }
} // spider::start_dead()

/*----------------------------------------------------------------------------*/
/**
 * \brief Throw venom.
 */
void ptb::spider::throw_venom()
{
  bear::engine::model_mark_placement m;

  if ( get_mark_placement("mouth", m) )
    {
      const bear::universe::position_type pos(m.get_position());
      spider_venom* new_spider_venom = new spider_venom;

      CLAW_ASSERT
        (new_spider_venom->is_valid(),
         "The spider_venom created by spider isn't correctly initialized" );
      new_spider_venom->is_main_venom();
      new_item( *new_spider_venom );

      new_spider_venom->set_center_of_mass(pos);
      new_spider_venom->set_z_position( m.get_depth_position() );
    }
} // spider::throw_venom()

/*----------------------------------------------------------------------------*/
/**
 * \brief Go up.
 */
void ptb::spider::go_up()
{
  if ( m_link != NULL )
    {
      remove_all_links();
      m_link = NULL;
    }

  m_go_up = true;

  bear::universe::forced_join mvt;
  mvt.set_reference_point_on_center(*m_silk_reference_item);
  mvt.set_auto_remove(true);
  mvt.set_total_time( 1 );

  set_forced_movement( mvt );
} // spider::go_up()

/*----------------------------------------------------------------------------*/
/**
 * \brief Scan if spider can throw venom.
 * \param player_at_right (out) True if player is at right.
 * \param player_at_left (out) True if player is at left.
 */
bool ptb::spider::scan(bool& player_at_right, bool& player_at_left)
{
  bool result = false;
  player_at_left = false;
  player_at_right = false;

  player_proxy p1 = util::find_player( get_level_globals(), 1 );
  player_proxy p2 = util::find_player( get_level_globals(), 2 );

  if( p1 != NULL )
    result = scan_for_player(p1, player_at_right, player_at_left);


  if ( !result && (p2 != NULL) )
    result = scan_for_player(p2, player_at_right, player_at_left);

  return result;
} // spider::scan()

/*----------------------------------------------------------------------------*/
/**
 * \brief Check if a player is visible for the spider.
 * \param p The player we are looking for.
 * \param player_at_right (out) True if player is at right.
 * \param player_at_left (out) True if player is at left.
 */
bool ptb::spider::scan_for_player
( const player_proxy& p, bool& player_at_right, bool& player_at_left ) const
{
  bool result = false;
  bool found = false;

  bear::universe::rectangle_type rect
    ( get_left() - 150, get_bottom() - m_spider_silk_length,
      get_right() + 150, get_bottom() );

  if ( rect.intersects(p.get_bounding_box()) )
    found = scan_no_wall_in_direction
      ( get_bottom_middle(), p.get_top_middle() - get_bottom_middle() );

  if ( found )
    {
      bear::engine::model_mark_placement m;

      if ( get_mark_placement("mouth", m) )
        {
          if ( m.get_position().x > p.get_right() )
            {
              if ( std::abs(p.get_right() - m_origin_position.x) <
                   m_max_walk_distance )
                player_at_left = true;
            }
          else if ( m.get_position().x < p.get_left() )
            {
              if ( std::abs(p.get_left() - m_origin_position.y) <
                   m_max_walk_distance )
                player_at_right = true;
            }
          else
            result = true;
        }
    }

  return result;
} // spider::scan_in_direction()

/*----------------------------------------------------------------------------*/
/**
 * \brief Scan if there is a player in a given direction.
 * \param origin The position from which we start watching.
 * \param dir The direction od scan.
 */
bool ptb::spider::scan_no_wall_in_direction
( const bear::universe::position_type& origin,
  const bear::universe::vector_type& dir ) const
{
  bear::universe::item_picking_filter filter;
  filter.set_can_move_items_value(true);

  if ( get_layer().has_world() )
    return
      get_layer().get_world().pick_item_in_direction
      (origin, dir, filter) == NULL;
  else
    return false;
} // spider::scan_no_wall_in_direction()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create link for dangle state.
 */
void ptb::spider::create_silk_link(base_item* ref)
{
  if ( m_silk_reference_item != NULL )
    {
      m_silk_reference_item->set_horizontal_middle(get_horizontal_middle());

      m_link = new bear::universe::link
        ( *ref, *m_silk_reference_item, 2000000, 0, m_spider_silk_length );

      create_link_visual(this);
    }
} // spider::create_silk_link()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create link visual.
 */
void ptb::spider::create_link_visual(base_item* ref)
{
  if ( m_link_visual != NULL )
        m_link_visual->kill();

  m_link_visual = new bear::continuous_link_visual;
  m_link_visual->set_items(ref, m_silk_reference_item);
  m_link_visual->set_center_of_mass(get_center_of_mass());
  m_link_visual->set_height(10);
  m_link_visual->set_width(10);
  bear::visual::sprite sp
    (get_level_globals().auto_sprite
     ("gfx/castle/spider/spider.png", "web" ));
  sp.mirror(true);
  m_link_visual->set_sprite(sp);

  new_item(*m_link_visual);
} // spider::create_link_visual()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create reference item for silk.
 */
void ptb::spider::create_silk_reference_item()
{
  m_silk_reference_item = new bear::reference_item;

  CLAW_ASSERT
    (m_silk_reference_item->is_valid(),
     "The reference_item created by spider isn't correctly initialized" );

  new_item( *m_silk_reference_item );

  m_silk_reference_item->set_center_of_mass(get_top_middle());
} // spider::create_silk_reference_item()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create reference item for dead state.
 */
bear::engine::base_item* ptb::spider::create_dead_reference_item()
{
  bear::reference_item* ref = new bear::reference_item;

  CLAW_ASSERT
    (ref->is_valid(),
     "The reference_item created by spider isn't correctly initialized" );
  ref->set_height(5);
  ref->set_width(5);
  new_item( *ref );

  ref->set_center_of_mass(get_center_of_mass());

  return ref;
} // spider::create_dead_reference_item()

/*----------------------------------------------------------------------------*/
/**
 * \brief Give a string representation of the item.
 * \param str (out) The result of the convertion.
 */
void ptb::spider::to_string( std::string& str ) const
{
  std::ostringstream oss;

  super::to_string(str);

  oss << "state: " << get_current_action_name() << "\n";
  oss << "origin_position: " << m_origin_position.x << " " <<
    m_origin_position.y << "\n";

  str += oss.str();
} // spider::to_string()

/*----------------------------------------------------------------------------*/
/**
 * \brief Export the methods of the class.
 */
void ptb::spider::init_exported_methods()
{
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::spider, start_throw_venom, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::spider, start_walk, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::spider, start_dangle, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::spider, start_dead, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::spider, go_up, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::spider, throw_venom, void );
} // spider::init_exported_methods()

/*----------------------------------------------------------------------------*/
TEXT_INTERFACE_IMPLEMENT_METHOD_LIST( ptb::spider )
