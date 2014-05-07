#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "config.h"
#include "platform.h"

void Platform::m_CommonHandleEvent(const ALLEGRO_EVENT &ev, State& state)
{
	switch(ev.type) {
	case ALLEGRO_EVENT_DISPLAY_CLOSE:
		m_done_flag = true;
		break;

	case ALLEGRO_EVENT_KEY_DOWN:
		state.KeyDown(ev.keyboard.keycode);
		break;

	case ALLEGRO_EVENT_KEY_UP:
		state.KeyUp(ev.keyboard.keycode);
		break;

	case ALLEGRO_EVENT_KEY_CHAR:
		state.KeyTyped(ev.keyboard.unichar);
		break;

	default:
		break;
	}
}

Platform::Platform() :
	m_done_flag { false }
{
	/* Initialize Allegro. */
	if (!al_init()) {
		exit(1); // TODO: Get rid of exits.
	}

	al_init_font_addon();
	if (!al_init_ttf_addon()) {
		exit(1);
	}

	if (!al_install_keyboard()) {
		exit(1);
	}

	al_set_new_display_option(ALLEGRO_DEPTH_SIZE, 16, ALLEGRO_SUGGEST);
	al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_OPENGL | ALLEGRO_OPENGL_3_0);

	/* Initialize basic resources. */
	m_display.reset(al_create_display(cfg_screen_w, cfg_screen_h));
	if (!m_display) {
		exit(1);
	}

	m_queue.reset(al_create_event_queue());
	if (!m_queue) {
		exit(1);
	}

	al_register_event_source(m_queue.get(), al_get_display_event_source(m_display.get()));
	al_register_event_source(m_queue.get(), al_get_keyboard_event_source());
}

Platform::~Platform()
{
}

void Platform::Loop(std::unique_ptr<State> initial_state)
{
	const double dt = 1.0 / cfg_fps;
	const double max_frame_time = 0.25;

	double current_time = al_get_time();
	double accumulator = 0.0;

	std::unique_ptr<State> current_state = std::move(initial_state);

	while(!m_done_flag) {

		/* Logic part. */
		double new_time = al_get_time();
		double frame_time = new_time - current_time;

		if(frame_time > max_frame_time) {
			frame_time = max_frame_time;
		}

		current_time = new_time;
		accumulator += frame_time;

		while (accumulator >= dt) {

			ALLEGRO_EVENT ev;
			while(!al_is_event_queue_empty(m_queue.get())) {
				al_get_next_event(m_queue.get(), &ev);
				m_CommonHandleEvent(ev, *current_state);
			}

			current_state->Tick(dt);
			accumulator -= dt;
		}

		/* Display part. */
		const double weight = accumulator / dt;
		current_state->Draw(weight);
		al_flip_display();
	}
}
