#include "cmd_sys.h"
#include <print>

void System::ping(const dpp::slashcommand_t& event) {
    std::println("[INFO] /ping triggered.\n");
    event.reply("Bot Pong!");
}
