#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "diagnostics.h"
#include "config.h"
#include "platform.h"

Platform::Platform()
{
	// Initialize Allegro.
	if (!al_init()) {
		DIAG_ERROR_EXIT("Failed initializing allegro.\n");
	}

	al_init_font_addon();
	if (!al_init_ttf_addon()) {
		DIAG_ERROR_EXIT("Failed initializing TTF addon.\n");
	}

	if (!al_install_keyboard()) {
		DIAG_ERROR_EXIT("Failed installing keyboard.\n");
	}

	if (!al_install_mouse()) {
		DIAG_ERROR_EXIT("Failed installing mouse.\n");
	}

	al_set_new_display_option(ALLEGRO_DEPTH_SIZE, 16, ALLEGRO_SUGGEST);
	al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_OPENGL | ALLEGRO_OPENGL_3_0);

	// Initialize basic resources.
	m_display.reset(al_create_display(cfg_screen_w, cfg_screen_h));
	if (!m_display) {
		DIAG_ERROR_EXIT("Failed creating display.\n");
	}

	m_queue.reset(al_create_event_queue());
	if (!m_queue) {
		DIAG_ERROR_EXIT("Failed creating event queue.\n");
	}

	al_register_event_source(m_queue.get(), al_get_display_event_source(m_display.get()));
	al_register_event_source(m_queue.get(), al_get_keyboard_event_source());
	al_register_event_source(m_queue.get(), al_get_mouse_event_source());

	m_current_time = al_get_time();
	m_time_accumulator = 0;
}

Transition Platform::ProcessEvents(State& state)
{
	ALLEGRO_EVENT ev;
	while(!al_is_event_queue_empty(m_queue.get())) {
		al_get_next_event(m_queue.get(), &ev);
		switch(ev.type) {
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			return { Transition::State::END };

		case ALLEGRO_EVENT_KEY_DOWN:
			state.KeyDown(ev.keyboard.keycode);
			break;

		case ALLEGRO_EVENT_KEY_UP:
			state.KeyUp(ev.keyboard.keycode);
			break;

		case ALLEGRO_EVENT_KEY_CHAR:
			state.KeyTyped(ev.keyboard.unichar);
			break;

		case ALLEGRO_EVENT_MOUSE_AXES:
			state.MouseMove(ev.mouse.dx, ev.mouse.dy);
			al_set_mouse_xy(m_display.get(), cfg_screen_w / 2, cfg_screen_h / 2);
			break;

		default:
			break;
		}
	}

	return { Transition::State::THIS_STATE };
}

Transition Platform::LoopStep(State& state)
{
	const double dt = 1.0 / cfg_fps;
	const double max_frame_time = 0.25;

	double new_time = al_get_time();
	double frame_time = new_time - m_current_time;

	if(frame_time > max_frame_time) {
		frame_time = max_frame_time;
	}

	m_current_time = new_time;
	m_time_accumulator += frame_time;

	while (m_time_accumulator >= dt) {
		auto transition = state.Tick(dt);
		if (transition.target_state != Transition::State::THIS_STATE) {
			return transition;
		}
		m_time_accumulator -= dt;
	}

	const double weight = m_time_accumulator / dt;
	state.Draw(weight);
	al_flip_display();

	return { Transition::State::THIS_STATE };
}
