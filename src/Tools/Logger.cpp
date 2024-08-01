#include "Logger.hpp"
#include "../Renderer/Atlas.hpp"
#include "../Utils/Math.hpp"

Logger::Logger(SDL_Texture* logger, float logSpeed, bool enabled )
{
	m_logger = logger;
	m_log_speed = logSpeed;
	m_enabled = enabled;
}

void Logger::init(Atlas* atlas, TTF_Font* font, vec2f scale)
{
	if (atlas == nullptr || font == nullptr) {
		std::cout << "Couldnt initialize the logger! " << std::endl;
		m_enabled = false;
	}
	m_atlas = atlas;
	m_scale = scale;
	m_font = font;
}

void Logger::log(std::string text)
{
	auto data = std::make_unique<LogData>(text);

	m_logs.push_back(std::move(data));
}

void Logger::update(float deltaTime)
{
	if (m_logs.size() == 0 || !m_enabled)return;

	auto it = m_logs.begin();
	while (it != m_logs.end()) {
		if (!it->get()) {
			++it;
			continue;
		}
		it->get()->y = Math::lerp(it->get()->y, 60, m_log_speed * deltaTime);
		if (it->get()->y >= 59.8f) {
			it = m_logs.erase(it);
		}
		else {
			++it;
		}
	}
}

void Logger::draw()
{
	if (m_logs.size() == 0 || !m_enabled)return;

	for (auto& log : m_logs) {
		if (!log.get())continue;

		m_atlas->draw_texture(m_logger, m_scale, vec2f(25, log.get()->y), false, 1, false);
		m_atlas->draw_text({38, log.get()->y + 14}, log.get()->text.c_str(), m_font, { 255, 255, 255 });
	}
}
