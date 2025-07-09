#include "cmd_config.h"
#include "file_manager.h"
#include <print>

std::vector<dpp::command_option> ConfigCommand::get_options() const {
    return {
        dpp::command_option(dpp::co_string, "setting", "Setting to configure", true)
            .add_choice(dpp::command_option_choice("prefix", "prefix"))
            .add_choice(dpp::command_option_choice("channel", "channel"))
    };
}

void ConfigCommand::on_slash(const dpp::slashcommand_t& slash, const dpp::cluster& bot) {
    std::string guild_id = std::to_string(slash.command.guild_id);
    std::string setting = std::get<std::string>(slash.get_parameter("setting"));
    
    std::println("[INFO] /config triggered for setting: {}", setting);
    
    if (setting == "prefix") {
        // Show current prefix or allow setting new one
        std::string current_prefix = FileManager::load(guild_id, "prefix");
        if (current_prefix.empty()) {
            current_prefix = "!"; // default
        }
        
        dpp::message msg = build_main_message();
        msg.set_content(std::format("Current prefix: `{}`\nUse the modal to change it.", current_prefix));
        
        slash.reply(msg);
    } else {
        slash.reply("Configuration option not implemented yet!");
    }
}

dpp::message ConfigCommand::build_main_message() const {
    dpp::message msg;
    msg.add_component(
        dpp::component().add_component(
            dpp::component()
                .set_type(dpp::cot_button)
                .set_id("config_modal")
                .set_label("Configure Settings")
                .set_style(dpp::cos_primary)
        )
    );
    return msg;
}

dpp::interaction_modal_response ConfigCommand::build_modal() const {
    dpp::interaction_modal_response modal("config_modal", "Bot Configuration");
    modal.add_component(
        dpp::component()
            .set_type(dpp::cot_text_input)
            .set_id("prefix_input")
            .set_label("Command Prefix")
            .set_style(dpp::text_short)
            .set_placeholder("Enter new prefix (e.g., !)")
            .set_max_length(5)
            .set_required(true)
    );
    return modal;
}
