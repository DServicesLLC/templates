#include <dpp/dpp.h>
#include <cstdlib>
#include <string>
#include <print>
#include <iostream>
#include "manager.h"

int main () {

	const char* env("DISCORD_BOT_TOKEN");
	const char* token_env = std::getenv(env);
	
	if (!token_env) return std::println(std::cerr, "[FATAL] Environment variable {} not found!", env), 1;

	std::string token(token_env);
	std::println("[INFO] Environment variable {} found.", env);

	dpp::intents intents = static_cast<dpp::intents>(
				dpp::i_default_intents
				| dpp::i_guild_members
				| dpp::i_message_content
	);

	dpp::cluster bot(token, intents);
	// bot.on_log(dpp::utility::cout_logger());
	
	Manager mngr(bot);

	bot.on_ready([&bot, &mngr](const dpp::ready_t&) {
		std::println("[INFO] Bot is online and ready.");
		//bot.global_bulk_command_delete(); //------->> USE TO CLEAR ALL SLASH COMMAND CACHE
		mngr.register_commands(bot);
		
	});

	bot.on_slashcommand([&bot, &mngr](const dpp::slashcommand_t& event) {
		mngr.handle_slashcommand(event);
	});

	bot.on_button_click([&bot, &mngr](const dpp::button_click_t& event) {
		mngr.handle_button_click(event);
	});

	bot.on_select_click([&bot, &mngr](const dpp::select_click_t& event) {
		mngr.handle_select(event);
	});

	bot.on_form_submit([&bot, &mngr](const dpp::form_submit_t& event) {
		std::println("[INFO] Form submitted by <@{}> in guild <{}>", event.command.id.str(), event.command.guild_id.str());
		mngr.handle_form_submit(event);
	});
	
	bot.start(dpp::st_wait);
	return 0;
}
